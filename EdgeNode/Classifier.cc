/*
 * Classifier.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */


#include "Classifier.h"
#include "Packet_m.h"

Define_Module(Classifier);

Classifier::~Classifier(){
       if (numOuts != 0){
          free(rules); //libera memoria dinámica
       }
}
//Abre el archivo Classifier_Rules, lee todas las reglas y crea objetos para cada una.
void Classifier::initialize(){

   numOuts = par("numOuts");

   droppedPacket = 0;
   WATCH(droppedPacket); //permite inspeccionar esta variable en la interfaz gráfica y se emite en el archivo instantáneo.

   //Se inician las variables estadísticas
   recvPackSizeVec.setName("recvPacketSize");
   recvPackSize.setName("recvPackSize");

   if (numOuts != 0){

       //Almacena la información proveniente de Clasifier_Rules
       rules = (Classifier_Rules*)calloc(numOuts,sizeof(Classifier_Rules)); //se usa calloc para reservar memoria, de forma dinámica
       //lee una línea cada vez y crea la regla asociada para cada cola.
       char *line = (char*)calloc(1500,sizeof(char)); //Debido a esto, el máximo número de caracteres por línea es 1500.
       int i=0;

       //abre el archivo Rules.dat y lo almacena en rulesFile
       const char *rulesFile = par("rules");

       //Si rules está vacio, se muestra un mensaje de error y para la simulación.
       if(strlen(rulesFile) == 0){
           opp_error("El archivo de reglas no se encuentra definido");
       }
       // abre el archivo Rules.Dat en *ruleFile
       FILE *ruleFile = fopen(rulesFile,"r"); // r = leer el archivo... w=escribir...d=Borrar

       if(ruleFile != NULL){
           //fgets lee hasta que se encuentra un carácter \n
          while(fgets(line,1500,ruleFile) != NULL){
             if(strcmp(line,"\n") != 0 && line[0] != '#'){ //Ignora los comentarios (líneas que empiezan con #)
                 //toma "line" como parámetro de entrada
                 //para realizar la comparación de los parámetros
                 rules[i] = Classifier_Rules(line);
                i++;
             }
          }
       }
       else{
           opp_error("No es posible abrir el archivo de reglas");
       }

       fclose(ruleFile);
       // i debe ser igual a numQueues. Si no lo es, seguramente hay un error.
       if(!(i == numOuts)){
           printf("(Classifier_Rules) Aviso: El despachador de reglas no coincide con las colas de los modulos.\n");
       }
       free(line);
   }
}

//Cuando llega un paquete, se compara con todas las reglas. Si coincide con alguna regla, se manda al correspondiente compuerta de salida. Si no, se descarta.
void Classifier::handleMessage(cMessage *msg){
   int i;
   Packet *pkt = check_and_cast<Packet *> (msg);
   // se registra el paquete entrante
   recvPackSizeVec.record(pkt->getByteLength());
   recvPackSize.collect(pkt->getByteLength());
   //fin del registro

   //Verifica si el paquete coincide con alguna regla. Se mandará a la primera compuerta donde coincide la regla.
   for(i=0;i < numOuts;i++){
      if(rules[i].match(pkt)){
         send(pkt,"out",i);
         return;
      }
   }
   //Si el paquete no coincide con alguna regla, se descarta.
   delete pkt;
   //contador de paquetes descartados
   droppedPacket++;
}

void Classifier::finish(){
  recordScalar("Packets received",recvPackSize.getCount());
  recordScalar("Average packet size",recvPackSize.getMean());
  recordScalar("Packet size variance",recvPackSize.getVariance());
  recordScalar("Dropped Packets",droppedPacket);
}

