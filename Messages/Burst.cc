/*
 * Burst.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana
 */


#include "Burst.h"

Register_Class(Burst);

void Burst::insertMessage(cMessage *msg){
   Messages_var.insert(msg);
}

cMessage* Burst::retrieveMessage(){
   //Take the first element of the queue and retrieve it
   if(!Messages_var.empty()){
        cMessage *msg = (cMessage*)Messages_var.pop();
    return msg;
   }else return NULL; //If empty, return NULL
}

bool Burst::hasMessages(){
   if(Messages_var.empty()) return false;
   else return true;
}

Burst::~Burst(){
    Messages_var.clear();
}

