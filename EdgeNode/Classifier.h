/*
 * Classifier.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef CLASSIFIER_H_
#define CLASSIFIER_H_

#include<omnetpp.h>
#include<stdio.h>
#include<string.h>
#include "Classifier_Rules.h"

using namespace std;

//Usa un archivo de reglas para asignarle una compuerta de salida a cada paquete.

class Classifier : public cSimpleModule{
   protected:
      Classifier_Rules *rules; //Clasificador de reglas..Puntero a la clase Classfier_Rules
      int numOuts; //Número de compuertas de salida.

      //Estadísticas
      cStdDev recvPackSize; //Paquetes recibidos
      int droppedPacket; //Número de paquetes descartados.
      cOutVector recvPackSizeVec; //Longitud de los paquetes recibidos (en bytes).

      virtual void initialize();
      virtual void finish();

      virtual void handleMessage(cMessage *msg);
   public:
      virtual ~Classifier();
};


#endif /* CLASSIFIER_H_ */


