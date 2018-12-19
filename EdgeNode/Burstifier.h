/*
 * Burstifier.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef BURSTIFIER_H_
#define BURSTIFIER_H_

#include <omnetpp.h>
#include"Burst.h"
#include"Packet_m.h"
#include "BurstifierInfo_m.h"

// Esta clase almacena los paquetes entrantes y los ensambla en r�fagas �pticas usando un criterio dado (tiempo, n�mero de paquetes, tama�o total de la cola de paquetes).
class Burstifier: public cSimpleModule
{
protected:

    cQueue burst; //Cola de paquetes.

    simtime_t maxTime; // Tiempo m�ximo. Si se cumple este tiempo. La r�faga ser� ensamblada con el contenido de la cola en ese instante
    int maxSize; // Tama�o M�ximo de la r�faga.
    int numPackets; // M�ximo n�mero de paquetes.
    simtime_t minOffset; // Offset m�nimo del BCP.
    simtime_t maxOffset; // Offset m�ximo del BCP.
    int minSizePadding; // M�nimo tama�o que una r�faga debe tener. Si no logra conseguir este valor, se aumentan bits de relleno. Si es 0, no se aumentan bits de relleno
    bool addLastPacket; // Si es verdadedo, permite que el �ltimo paquete se adicione a la r�faga, incluso si la r�faga excede su tama�o. Si es falso, la r�faga se ensambla y el paquete ser� el primero de la siguiente r�faga.
    int tamHeader; // Tama�o de la cabecera de la r�faga.
    int tamHeaderPacket; // Tama�o de la cabecera de cada paquete insertado a la r�faga.

    //informaci�n sobre la r�faga
    int burstBits; //Tama�o actual de la r�faga, en bits.
    int numPacketsInBurst; //N�mero de paquetes de la r�faga.
    int sourceAddress; //direccion de origen de la rafaga, usada para el calculo de retardo de propagacion --nuevo
    int destAddress; //direccion de destino de la rafaga --nuevo
    int destLabel; // Etiqueta de destino de la r�faga

    cMessage *maxTime_msg; //Mensaje de tiempo m�ximo

    //Estad�sticas
    int burstCounter;
    cStdDev recvPackSize; //Paquetes recibidos.
    cOutVector recvPackSizeVec; //Tama�o de los paquetes recibidos (en bytes).
    cStdDev timeAssembled;
    cOutVector avgPacketTime; // Promedio de retardo de paquetes, debido al ensamblado de r�fagas.

    simtime_t firstPacket_t; //Tiempo de llegada del primer paquete de la actual r�faga.

public:

    virtual ~Burstifier();

protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:

    //Construye un objeto de r�fagas.
    void assemblyBurst();
};


#endif /* BURSTIFIER_H_ */
