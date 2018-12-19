/*
 * Source.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef SOURCE_H_
#define SOURCE_H_


#include <fstream>
#include <omnetpp.h>
#include <vector>
#include <map>
#include <string.h>
#include "Packet_m.h"
#include "Routing.h"
#include <algorithm>

using namespace std;

//Generador de Paquetes: genera datagramas IP

class Source : public cSimpleModule{

private:

    int myAddress;
    std::vector<int> destAddresses;
    cPar *sendIATime;
    cPar *packetLengthBytes;
    //prioridad
    int type;

    cMessage *generatePacket;
    long pkCounter;

    simsignal_t endToEndDelaySignal;
    simsignal_t hopCountSignal;
    simsignal_t sourceAddressSignal;

    RoutingNuevo *routingNuevoS;


public:

    Source();
    virtual ~Source();

protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* SOURCE_H_ */
