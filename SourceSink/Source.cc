/*
 * Source.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 *
 */

#include "Source.h"

Define_Module(Source);


Source::Source()
{
    generatePacket = NULL;
}

Source::~Source()
{
    cancelAndDelete(generatePacket);
}

void Source::initialize()
{
    myAddress = par("address");
    packetLengthBytes = &par("packetLength");
    sendIATime = &par("sendIaTime");  // parámetro volátil
    pkCounter = 0;

    WATCH(pkCounter);
    WATCH(myAddress);

    const char *destAddressesPar = par("destAddresses");
    cStringTokenizer tokenizer(destAddressesPar);
    const char *token;

    while ((token = tokenizer.nextToken())!=NULL)
        destAddresses.push_back(atoi(token)); //atoi convierte un carácter a un entero

    if (destAddresses.size() == 0)
        throw cRuntimeError("At least one address must be specified in the destAddresses parameter!");

    generatePacket = new cMessage("nextPacket");
    scheduleAt(sendIATime->doubleValue(), generatePacket);

    endToEndDelaySignal = registerSignal("endToEndDelay");
    hopCountSignal =  registerSignal("hopCount");
    sourceAddressSignal = registerSignal("sourceAddress");

}
void Source::handleMessage(cMessage *msg)
{
    if (msg == generatePacket)
    {

        //if (myAddress == 2 || myAddress == 3 || myAddress == 8){
        // Manejo y envio del paquete
        int destAddress = destAddresses[intuniform(0, destAddresses.size()-1)];
        //int destAddress = 1;

        char pkname[40];
        sprintf(pkname,"to-%d-#%ld", destAddress, pkCounter++);
        EV << "generating packet " << pkname << endl;

        Packet *pkt = new Packet(pkname);

        pkt->setByteLength(packetLengthBytes->longValue());
        pkt->setSrcAddr(myAddress);
        pkt->setDestAddr(destAddress);

        // Se establece la prioridad
        int type = intuniform(0,2);
        pkt->setPriority(type);

        send(pkt,"out");

        scheduleAt(simTime() + sendIATime->doubleValue(), generatePacket);
        if (ev.isGUI()) bubble("Generating packet...");

            //}
    }

}


