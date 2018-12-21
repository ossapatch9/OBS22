/*
 * CoreOutput.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#include "CoreOutput.h"

Define_Module(ControlOutput);

ControlOutput::~ControlOutput(){
   int i;
   for(i=0;i<numPorts;i++)
   free(gate2Colour[i]);
   free(gate2Colour);
   free(portLen);
   free(inDataBegin);
   free(outPortBegin);
}

void ControlOutput::initialize(){
   numPorts = par("numPorts");

   const char* portLenStr = par("lambdasPerPort").stringValue();
   if(strcmp(portLenStr,"") == 0) opp_error("OBS_CoreOutput: lambdasPerPort not initialized");

   //se crean espacios de memoria dinámica para las variables a continuacion

   portLen = (int*)calloc(numPorts,sizeof(int));
   inDataBegin = (int*)calloc(numPorts,sizeof(int));
   outPortBegin = (int*)calloc(numPorts,sizeof(int));

   cStringTokenizer tokenizer(portLenStr);
   int i = 0;
   while(tokenizer.hasMoreTokens()){
      portLen[i] = atoi(tokenizer.nextToken()) + 1; // lambdasPerPort considera colo canales de datos. En este vector se incluye un canal de control por cada fibra.
      i++;
   }

   inDataBegin[0] = numPorts; //La primera fibra comienza justo después de los canales de control

   for(i=1;i<numPorts;i++)
      inDataBegin[i] = inDataBegin[i-1] + (portLen[i-1] - 1); //Adiciona un número de canales (excepto control) para el índice de fibra anterior.

   //Este vector almacena el índice inicial sa cada salida de la fibra
   //Aquí se incluye el canal de control
   outPortBegin[0] = 0;

   for(i=1;i<numPorts;i++) //Similar a inDataBegin pero aquí no se abstrae 1 porque se incluirán canales de control
      outPortBegin[i] = outPortBegin[i-1] + (portLen[i-1]);

   //Crea el mapa de color inverso: lambda a colour

   //Indexado por número de puerto y lambda, retorna el color
   gate2Colour = (int**)calloc(numPorts,sizeof(int*));
   for(i=0;i<numPorts;i++)
      gate2Colour[i] = (int*)calloc(portLen[i]-1,sizeof(int));

   //Crea un mapa de colores: un vector de mapas. El mismo de CoreInput
   const char* colourString = par("colours");

   map<int,int> tempMap;
   colours.reserve(numPorts);

   //se adiciona si los vectores de colores no son definidos en el .ini
   if(strcmp(colourString,"") == 0){
      int j=0;
      for(i=0;i<numPorts;i++){
         for(j=0;j<(portLen[i]-1);j++){
            tempMap[j] = j;
            gate2Colour[i][j] = j; // Colour = lambda
         }
         colours.push_back(map<int,int>(tempMap));
         tempMap.clear();
      }
   }else{
      //Comienzo del proceso de análisis (parseo)
      cStringTokenizer colourTokenizer(colourString);

      int colourLambda = 0;
      int colourPort = 0;
      int colourValue = 0;
      while(colourTokenizer.hasMoreTokens()){
         const char* token = colourTokenizer.nextToken();
         if(strcmp(token,"|") == 0){ //Se lee la barra. Se cambia a la siguiente fibra y se reinician los contadores de lambda.
            colours.push_back(map<int,int>(tempMap));
            colourLambda = 0;
            colourPort++;
            tempMap.clear();
         }else{ //Se asume que es un valor entero y se registrar el color
            colourValue = atoi(token);
            tempMap[colourValue] = colourLambda;
            gate2Colour[colourPort][colourLambda] = colourValue;
            colourLambda++;
         }
      }
      //una vez terminado, se el mapa de colores en le vector
      colours.push_back(map<int,int>(tempMap));
      tempMap.clear();
   }
}

void ControlOutput::handleMessage(cMessage *msg){

    cGate *gate = msg->getArrivalGate();
    int msgPort = getOutPort(gate->getIndex());
    int msgLambda = getOutLambda(gate->getIndex());

    msg->setSchedulingPriority(0); //Restaura la prioridad del mensaje original

    send(msg,"out",outPortBegin[msgPort] + msgLambda); // Reenvia el paquete entrante a la corresponsiente compuerta de salida
}
int ControlOutput::getOutPort(int gateIndex){
   if(gateIndex < numPorts) //Es un BCP
      return gateIndex;
   else{ // Canal de datos
      int i;
      for(i=0;i<numPorts-1;i++){
         if((gateIndex >= inDataBegin[i]) && (gateIndex < inDataBegin[i+1]))
            return i;
      }
      if((gateIndex >= inDataBegin[numPorts-1]) && (gateIndex < inDataBegin[numPorts-1] + portLen[numPorts-1])) return numPorts - 1;
   }
   return -1;
}

int ControlOutput::getOutLambda(int gateIndex){
   int port = getOutPort(gateIndex); //Se usa getOutPort  para saber cual es la fibra a la cual pertenece el canal
   if(gateIndex < numPorts) //BCP
      return portLen[port] - 1; //Retorna el último lambda para esta fibra
   else
      return gateIndex - (outPortBegin[port] + (numPorts - port)); // La última suma se realizó para tener el cuenta el primer canal de datos es proporcional para el número  of the number of fibers
}

int ControlOutput::getOXCGate(int port,int lambda){
   Enter_Method("peticion de la salida OXC, para la compuerta %d, y longitud de onda %d\n",port,lambda);
   return inDataBegin[port] + lambda - numPorts;
}

int ControlOutput::getLambdaByColour(int port,int colour){
   Enter_Method("obteniendo longitud de onda por puerto %d y color %d\n",port,colour);
   if (colours[port].count(colour) != 0){//Si el color no existe
       return colours[port][colour];
   }
   else{//Si el color no existe
       opp_error("El colo registrado \"%d\ no se encuentra en el mapa", colour);
       return -1;
   }
}

int ControlOutput::getColourByLambda(int port,int lambda){
    Enter_Method_Silent();
   return gate2Colour[port][lambda];
}


