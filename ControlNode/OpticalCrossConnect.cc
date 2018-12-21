/*
 * OpticalCrossConnect.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana
 */

#include "OpticalCrossConnect.h"
#include "Burst.h"

Define_Module(OpticalCrossConnect);

OpticalCrossConnect::~OpticalCrossConnect(){
    free(schedulingTable);
}

void OpticalCrossConnect::initialize(){

    OXCDelay = par("OXCDelay");

   // Todas las compuertas de entrada  se encuentran iniciadas en -1
   schedulingTable = (int*)calloc(gateSize("in"),sizeof(int));
   int i;
   for(i=0;i<gateSize("in");i++){
      schedulingTable[i] = -1;
      WATCH(schedulingTable[i]);
   }
}

void OpticalCrossConnect::handleMessage(cMessage *msg){

    if(msg->getKind() == 1){ //Inicio de la ráfaga.

        take(msg);//toma posesión
        Burst *recvBurst = check_and_cast < Burst*> (msg);
        numSaltos = recvBurst->getNumSaltos() + 1;
        recvBurst->setNumSaltos(numSaltos);

    }
   //Algoritmo sencillo: verifica si la compuerta de entrada; tiene una conexión programada y manda el mensaje a la compuerta de salida asignada.
   cGate *gate = msg->getArrivalGate();

   if(schedulingTable[gate->getIndex()] == -1) delete msg; //Compuerta de salida no asiganada. Se descarta la ráfaga
   else
      sendDelayed(msg,OXCDelay,"out",schedulingTable[gate->getIndex()]);
}

void OpticalCrossConnect::setGate(int inGate,int outGate){
   Enter_Method("programando conexion de compuerta %d -> %d",inGate,outGate);

   if(schedulingTable[inGate] != -1) opp_error("Attempting to schedule an already scheduled input channel. Channel id: %d",inGate);
   schedulingTable[inGate] = outGate;
}

void OpticalCrossConnect::unsetGate(int inGate){
   Enter_Method("desprogramando compuerta %d",inGate);
   schedulingTable[inGate] = -1;
}



