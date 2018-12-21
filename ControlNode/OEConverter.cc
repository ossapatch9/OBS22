/*
 * OEConverter.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#include<omnetpp.h>
#include "BurstControlPacket_m.h"
#include "BCPControlInfo_m.h"

using namespace std;

// Conversor óptico-eléctrico. Reune el inicio y final de los BCPs y crea un "BCP eléctrico" que contiene información sobre la entrada de la fibra y el tiempo de llegada del iniBCP.
class OEConverter : public cSimpleModule
{
   private:
      list<BurstControlPacket*> pendingMsgs; // BCPs pendientes para conversión.
      simtime_t OEConversionDelay; //Retardo de conversión del módulo. Establecido como parámetro en el archivo .ned.
   protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      virtual void finish();
   public:
      virtual ~OEConverter();
};

Define_Module(OEConverter);

OEConverter::~OEConverter(){
   //Borra los mensajes pendientes de la cola
   list<BurstControlPacket*>::iterator iter_list;
   BurstControlPacket *item;
   for(iter_list = pendingMsgs.begin();iter_list != pendingMsgs.end(); iter_list++){
      item = *iter_list;
      delete item;
   }
   pendingMsgs.clear();
}

void OEConverter::initialize(){
   OEConversionDelay = par("OEConversionDelay");
}

void OEConverter::handleMessage(cMessage *msg){
   // BCP recibido
   cGate *gate = msg->getArrivalGate();
   BurstControlPacket *bcp = check_and_cast < BurstControlPacket *> (msg);
   int bId = bcp->getIdBurstifier();
   int nSeq = bcp->getNumSeq();

   if(bcp->getKind() == 1){ //Si se recibe el inicio de un BCP se coloca en la cola.
      BCPControlInfo *ctlMsg = new BCPControlInfo(); // Se addiciona la información de llegada del BCP
      ctlMsg->setBCPArrival(simTime());
      bcp->setControlInfo(ctlMsg);
      pendingMsgs.push_back(bcp);
   }else{ //Fin del BCP. Se busca el BCP en la cola y se crea un "BCP eléctrico"
      //Se busca usando los campos de identificacion del BCP.
      list<BurstControlPacket*>::iterator iter_list;
      BurstControlPacket *item;
      for(iter_list = pendingMsgs.begin();iter_list != pendingMsgs.end(); iter_list++){
         item = *iter_list;

         if((item->getIdBurstifier() == bId) && (item->getNumSeq() == nSeq)){ //Inicio del BCP encontrado

            BurstControlPacket *bcpDup = item->dup(); // Se duplica este mensaje el cual será el BCP eléctrico
            BCPControlInfo *ctlMsg = (BCPControlInfo*)item->removeControlInfo(); //Se remueve el objeto con la información de control
            pendingMsgs.remove(item);

            bcpDup->setKind(3); // Kind=3: BCP Eléctrico
            bcpDup->setName("elecBCP"); //Se modifica para volver el entorno gráfico más amigable y claro.

            ctlMsg->setPort(gate->getIndex());
            bcpDup->setDeltaArriveBurst(bcpDup->getDeltaArriveBurst() - (simTime() - ctlMsg->getBCPArrival()) - OEConversionDelay); // Actualiza el tiempo de llegada considerando el retardo de la converión, el tiempo de llegada del BCP original,  y tiempo actual.
            bcpDup->setControlInfo(ctlMsg);
            sendDelayed(bcpDup,OEConversionDelay,"out"); //Se manda el BCP eléctrico a la compuerta de salida.
            delete msg;
            delete item;
            return;
         }
      }
   }
}

void OEConverter::finish(){
   recordScalar("BCPs pending to be converted in electrical", pendingMsgs.size());
}


