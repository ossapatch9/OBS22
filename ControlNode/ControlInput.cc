/*
 * ControlInput.cc
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#include "ControlInput.h"


Define_Module(ControlInput);

ControlInput::~ControlInput(){
   free(portLen);
   free(inPortBegin);
   free(outDataBegin);
}

void ControlInput::initialize(){
    //obtengo la direccion de la fuente correspondiente al modulo EdgeAndCore actual
    //para usarla en el calculo de retardo de propagacion
    miDireccion = getParentModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");
    WATCH(miDireccion);

    LinkDelay = 0;


   numPorts = par("numPorts");

   const char* portLenStr = par("lambdasPerPort").stringValue();
   if(strcmp(portLenStr,"") == 0) opp_error("OBS_CoreInput: lambdasPerPort not initialized");

   portLen = (int*)calloc(numPorts,sizeof(int));
   // inPortBegin contiene el índice de la compuerta de salida de OMNeT++ donde cada fibra lógica comienza
   inPortBegin = (int*)calloc(numPorts,sizeof(int));
   // outDataBegin contiene le índice de la compuerta de salide de OMNeT++ donde cada fibra lógica comienza para los canales de datos.
   outDataBegin = (int*)calloc(numPorts,sizeof(int));

   cStringTokenizer tokenizer(portLenStr);
   int i = 0;

   while(tokenizer.hasMoreTokens()){
      portLen[i] = atoi(tokenizer.nextToken()) + 1; // lambdasPerPort considera sólo canales de datos. En este vector se incluye un canal de control para cada fibra.
      i++;
   }

   inPortBegin[0] = 0;
   for(i=1;i<numPorts;i++)
      //la fibra i comienza después del canal (i-1).
      //Si se añade el número i-1 de canales de fibra al número donde las i-1 fibras comienzan, se tendrá el el índice de compuerta de entrada para la fibra i
      inPortBegin[i] = inPortBegin[i-1] + (portLen[i-1]);

   outDataBegin[0] = numPorts; //El primer canal de datos irá justo después de los canales de control.
   for(i=1;i<numPorts;i++)
      outDataBegin[i] = outDataBegin[i-1] + (portLen[i-1] - 1);


   //Crea las estructuras de colores
   const char* colourString = par("colours");
   // colour es un vector que contiene objetos almacenados en un mapa. Cada entrada del vector, representa una fibra óptica y cada mapa representa los colores disponibles.
   // Maps se encuentra indexado por el número del color, y cada valor asociado es el Id del canal lógico (lambda)

   // Crea un mapa temporal para inicializar el vector de colores
   map<int,int> tempMap;
   colours.reserve(numPorts); // Pre-aloca la memoria para aumentar la eficiencia

   //Para el caso en que la variable string esté vacia:
   if(strcmp(colourString,"") == 0){
      int j=0;
      for(i=0;i<numPorts;i++){
         for(j=0;j<(portLen[i]-1);j++){ //i=0 -->tempMap[0]= 0...tempMap[1]=1... ---i=1 -->tempMap[0]=0...temMap[1]=1...tempMap[2]=2...tempMap[3]=3...
            tempMap[j] = j; // color = lambda
         }
         colours.push_back(map<int,int>(tempMap)); // Inserta tempMap como una entrada hacia el vector colours
         tempMap.clear(); // Limpia el mapa temporal. Está listo para usarse de nuevo.
      }
   }else{ // colourString se encuentra establecido. Se parsea la cadena y se llena la estructura
      //Se comienza el proceso de análisis (parseo)
      cStringTokenizer colourTokenizer(colourString);

      int colourLambda = 0;
      int colourValue = 0;
      while(colourTokenizer.hasMoreTokens()){
         const char* token = colourTokenizer.nextToken();
         if(strcmp(token,"|") == 0){ //Si se llega a la barra se cambia a la siguiente fibra y se reinicia el contador.
            colours.push_back(map<int,int>(tempMap)); //Se inserta el mapa creado en el vector
            colourLambda = 0;
            tempMap.clear(); // Se borra el mapa temporal
         }else{ //Se asume que el este valor es entero. Se registra el color
            colourValue = atoi(token); // Se convierte el valor de la cadena a un entero
            tempMap[colourValue] = colourLambda; //Se inserta el color como un índice del mapa y el lambda de la fibra como el valor.
            colourLambda++;
         }
      }
      // Cuando el análisis de la cadena termina, se inserta el mapa resultante en la última posición del vector
      colours.push_back(map<int,int>(tempMap));
      tempMap.clear(); // Todo se borra
   }
}

void ControlInput::handleMessage(cMessage *msg){


    cGate *gate = msg->getArrivalGate();

    int port = getInPort(gate->getIndex());
    WATCH(port);
    int lambda = getInLambda(gate->getIndex());

    char pkname[40];
    sprintf(pkname,"port--%d--lambda--%d--", port, lambda);
    EV << "info...." << pkname << endl;

    if((portLen[port] -1) == lambda){ // Si el valor del lambda es el último de esta fibra, la salida se establece como BCP
       send(msg,"out",port); // Los primeros numPorts de las compuertas de salida son asigandos a canales BCP. Se Manda este mensaje a la correspondiente salida. Es decir 0, 1, 2 o 3 o 4.
    }
    else{ //Si no es  un BCP es una ráfaga de datos

       // Se cambian las prioridades de la ráfaga para forzar los eventos. La ráfaga inicial tendrá prioridad 3 y la ráfaga final tendrá prioridad 0.
       if(msg->getKind() == 1){
           msg->setSchedulingPriority(3);
       }
       else{
           msg->setSchedulingPriority(0);}
       send(msg,"out",outDataBegin[port] + lambda); // Se usa outDataBegin para calcular el índice de la compuerta de salida OMNeT++
    }



    //codigo para retardo de propagacion
    if (miDireccion == 10){

        if (port == 1)
        {
           LinkDelay = 0.002;
        }

        else if (port == 2)
        {
           LinkDelay = 0.003;
        }
        else
        {
           LinkDelay = 0.004;
        }

    }


        WATCH(LinkDelay);

}

// Dado el índice de la compuerta de entrada, calcular el número de fibra correspondente.
int ControlInput::getInPort(int gateIndex){
   int i;
   // Usa inPortBegin y portLen en el último caso, mirando a qué fibra corresponde el índice.
   for(i=0;i<numPorts-1;i++)
      // ¿el parámetro gateIndex corresponde a la fibra i?
      if((gateIndex >= inPortBegin[i]) && (gateIndex < inPortBegin[i+1]))
         return i;

   // Si el parámetro gateIndex es ubicado en el último canal portLen[numPorts-1], entonces corresponde a la última fibra
   if((gateIndex >= inPortBegin[numPorts-1]) && (gateIndex < inPortBegin[numPorts-1] + portLen[numPorts-1])) return numPorts - 1;

   return -1;
}

// Se usa el índice de la compuerta de entrada para calcular el número del lambda dentro de la fibra correspondiente
int ControlInput::getInLambda(int gateIndex){
  //Primero se calcula el número de la fibra
  int port = getInPort(gateIndex);
  // Luego,  se substrae el índice donde pertenece el puerto. Esto hace que la primera lambda en la fibra, cuente como cero, la segunda fibra como uno, etc. En vez el valor del puerto.
  return gateIndex - inPortBegin[port];
}

// Convierte enlaces de datos, identificados por su Id de la fibra y lambda (no color) a compuertas de salida para OXC
int ControlInput::getOXCGate(int port, int lambda){
    ev << "getInOXC\n";
   Enter_Method("Obteniendo entrada para OXC en el puerto %d y longitud de ona %d\n",port,lambda);
   if((portLen[port] -1) == lambda) // Si es el último lambda de la fibra, es un BCP
       return -1;// Retorna -1 como error.
    else // Si no, es un canal de datos...
       // Se usa outDataBegin para la fibra deseada,  se calcula el canal de salida para este enlace
       return outDataBegin[port] + lambda - numPorts;
}

// Este método recibe un enlace identificado por el Id de la fibra y el color.
// Convierte el color a un lambda
int ControlInput::getLambdaByColour(int port, int colour){
    ev << "obteniendo longitud de onda por color\n";
    Enter_Method_Silent();
   if (colours[port].count(colour) != 0){//Si el color existe
       return colours[port][colour];
   }
   else{//Si el color no existe
       opp_error("El colo registrado \"%d\ no se encuentra en el mapa", colour);
       return -1;
   }
}
