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

    maxTime =par("maxTime"); // Tiempo m�ximo. Si este tiempo se cumple, la r�faga ser� ensamblada con el contenido de la cola en ese instante.
    maxSize=par("maxSize"); // Tama�o M�ximo de la r�faga.
    numPackets =par("numPackets"); // M�ximo n�mero de paquetes.
    minOffset=par("minOffset"); // Offset m�nimo del BCP.
    maxOffset=par("maxOffset"); // Offset m�ximo del BCP.
    minSizePadding=par("minSizePadding"); // M�nimo tama�o que una r�faga debe tener. Si no logra conseguir este valor, se aumentan bits de relleno. Si es 0, no se aumentan bits de relleno
    addLastPacket=par("addLastPacket"); // Si es verdadedo, permite que el �ltimo paquete se adicione a la r�faga, incluso si la r�faga excede su tama�o. Si es falso, la r�faga se ensambla y el paquete ser� el primero de la siguiente r�faga.
    tamHeader=par("tamHeader"); // Tama�o de la cabecera de la r�faga.
    tamHeaderPacket=par("tamHeaderPacket"); // Tama�o de la cabecera de cada paquete insertado a la r�faga.
    destLabel = par("destLabel"); //Etiqueta de destino



    //Inicio de la cola
    burst.setName("colabursts");

    //Inicio de contadores
    int tamHeaderBits = tamHeader*8;
    burstBits = tamHeaderBits;
    numPacketsInBurst = 0;

    //Se crea el mensaje de tiempo m�ximo
    maxTime_msg = new cMessage("maxTime");

    //Estad�sticas
    recvPackSizeVec.setName("burstifierInPacketSize");
    avgPacketTime.setName("avgPacketTime");
    recvPackSize.setName("recvPackSize");
    burstCounter =0;
    timeAssembled.setName("timeAssembled");

    recordScalar("my ID",getId());
}

//Se reciben los paquetes, se almacenan en una cola y se ensamblan si se cumple aguna condici�n
void Burstifier::handleMessage(cMessage *msg)
{
    //obtenemos direccion de fuente en este modulo
         //sourceAddress = getParentModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");
         //WATCH(sourceAddress);
    if(msg->isSelfMessage()) //Si recibe un automensaje...
    {
        assemblyBurst(); //Ensambla la r�faga e inicializa las variables
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

        // Comprobar si el busrtifier est� vacio
        if(burst.empty()) // Si lo est�, inicializar el tiempo m�ximo y la cola
        {
            scheduleAt(simTime() + maxTime, maxTime_msg ); //Establece el tiempo m�ximo
            //Registrar el momento en el que llega el primer paquete
              firstPacket_t = simTime();
        }

        else if(desborde && !addLastPacket)
        { // Entra si se necesita ensamblar la r�faga antes de que el paquete sea insertado en la cola
            if(burst.empty())opp_error("No es posible ensamblar una r�faga con una cola vac�a");

            //Ensamblar la r�faga e iniciar contadores
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

        //Si la sobrecarga no est� habilitada, pero ocurre sobrecarga cuando se inserta el primer paquete, se genera un error.
        if(desborde && !addLastPacket)
            opp_error("La sobrecarga se gener� insertando el primer mensaje y los requerimientos no permiten sobrecarga(overflowLastPacket es falso)");
        //Si ocurre la sobrecarga o se llena al m�ximo n�mero de paquetes se debe ensamblar la r�faga.
        if((desborde || numPacketsInBurst == numPackets) || burstBits ==maxSizeBits)
        {
            assemblyBurst();
            if(maxTime_msg->isScheduled()) cancelEvent(maxTime_msg);
        }
    }

}

void Burstifier::assemblyBurst()
{
    // Almacenar en avgPacketTime el promedio de tiempo de espera para todos los paquetes de esta r�faga
       avgPacketTime.record((simTime() - firstPacket_t) - timeAssembled.getMean());

    // Comprobar si la rafaga logra el m�nimo tama�o, si no, usar bits de relleno

    int minTamanRellenoBits = minSizePadding*8;

    if(burstBits < minTamanRellenoBits) burstBits =minTamanRellenoBits;

    //Se crea la r�faga e inserta el contenido de la cola
     Burst *bst = new Burst();

     bst->setNumPackets(numPacketsInBurst);
     bst->setBitLength(burstBits);
     bst->setMinOffset(minOffset);
     bst->setMaxOffset(maxOffset);
     bst->setIdBurstifier(getId()); //retorna el �ndice del vector correspondiente el m�dulo
     bst->setSecNum(burstCounter);
     bst->setSourceAddress(sourceAddress);
     bst->setDestAddress(destAddress);


     EV << "Tama�o de la rafaga..." << burstBits << endl;

     BurstifierInfo *info = new BurstifierInfo();
     info->setLabel(destLabel); //se define en el .ini una etiqueta de destino para cada burstifier
     bst->setControlInfo(info);

    //SenderID ser� establecido, una vez la r�faga llegue a Sender
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

    //Una vez ensamblada la r�faga, se mandan a la compuerta de salida.
    send(bst,"out");
}

void Burstifier::finish(){
      recordScalar("Packets received",recvPackSize.getCount());
      recordScalar("Average packet size",recvPackSize.getMean());
      recordScalar("Packet size variance",recvPackSize.getVariance());
}



