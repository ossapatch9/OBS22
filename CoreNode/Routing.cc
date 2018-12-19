/*
 * Routing.cc
 *
 *  Created on: 9/05/2013
 *      Author: Tatiana y Adriana
 */



/**
 * Esta clase utiliza la herramienta incluida en OMNeT, denominada cTpology, para encontrar el grafo de la red, y realiza
 * enrutamiento estático usando el algoritmo del camino más corto, sin peso "calculateUnweightedSingleShortestPathsTo"
 */

#include "Routing.h"

Define_Module(RoutingNuevo);

void RoutingNuevo::initialize(){


          miDireccion = getParentModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");
          cTopology *topo = new cTopology("topo");
          topo->extractByParameter("variableCoreNode");
          EV <<"Topologia Encontrada " <<topo->getNumNodes() <<" nodos\n";

          cTopology::Node *thisNode = topo->getNodeFor(getParentModule());//retorna el grafo del nodo que corresponde al módulo dado en la red, en este caso coreNode

          // Encontrar las conexiones salientes de cada nodo

          for (int i=0; i<topo->getNumNodes(); i++) //getNumNodes retorna el número de nodos en el grafo, en este caso son catorse y se enumeran del 0 al 13
          {
             if(topo->getNode(i)==thisNode) continue; //retorna el puntero del nodo en la posición i
             ev << "Nodo i=" << i+1 << " es " << thisNode->getModule()->getFullPath() << endl;
             ev << " Tiene-- " << thisNode->getNumOutLinks() << " conexiones hacia otros nodos\n";
             ev << " and " << thisNode->getNumInLinks() << " conexiones desde otros nodos\n";

             topo->calculateUnweightedSingleShortestPathsTo(topo->getNode(i)); //aplica el algoritmo dijkstra para encontrar los caminos más cortos en el grafo
             cGate *parentModuleGate = thisNode->getPath(0)->getLocalGate(); //getLocalGate retorna la compuerta del fin local de la conexión...getPath retorna el siguiente enlace en el camino más corto (número cero en este caso) hacía el nodo objetivo
             int gateIndex = parentModuleGate->getIndex();//retorna el índice de la compuerta padre--Es decir:coreNode
             direccion = topo->getNode(i)->getModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");    //getModule()->par("address");
             rTable[direccion] = gateIndex; //en una tabla se guarda la direccion y la compuerta de salida que conduce al destino más cercano requerido, esta tabla se usará más adelante para enrutar las ráfagas hacia su salida.
             EV << "  hacia la direccion: " << direccion << " la compuerta de salida es " << gateIndex << endl;
             ev << " Las conexiones de otros módulos son\n";
             }


          for (int j=0; j<thisNode->getNumOutLinks(); j++)
          {
             cTopology::Node *neighbour = thisNode->getLinkOut(j)->getRemoteNode(); //el puntero *neighbour devuelve las conexiones hacia otros modulos
             cGate *gate = thisNode->getLinkOut(j)->getLocalGate(); //el puntero *gate devuelve la compuerta de salida que corresponde al enlace de salida dado anteriormente.
             dirAdjacentNode = neighbour->getModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->getAncestorPar("address"); //devuelve la direccion del nodo adyancete al que esta conectado el nodo actual, dependiendo de su enlace de salida
             ev << " " << neighbour->getModule()->getFullPath()
             << " a traves de la compuerta " << gate->getFullName() <<" Dirreccion adyancente " <<dirAdjacentNode<< endl;
          }

 delete topo;
}

CoreRouting *RoutingNuevo::getEntry(int inLabel)
{
    lambdasC = getParentModule()->getParentModule()->par("lambdasCore");
    lambdasE = getParentModule()->getParentModule()->par("lambdasEdge");

    // Los parámetros mostrados a continuacion devuelven la primera y última compuerta de cada puerto en la red NSFnet. (Por ejemplo rango1 y rango2, rango 2 y rango 3, rango 3 y rango 4, rango4 y rango5 corresponden a: 3-7, 7,12 - 12,17 - 17,22 para el caso de lambdasEdge= 2 y lambdaCore=4)
    int rango1 = lambdasE +1;
    int rango2 = rango1 + lambdasC;
    int rango3 = rango1 + 2*lambdasC + 1;
    int rango4 = rango1 + 3*lambdasC + 2;
    int rango5 = rango1 + 4*lambdasC + 3;

    CoreRouting *item= new CoreRouting();

    //En este caso, si la direccion de origen de la rafaga es igual a la direccion de destino, la rafaga ya ha hecho su recorrido y se enviara al edge de destino que le correponde, este edge, tiene asignado el puerto 0;
    if(miDireccion==inLabel)
      {
        puertoSalida=0;
        item->setOutColor(-9);
        item->setOutPort(puertoSalida);
        item->setOutLabel(-9);
        return item->dup();
      }
       else{
            RoutingTable::iterator it = rTable.find(inLabel);//esta es a tabla hhalada en initialie que devuelve la compuerta de salida al buscar la direccion de destino
             int outGateIndex = (*it).second;//es el segundo componente del mapa, es decir; gate index
             EV << "Reenviando paquete " << " por la compuerta de salida: " << outGateIndex << endl;

               //Dependiendo del rango, la ráfaga saldra por la compuerta denominada "puertoSalida" para ser tratada de igual forma en el siguiente nodo o ser enviada a sus destino
                if(outGateIndex >=rango1 && outGateIndex<=rango2){
                    puertoSalida=1;
                    item->setOutColor(-9);
                    item->setOutPort(puertoSalida);
                    item->setOutLabel(-9);
                    return item->dup();
                }
                if(outGateIndex >rango2 && outGateIndex<=rango3){
                    puertoSalida=2;
                    item->setOutColor(-9);
                    item->setOutPort(puertoSalida);
                    item->setOutLabel(-9);
                    return item->dup();

                }
                if(outGateIndex >rango3 && outGateIndex<=rango4){
                    puertoSalida=3;
                    item->setOutColor(-9);
                    item->setOutPort(puertoSalida);
                    item->setOutLabel(-9);
                    return item->dup();
                }
                if(outGateIndex >rango4 && outGateIndex<=rango5){
                    puertoSalida=4;
                    item->setOutColor(-9);
                    item->setOutPort(puertoSalida);
                    item->setOutLabel(-9);
                    return item->dup();
                }
             }
    return NULL; //si la rafaga no es asignada a ninguna compuerta, se presenta un error, y la informacion de routing no puede ser almacenada en el BCP.
}


