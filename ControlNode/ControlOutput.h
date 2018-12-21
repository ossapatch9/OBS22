/*
 * CoreOutput.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef CONTROLOUTPUT_H_
#define CONTROLOUTPUT_H_

#include<omnetpp.h>
#include<map>
#include<vector>

using namespace std;

// Este módulo realiza la tarea inversa de CoreInput: reune los canales de control y de datos y los reordena con el fin de conectar el coreNode con otro nodo OBS.
// Es compatible con los "colores" de los canales de datos.

class ControlOutput : public cSimpleModule{
   private:
      vector< map<int,int> > colours; //vector del mapa de colores de salida (un mapa por cada fibra).
      int **gate2Colour; //mapeo entre puerto/lambda y colores.
      int numPorts; //número de fibras conectadas.
      int *portLen; //Número de canales (datos+control) por cada fibra óptica.
      int *inDataBegin;
      int *outPortBegin;
   protected:
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      int getOutPort(int gateIndex);
      int getOutLambda(int gateIndex);
   public:
      virtual ~ControlOutput();
      // Convierte el puerto y lambda a compuertas de salida hacia OXG.
      int getOXCGate(int port,int lambda);
      int getLambdaByColour(int port,int colour);
      //Obtiene el color de salida mediante el puerto y lambda.
      int getColourByLambda(int port,int lambda);
};

#endif /* CONTROLOUTPUT_H_ */
