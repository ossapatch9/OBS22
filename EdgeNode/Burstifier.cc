/*
 * Burstifier.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#include "Burstifier.h"


Define_Module(Burstifier);

Burstifier::~Burstifier()
{
burst.clear();
cancelAndDelete (maxTime_msg);
}

void Burstifier::initialize()
{

    //Se inicializan las variables del archivo .ned

    maxTime =par("maxTime"); // Tiempo máximo. Si este tiempo se cumple, la ráfaga será ensamblada con el contenido de la cola en ese instante.
    maxSize=par("maxSize"); // Tamaño Máximo de la ráfaga.
    numPackets =par("numPackets"); // Máximo número de paquetes.
    minOffset=par("minOffset"); // Offset mínimo del BCP.
    maxOffset=par("maxOffset"); // Offset máximo del BCP.
    minSizePadding=par("minSizePadding"); // Mínimo tamaño que una ráfaga debe tener. Si no logra conseguir este valor, se aumentan bits de relleno. Si es 0, no se aumentan bits de relleno
    addLastPacket=par("addLastPacket"); // Si es verdadedo, permite que el último paquete se adicione a la ráfaga, incluso si la ráfaga excede su tamaño. Si es falso, la ráfaga se ensambla y el paquete será el primero de la siguiente ráfaga.
    tamHeader=par("tamHeader"); // Tamaño de la cabecera de la ráfaga.
    tamHeaderPacket=par("tamHeaderPacket"); // Tamaño de la cabecera de cada paquete insertado a la ráfaga.
    destLabel = par("destLabel"); //Etiqueta de destino



    //Inicio de la cola
    burst.setName("colabursts");

    //Inicio de contadores
    int tamHeaderBits = tamHeader*8;
    burstBits = tamHeaderBits;
    numPacketsInBurst = 0;

    //Se crea el mensaje de tiempo máximo
    maxTime_msg = new cMessage("maxTime");

    //Estadísticas
    recvPackSizeVec.setName("burstifierInPacketSize");
    avgPacketTime.setName("avgPacketTime");
    recvPackSize.setName("recvPackSize");
    burstCounter =0;
    timeAssembled.setName("timeAssembled");

    recordScalar("my ID",getId());
}

//Se reciben los paquetes, se almacenan en una cola y se ensamblan si se cumple aguna condición
void Burstifier::handleMessage(cMessage *msg)
{
    //obtenemos direccion de fuente en este modulo
         //sourceAddress = getParentModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");
         //WATCH(sourceAddress);
    if(msg->isSelfMessage()) //Si recibe un automensaje...
    {
        assemblyBurst(); //Ensambla la ráfaga e inicializa las variables
    }
    else //Si no, es un paquete?
    {
        Packet *pqt = check_and_cast<Packet*>(msg);

        sourceAddress = pqt->getSrcAddr();
        WATCH(sourceAddress);

        destAddress = pqt->getDestAddr();
        WATCH(destAddress);

        //almacenar el paquete entrante
        recvPackSizeVec.record(pqt->getByteLength());
        recvPackSize.collect(pqt->getByteLength());

        bool desborde = false;
        int maxSizeBits = maxSize*8;
        int tamHeaderPacketBits = tamHeaderPacket*8;

        if(((burstBits + pqt->getBitLength() + tamHeaderPacketBits)> maxSizeBits)) desborde = true;

        // Comprobar si el busrtifier está vacio
        if(burst.empty()) // Si lo está, inicializar el tiempo máximo y la cola
        {
            scheduleAt(simTime() + maxTime, maxTime_msg ); //Establece el tiempo máximo
            //Registrar el momento en el que llega el primer paquete
              firstPacket_t = simTime();
        }

        else if(desborde && !addLastPacket)
        { // Entra si se necesita ensamblar la ráfaga antes de que el paquete sea insertado en la cola
            if(burst.empty())opp_error("No es posible ensamblar una ráfaga con una cola vacía");

            //Ensamblar la ráfaga e iniciar contadores
            assemblyBurst();


            if(maxTime_msg->isScheduled())cancelEvent(maxTime_msg); //Se cancela el tiempo maximo y se programa uno nuevo
            scheduleAt(simTime() + maxTime, maxTime_msg);
            firstPacket_t = simTime();

            //Calcular si la sobrecarga se da con el primer paquete
                       desborde = false;

            if(((burstBits + pqt->getBitLength()+ tamHeaderPacketBits)> maxSizeBits)) desborde=true;
        }
        //Insertar el paquete actual en la cola
        timeAssembled.collect(simTime()-firstPacket_t);
        burst.insert(pqt);
        burstBits += pqt->getBitLength() + tamHeaderPacketBits;
        numPacketsInBurst++;

        //Si la sobrecarga no está habilitada, pero ocurre sobrecarga cuando se inserta el primer paquete, se genera un error.
        if(desborde && !addLastPacket)
            opp_error("La sobrecarga se generó insertando el primer mensaje y los requerimientos no permiten sobrecarga(overflowLastPacket es falso)");
        //Si ocurre la sobrecarga o se llena al máximo número de paquetes se debe ensamblar la ráfaga.
        if((desborde || numPacketsInBurst == numPackets) || burstBits ==maxSizeBits)
        {
            assemblyBurst();
            if(maxTime_msg->isScheduled()) cancelEvent(maxTime_msg);
        }
    }

}

void Burstifier::assemblyBurst()
{
    // Almacenar en avgPacketTime el promedio de tiempo de espera para todos los paquetes de esta ráfaga
       avgPacketTime.record((simTime() - firstPacket_t) - timeAssembled.getMean());

    // Comprobar si la rafaga logra el mínimo tamaño, si no, usar bits de relleno

    int minTamanRellenoBits = minSizePadding*8;

    if(burstBits < minTamanRellenoBits) burstBits =minTamanRellenoBits;

    //Se crea la ráfaga e inserta el contenido de la cola
     Burst *bst = new Burst();

     bst->setNumPackets(numPacketsInBurst);
     bst->setBitLength(burstBits);
     bst->setMinOffset(minOffset);
     bst->setMaxOffset(maxOffset);
     bst->setIdBurstifier(getId()); //retorna el índice del vector correspondiente el módulo
     bst->setSecNum(burstCounter);
     bst->setSourceAddress(sourceAddress);
     bst->setDestAddress(destAddress);


     EV << "Tamaño de la rafaga..." << burstBits << endl;

     BurstifierInfo *info = new BurstifierInfo();
     info->setLabel(destLabel); //se define en el .ini una etiqueta de destino para cada burstifier
     bst->setControlInfo(info);

    //SenderID será establecido, una vez la ráfaga llegue a Sender
    burstCounter++;
    cMessage *msgTemporal;

    while(!(burst.empty()))
    {
      msgTemporal=(cMessage*)burst.pop();
      bst->insertMessage(msgTemporal);
    }

    //Iniciar contadores
    burst.clear();
    numPacketsInBurst=0;
    int tamHeaderBits = tamHeader*8;
    burstBits = tamHeaderBits;
    firstPacket_t = 0;

    //Una vez ensamblada la ráfaga, se mandan a la compuerta de salida.
    send(bst,"out");
}

void Burstifier::finish(){
      recordScalar("Packets received",recvPackSize.getCount());
      recordScalar("Average packet size",recvPackSize.getMean());
      recordScalar("Packet size variance",recvPackSize.getVariance());
}



