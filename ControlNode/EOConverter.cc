/*
 * EOConverter.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#include<omnetpp.h>
#include "BurstControlPacket_m.h"
#include "BCPControlInfo_m.h"

using namespace std;

//Conversor �ptico El�ctrico. Convierte el BCP el�ctrico en el BCP �ptico (conmienzo y final del BCP)
class EOConverter : public cSimpleModule
{
   private:
      double dataRate; //Velocidad de transmisi�n de la fibra �ptica.
      simtime_t EOConversionDelay; //Retardo de conversi�n del m�dulo. Establecido como par�metro en el archivo .ned
   protected:
      cQueue **BCPqueues; // BCPs pendientes por enviar (porque estas cabeceras encontraron el canal ocupado). Uno por cada fibra.
      int numPorts; //N�mero de fibras.
      bool *control_is_busy; //es verdadero si el canal de control se encuentra ocupado en el momento.
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
   public:
      virtual ~EOConverter();
};

Define_Module(EOConverter);

EOConverter::~EOConverter(){
    for (int i=0; i<numPorts; i++)
    delete BCPqueues[i];
    delete [] BCPqueues;
    free(control_is_busy);
}

void EOConverter::initialize(){
   dataRate = par("dataRate");
   EOConversionDelay = par("EOConversionDelay");

   numPorts = par("numPorts");
   control_is_busy = (bool *)calloc(numPorts,sizeof(bool));
   BCPqueues = new cQueue *[numPorts];
   for (int i=0; i<numPorts; i++)
   {
       control_is_busy[i] = false;
       char buf[32];
       sprintf(buf, "waitingBCPs{%d}", i);
       BCPqueues[i] = new cQueue(buf);
   }
}

void EOConverter::handleMessage(cMessage *msg){
    //Si el mensaje no es un BCP entonces es un mensaje de control
    //se toma un BCP de la cola
    if(dynamic_cast <BurstControlPacket *> (msg) == NULL){
        if (msg->isSelfMessage()){
            //El n�mero del puerto ser� guardado en el par�metro "kind" del mensaje
            int waitingPort = msg->getKind();
            EV << "  clase de mensaje " << waitingPort << "\n";
            control_is_busy[waitingPort] = false;
            if (!BCPqueues[waitingPort]->isEmpty()){
                BurstControlPacket *waitingBCP = (BurstControlPacket*) BCPqueues[waitingPort]->pop();
                scheduleAt(simTime(),waitingBCP);
            }
            delete msg;
        }
        else{
            opp_error("Mensaje desconocido recibido");
        }
    }
    else{
        if(!msg->isSelfMessage()){//Si el BCP ha llegado desde fuera
            //Reiniciar la llegada del BCP
            BurstControlPacket *bcp = check_and_cast < BurstControlPacket *> (msg);
            BCPControlInfo *info = (BCPControlInfo*)bcp->getControlInfo();
            info->setBCPArrival(simTime()+EOConversionDelay);
            scheduleAt(simTime()+EOConversionDelay,bcp);
        }
        else{// Si el BCP es un automensaje (ha esperado debido al retardo de la conversi�n electro �ptica)
            BurstControlPacket *bcp = check_and_cast < BurstControlPacket *> (msg); // Convierte (si es posible) a un mensaje BCP de datos
            //La informaci�n de control no debe ser removida hasta que se manda el BCP
            BCPControlInfo *infoAux = (BCPControlInfo*)bcp->getControlInfo();

            int port = infoAux->getPort();
            EV << "  Puerto de EOConverter   " << port << "\n";

           if (control_is_busy[port]){//Si el canal de control est� acupado transmitiendo otro BCP, se coloca en la cola
               BCPqueues[port]->insert(bcp);
           }
           else{
               //Toma el canal de control
               control_is_busy[port] = true;

               BCPControlInfo *info = (BCPControlInfo*)bcp->removeControlInfo(); // Se extrae la informaci�n de control
               BurstControlPacket *endBCP = new BurstControlPacket("endBCP");
               endBCP->setIdBurstifier(bcp->getIdBurstifier());
               endBCP->setNumSeq(bcp->getNumSeq());

               int bcpSize = bcp->getBitLength(); // Se toman las caracter�sticas necesarias del BCP

               //Finalmente, se manda el BCP �ptico (comienzo y fin) con la sincroniaci�n correcta entre ellos.
               bcp->setName("iniBCP");
               bcp->setKind(1);
               endBCP->setKind(2);
               //El tiempo que el BCP ha estado en la cola y el tiempo de conversi�n EO deben ser tomados de burstArrivalDelta
               bcp->setDeltaArriveBurst(bcp->getDeltaArriveBurst() - EOConversionDelay - (simTime() - info->getBCPArrival()));
               send(bcp,"out",info->getPort());
               //Se manda el mensaje final del BCP despu�s de un tiempo de transmisi�n
               sendDelayed(endBCP,(bcpSize/dataRate),"out",info->getPort());
               //El mensaje de control que informa que el canal de control fuera del puerto i, se encuentra libre
               cMessage *ctlMsg=new cMessage("control_is_free");
               ctlMsg->setKind(port);
               scheduleAt(simTime()+(bcpSize/dataRate),ctlMsg);
               //Se borra la informaci�n de control
               delete info;
           }
        }
    }
}

