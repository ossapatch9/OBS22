/*
 * Classifier_Rules.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef CLASSIFIER_RULES_H_
#define CLASSIFIER_RULES_H_

#include<string>
#include<string.h>
#include <omnetpp.h>
#include"Packet_m.h"

using namespace std;

//Representa un comparador de reglas el cual provee un un método de comprobación de emparejamiento.
//El archivo que usa esta clase para comparar la direccion de destino y la clase de paquete, se denominda, rules.dat


class Classifier_Rules{

   protected:
      bool isSet[2]; //Define los campos de comparacion tenidos en cuentas. En este caso, lo campos son: direccion y tipo de paquete.
      int destAddr; //Dirección de destino (isSet[0]).
      int priority;//Prioridad (isSet[1]).

   public:
      Classifier_Rules(string rule);
      Classifier_Rules(char* rule);
      virtual ~Classifier_Rules();

      //Metodo de comparación: comprueba si el paquete coincide o no con la regla.

      bool match(cMessage *msg);
};


#endif /* CLASSIFIER_RULES_H_ */
