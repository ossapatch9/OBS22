/*
 * CoreControlLogic.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana
 */

#include "CoreControlLogic.h"

Define_Module(CoreControlLogic);

CoreControlLogic::~CoreControlLogic() {
    free(recvBurstCounter);
    free(schedBurstCounter);
}

void CoreControlLogic::initialize() {

    dropCounter = 0;
    WATCH(dropCounter);

    guardTime = par("guardTime");
    processingTime = par("BCPProcessingDelay");
    cModule *parent = getParentModule();
    dataRate = par("dataRate");

    //si el archivo "report file" esta vacio, retorna nulo ya que no se almacenan datos sobre las refagas descartadas.

    if (strcmp(par("reportFile"), "") == 0) {
        data_f = NULL;
    } else {
        data_f = fopen(par("reportFile"), "w");
    }

    //Se usa check_and_cast cuando se quiere enlazar con otro submódulo. De otra forma se obtendrá un error de puntero a nulo.

    gatesHorizon = check_and_cast<CoreOutputHorizon*>(
            parent->getSubmodule("GatesHorizon"));
    routingNuevo = check_and_cast<RoutingNuevo*>(
            (parent->getParentModule())->getSubmodule("routingNuevo"));
    coreInput = check_and_cast<CoreInput*>(
            (parent->getParentModule())->getSubmodule("coreInput"));
    coreOutput = check_and_cast<CoreOutput*>(
            (parent->getParentModule())->getSubmodule("coreOutput"));
    oxc = check_and_cast<OpticalCrossConnect*>(
            (parent->getParentModule())->getSubmodule("OXC"));

    //Se inician todas las estadísticas

    int numInPorts = coreInput->par("numPorts");
    int numOutPorts = coreOutput->par("numPorts");
    recvBurstCounter = (int*) calloc(numInPorts, sizeof(int));
    schedBurstCounter = (int*) calloc(numOutPorts, sizeof(int));

    int i = 0;
    for (i = 0; i < numInPorts; i++) {
        recvBurstCounter[i] = 0;
        WATCH(recvBurstCounter[i]);
    }
    for (i = 0; i < numOutPorts; i++) {
        schedBurstCounter[i] = 0;
        WATCH(schedBurstCounter[i]);
    }
}

//Se asume que este módulo se encuentra conectado al conversor óptico eléctrico, por lo tanto, solo se reciben BCPs eléctricas

