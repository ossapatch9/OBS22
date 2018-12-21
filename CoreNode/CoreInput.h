/*
 * CoreInput.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef COREINPUT_H_
#define COREINPUT_H_

#include<omnetpp.h>
#include<map>

using namespace std;

//Este m�dulo actua como interaz entre los m�dulos CorecontrolUnit y OXC. Separa canales de datos y de control.
//Tambi�n implementa m�todos para cambiar los colores a compuertas usando Ids f�sicos.

class ControlInput : public cSimpleModule
{
   private:

      vector< map<int,int> > colours; //Entrada del mapa de colores.
      int numPorts; //N�mero de fibras conectadas.
      int *inPortBegin; //Este vector almacena el �ndice de la compuerta de entrada a la cual el comienzo de cada fibra �ptica se encuentra conectada. Por ejemplo: si lambdasPerPort es "3 2 3", ser� "0 4 7".
      int *outDataBegin; //Este vector almacena el �ndice de la compuerta de salidaa la cual el comienzo de los canales de datos de cada fibra �ptica se encuentra conectada. Por ejemplo: si lambdasPerPort es "3 2 3", ser� "3 6 8".
      int *portLen; //N�mero de canales (datos+control) para cada fibra �ptica.
      int miDireccion;//direccion de fuente correspondiente a el EdgeAndCore actual
      double LinkDelay;

   public:
      virtual ~ControlInput();
      //Retorna la compuerta OXG a trav�s de la cu�l la r�faga pasar�.
      int getOXCGate(int port, int lambda);
      int getLambdaByColour(int port,int colour);


   protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      int getInPort(int gateIndex);
      int getInLambda(int gateIndex);
};


#endif /* COREINPUT_H_ */
