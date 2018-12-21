/*
 * Routing.h
 *
 *  Created on: 17/05/2013
 *      Author: Tatiana y Adriana
 */

#ifndef ROUTING_H_
#define ROUTING_H_

#include <map>
#include <omnetpp.h>
#include "BurstControlPacket_m.h"
#include "CoreRouting_m.h"
#include "vector"
#include "Algorithm"

class RoutingNuevo : public cSimpleModule
{
  public:

    int puertoSalida;

  private:
    int lambdasC;
    int lambdasE;
    int miDireccion; //agregado para cTopology
    int direccion;
    int numberPorts;
    typedef std::map<int,int> RoutingTable; //agregado para cTopology
    RoutingTable rTable; //agregado para cTopology
    int dirAdjacentNode; //Entero que contiene la dirección del nodo adyacente

  protected:

      virtual void initialize();

  public:
      CoreRouting *getEntry(int inLabel);
      std::map<int,int> findAdjacentNodes(int dir,std::map<int,int> ant);

 };

#endif /* ROUTING_H_ */
