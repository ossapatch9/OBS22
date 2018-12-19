/*
 * CoreControlLogic.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef CORECONTROLLOGIC_H_
#define CORECONTROLLOGIC_H_

#include <omnetpp.h>
#include <map>
#include "CoreOutputHorizon.h"
#include "ControlUnitInfo_m.h"
#include "BurstControlPacket_m.h"
#include "BCPControlInfo_m.h"
#include "OpticalCrossConnect.h"
#include "CoreInput.h"
#include "CoreOutput.h"
#include "Routing.h"

#define OBS_SCHEDULE_OXC 1
#define OBS_UNSCHEDULE_OXC 2

//Crea un camino óptico basándose en el BCP entrante.

class CoreControlLogic : public cSimpleModule{
   private:

     CoreOutputHorizon *gatesHorizon; //Puntero al horizonte de salida.
     RoutingNuevo *routingNuevo; //Puntero a la clases rounting
     CoreInput *coreInput; //Puntero al módulo Input.
     CoreOutput *coreOutput; //Puntero al módulo Output.
     OpticalCrossConnect *oxc; //Puntero a OXC.

     simtime_t processingTime; //Unidad de control de procesamiento de tiempo para cada BCP.
     simtime_t guardTime; //Tiempo offset entre la llegada de la ráfaga y el orden de establecimieno del canal.
     double dataRate; //velocidad de transmisión del canal óptico.

     int dropCounter; //contador de ráfagas descartadas.
     int *recvBurstCounter; //Contador de ráfagas recibidas.
     int *schedBurstCounter; //Contador de ráfagas programadas.

   protected:
     int numSaltos; //variable para almacenar el numero de saltos que trae el bcp
     FILE *data_f; //Archivo descriptor de salida.

     virtual void initialize();
     virtual void finish();
     virtual void handleMessage(cMessage *msg);

   public:

     virtual ~CoreControlLogic();

};

#endif /* CORECONTROLLOGIC_H_ */
