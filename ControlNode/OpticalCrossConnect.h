/*
 * OpticalCrossConnect.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef OPTICALCROSSCONNECT_H_
#define OPTICALCROSSCONNECT_H_

#include <omnetpp.h>

//Punto de interconexi�n donde las r�fagas �pticas pasan de forma transparente.

class OpticalCrossConnect : public cSimpleModule{
   private:

      int numSaltos;
      int* schedulingTable; //Vector que representa las conexiones de las compuertas de entrada.
      simtime_t OXCDelay;
   public:
      virtual ~OpticalCrossConnect();
      // Par�metro 1: Establece una conexi�n entre la compuerta de entrada y de salida.
      // Par�metro 2: compuerta de entrada del m�dulo OXG.
      // Par�metro 3: compuerta de salida del m�dulo OXG para conectar.
      void setGate(int inGate, int outGate);
      // Par�metro 1: Deshabilita la conexi�n con la compuerta de la salida dada.
      // Par�metro 2: compuerta de entrada del m�udlo OXG usada como �ndice.
      void unsetGate(int inGate);
   protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
};


#endif /* OPTICALCROSSCONNECT_H_ */
