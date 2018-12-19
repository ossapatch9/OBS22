/*
 * CoreOutputHorizon.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */


#include "CoreOutputHorizon.h"

Define_Module(CoreOutputHorizon);

CoreOutputHorizon::~CoreOutputHorizon(){
    int i;
    int numPorts = par("numPorts");
    for(i=0;i<numPorts;i++)
    free(horizon[i]);
    free(horizon);
    free(portLambdas);
}

void CoreOutputHorizon::initialize(){
   int numPorts = par("numPorts");
   int i=0;
   int j = 0;
   portLambdas= (int*)calloc(numPorts,sizeof(int));

   cStringTokenizer tokenizer(par("lambdasPerPort").stringValue());
   while(tokenizer.hasMoreTokens()){
   portLambdas[i] = atoi(tokenizer.nextToken());
      i++;
   }

   horizon = (simtime_t**)calloc(numPorts,sizeof(simtime_t*));

   for(i=0;i<numPorts;i++){
      horizon[i] = (simtime_t*)calloc(portLambdas[i],sizeof(simtime_t));

      // Se llena la matriz del horizone con ceros
      for(j=0;j<portLambdas[i];j++){
         horizon[i][j] = 0;
         WATCH(horizon[i][j]);
      }
   }

}

//Se debe encontrar una longitud de onda cuyo valor de horizonte sea el más cercano (o incluso igual) al tiempo de llegada dado.
int CoreOutputHorizon::findNearestLambda(int port,simtime_t arrivalTime){
   Enter_Method("Encontrando la longitud de onda mas cercana para el puerto %d  el tiempo %s",port,arrivalTime.str().c_str());

   int i;
   int min = 0;

   simtime_t minDiff = -1; // El valor inicial es -1 porque cero es una diferencia de tiempo válida

   for(i=0;i<portLambdas[port];i++){
      // Es un algoritmo mínimo simple
      if(arrivalTime > horizon[port][i]){
         if(minDiff == -1){ //No se ha encontrado un mínimo aún. Por ahora este valor está bien.
        min = i;
            minDiff = arrivalTime - horizon[port][i];
         }else if((arrivalTime - horizon[port][i]) < minDiff){ //Retorna el minimo valor encontrado
            min = i;
            minDiff = arrivalTime - horizon[port][i];
         }
      }
   }
   // Si minDiff es -1  en este punto, no se ha encontrado mínimo
   if(minDiff == -1) return -1;

   return min;
}

void CoreOutputHorizon::updateHorizon(int port, int lambda, simtime_t newTime){
   Enter_Method("actualizando %d,%d horizonte",port,lambda);
   horizon[port][lambda] = newTime;
}

simtime_t CoreOutputHorizon::getHorizon(int port,int lambda){
   Enter_Method("peticion %d,%d horizonte",port,lambda);
   if(lambda == -1) return -1; //Solo en caso de que lambda sea -1
   return horizon[port][lambda];
}


