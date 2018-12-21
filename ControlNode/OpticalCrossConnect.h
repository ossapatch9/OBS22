/*
 * OpticalCrossConnect.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef OPTICALCROSSCONNECT_H_
#define OPTICALCROSSCONNECT_H_

#include <omnetpp.h>

//Punto de interconexión donde las ráfagas ópticas pasan de forma transparente.

class OpticalCrossConnect : public cSimpleModule{
   private:

      int numSaltos;
      int* schedulingTable; //Vector que representa las conexiones de las compuertas de entrada.
      simtime_t OXCDelay;
   public:
      virtual ~OpticalCrossConnect();
      // Parámetro 1: Establece una conexión entre la compuerta de entrada y de salida.
      // Parámetro 2: compuerta de entrada del módulo OXG.
      // Parámetro 3: compuerta de salida del módulo OXG para conectar.
      void setGate(int inGate, int outGate);
      // Parámetro 1: Deshabilita la conexión con la compuerta de la salida dada.
      // Parámetro 2: compuerta de entrada del móudlo OXG usada como índice.
      void unsetGate(int inGate);
   protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
};


#endif /* OPTICALCROSSCONNECT_H_ */
