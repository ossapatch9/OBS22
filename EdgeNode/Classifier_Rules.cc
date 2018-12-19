/*
 * Classifier_Rules.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#include "Classifier_Rules.h"
#include "Packet_m.h"

Classifier_Rules::Classifier_Rules(string rule){
    Classifier_Rules(rule.c_str());
}

Classifier_Rules::Classifier_Rules(char* rule){
   char *token;

   //Inicia los valores en falso
   int i;
   for(i=0;i<2;i++) isSet[i] = false;

   token = strtok(rule," \n"); //divide un sring en string más paqueños (tokens) mediante un delimitador, en este caso, /n
   while(token != NULL){
        if(strcmp(token,"destAddr") == 0){ //Si la regla tiene la dirección de destino?

         //El siguiente token es una dirección de destino, si no lo es, genera un error.
         token = strtok(NULL," \n");
         if(token != NULL){
            destAddr = atoi(token);
            isSet[0] = true;
         }
         else{
          throw runtime_error("No se puede parsear el valor de la direccion de destino en la regla");
         }
      }
      else if(strcmp(token,"priority") == 0){ //La regla tiene un tipo de servicio?
         token = strtok(NULL," \n");
         if(token != NULL){
             priority = atoi(token);
               isSet[1] = true;
         }
         else{
             throw runtime_error("No es posible parsear el valor de la prioridad en la regla");
         }
      }
      token = strtok(NULL," ");
   }
}

Classifier_Rules::~Classifier_Rules(){}

bool Classifier_Rules::match(cMessage *msg){

   Packet *pkt = check_and_cast<Packet*>(msg);

   // Comprueba cuáles opciones se encuentran en las reglas

   if(isSet[0]){
      if(!(pkt->getDestAddr() == destAddr)) return false;
   }
   if(isSet[1]){
      if(!(pkt->getPriority() == priority)) return false;
   }
   //Si todo está bien, retorna verdadero y finaliza.

   return true;
}