void CoreControlLogic::handleMessage(cMessage *msg) {

    //Automensaje de programación de OXC. Si el mensaje tiene como tipo "kind = OBS_SCHEDULE_OXC"
    if (msg->getKind() == OBS_SCHEDULE_OXC) {
        OBS_ControlUnitInfo *info = check_and_cast<OBS_ControlUnitInfo*>(msg);
        oxc->setGate(info->getInGate(), info->getOutGate());
        delete msg;
        return;
    } else if (msg->getKind() == OBS_UNSCHEDULE_OXC) {
        OBS_ControlUnitInfo *info = check_and_cast<OBS_ControlUnitInfo*>(msg);
        oxc->unsetGate(info->getInGate());
        delete msg;
        return;
    }
    //Paso 1 - se comprueba la recepcion del BCP
    BurstControlPacket *bcp = check_and_cast<BurstControlPacket*>(msg);

    //se extrae el valor de numSaltos
    numSaltos = bcp->getNumSaltos() + 1;
    //fijar el valor de numero de saltos en el bcp
    bcp->setNumSaltos(numSaltos);

    //Se extrae la información de control del BCP
    BCPControlInfo *info = (BCPControlInfo*) bcp->getControlInfo();

    //Paso 2 - se extrae toda la información necesaria del BCP
    int burstColour = bcp->getColorBurst(); //Color de la ráfaga
    int arrivalPort = info->getPort(); //Puerto de llegada 0 1 2 3 o 4, depende de los puerto
    simtime_t arrivalDelta = bcp->getDeltaArriveBurst(); //Tiempo de offset entre el BCP y la ráfaga
    int burstLength = bcp->getBurstSize(); //Longitud de la ráfaga
    int destLabel = bcp->getLabel(); //Etiqueta de destino de la ráfaga (destino)
    int burstifierId = bcp->getIdBurstifier();
    int numSeq = bcp->getNumSeq();

    char pkname[40];
    sprintf(pkname, "----burstColour--%d--ArrivalPort%d--destLabel--%d---",
            burstColour, arrivalPort, destLabel);
    EV << "info" << pkname << endl;

    int inGate = coreInput->getOXCGate(arrivalPort,
            coreInput->getLambdaByColour(arrivalPort, burstColour)); //Petición del la compuerta de entrada OXC para la ráfaga entrante
    //Se cuenta este mensaje como una ráfaga recibida
    recvBurstCounter[arrivalPort]++;

    simtime_t burstArrival = simTime() + arrivalDelta;

    // Comprobar si la ráfaga se encuentra programada para llegar en el futuro. Si todo está bien, la rafaga debería comportarse de esta forma. Pero es posible que el offset entre el BCP y la ráfaga haya sido muy pequeño y en algún punto del camino, la ráfaga entra al nodo Core antes que su BCP, en este caso de descarta el mensaje.
    if (burstArrival < simTime()) {
        ev << "BORRADO\n";
        //BCP descartado. La ráfaga también se descarta.
        delete msg;
        dropCounter++;

        //Ráfaga descartada (caso 1)
        if (data_f != NULL) {
            fprintf(data_f, "%d %d %s %s 1 1\n", burstifierId, numSeq,
                    simTime().str().c_str(), burstArrival.str().c_str());
        }
        return;
    }

    //Calculos de tiempo.
    simtime_t OXCConnectTime = burstArrival - guardTime / 2;
    int burstLengthInBits = burstLength * 8; //Longitud de la ráfaga en Bits
    simtime_t OXCChannelIsFree = burstArrival + (burstLengthInBits / dataRate);
    simtime_t OXCDisconnectTime = OXCChannelIsFree + (guardTime) / 4;
    simtime_t newHorizon = OXCChannelIsFree + (3 * guardTime) / 4;

    //Petición de la tabla de enrutamiento en el nodo Core preguntando el puerto, color y etiqueta de salida.
    CoreRouting *result = routingNuevo->getEntry(destLabel);
    if (result == NULL)
        opp_error("Error durante el metodo de enrutamiento de la rafaga");
    int outPort = result->getOutPort();
    int outColour = result->getOutColor();
    int outLabel = result->getOutLabel();
    delete result;

    int lambda = 0;
    if (outColour == -9) { // opcion *. Escoger lambda con el horizonte más cercano.
        // Escoger el mejor canal
        lambda = gatesHorizon->findNearestLambda(outPort, burstArrival);

        if (lambda == -1) { //Si ningún lambda se encuentra disponible
            delete msg;
            dropCounter++;

            //Ráfaga descartada (caso 2)
            if (data_f != NULL) {
                fprintf(data_f, "%d %d %s %s 1 2\n", burstifierId, numSeq,
                        simTime().str().c_str(), burstArrival.str().c_str());
            }

            return;
        }
    } else { //si no se configura el canal con "*". Usar el canal asignado
             //Verificar si el canal está libre en el momento de llegada de la ráfaga. (outColour es un color, por está razón se convierte a lambda usando el método getLambdaByColour)
        lambda = coreOutput->getLambdaByColour(outPort, outColour);

        if (gatesHorizon->getHorizon(outPort, lambda) > burstArrival) {
            //Descartar el BCP si el canal no se encuentra disponible al momento de la llegada de la ráfaga
            delete msg;
            dropCounter++;

            //Ráfaga descartada (caso 3)
            if (data_f != NULL) {
                fprintf(data_f, "%d %d %s %s 1 3\n", burstifierId, numSeq,
                        simTime().str().c_str(), burstArrival.str().c_str());
            }

            return;
        }
    }

    OBS_ControlUnitInfo *controlInfo = new OBS_ControlUnitInfo();
    OBS_ControlUnitInfo *controlInfo1 = new OBS_ControlUnitInfo();

    //Contador para ráfagas entrantes
    schedBurstCounter[outPort]++;

    //Actualizar el vector horizonte
    gatesHorizon->updateHorizon(outPort, lambda, newHorizon);

    //Programacion OXC (establece un automensaje)-->desde OXC output hasta coreOutput, usa el tiempo de conexión del optical cross connect y un mensaje de control de información
    controlInfo->setInGate(inGate);
    controlInfo->setOutGate(coreOutput->getOXCGate(outPort, lambda));
    controlInfo->setKind(OBS_SCHEDULE_OXC);
    controlInfo->setSchedulingPriority(2);

    scheduleAt(OXCConnectTime, controlInfo);

    //Desprogramar OXC (establece un automensaje)-->usa el tiempo de DESconexión del opticalCrossConnect y un mensaje de control de información
    controlInfo1->setInGate(inGate);
    controlInfo1->setKind(OBS_UNSCHEDULE_OXC);
    controlInfo1->setSchedulingPriority(1);

    scheduleAt(OXCDisconnectTime, controlInfo1);

    // Se actualiza el  BCP
    info->setPort(outPort);

    bcp->setColorBurst(coreOutput->getColourByLambda(outPort, lambda));
    bcp->setDeltaArriveBurst(arrivalDelta - processingTime);

    if (outLabel == -9)
        bcp->setLabel(destLabel);
    else
        bcp->setLabel(outLabel);

    //Esperar el tiempo de procesamiento dentro del Control Logic y luego reenviar este mensaje
    sendDelayed(bcp, processingTime, "out");

    //Ráfaga enviada
    if (data_f != NULL) {
        fprintf(data_f, "%d %d %s %s 0 0\n", burstifierId, numSeq,
                simTime().str().c_str(), burstArrival.str().c_str());
    }
}

void CoreControlLogic::finish() {
    // Registrar ráfagas descartadas
    recordScalar("Burst dropped in Core Node", dropCounter);
    if (data_f != NULL) {
        fclose(data_f);
    }
}

