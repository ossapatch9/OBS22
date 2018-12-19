/*
 * BurstList.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */


//Esta clase permite almacenar las rafagas en una cola, asignar los datos de cada una para enviarlas al siguente modulo

#ifndef BURSTLIST_H_
#define BURSTLIST_H_

#include <omnetpp.h>
#include "ScheduleBurst_m.h"
#include "Burst.h"
#include <vector>

using namespace std;

class BurstList: public cObject

{ //Hereda de cObject porque será usado como campo de control del mensaje
   private:

      long int counter; //Contador usado para asignar un único Id a cada elemento.
      long int numElems; //Número de elementos dentro del contador.

   protected:

      long int listSize; //Tamaño de la lista.
      int maxSize; //Máximo tamaño.
      int maxElems; //Máximo número de elementos.
      cOutVector numElemsVector; //Vector de salida.
      cQueue burstList; //Lista.

   public:

      BurstList();
     ~BurstList();

     int insertBurst(Burst *burst,simtime_t sendTime);
     void removeBurst(int bId);
     Burst* retrieveBurst(int index);
     int retrieveBurstSize(int index);
     simtime_t retrieveSendTime(int index);
     simtime_t retrieveMinOffset(int index);
     simtime_t retrieveMaxOffset(int index);
     //Establece el máximo tamaño y/o máxima longitud de la cola.

     void setMaxSize(int size);
     void setMaxElems(int numElems);
};
#endif /* BURSTLIST_H_ */
