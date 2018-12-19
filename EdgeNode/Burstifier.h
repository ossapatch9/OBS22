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

// Esta clase almacena los paquetes entrantes y los ensambla en ráfagas ópticas usando un criterio dado (tiempo, número de paquetes, tamaño total de la cola de paquetes).
class Burstifier: public cSimpleModule
{
protected:

    cQueue burst; //Cola de paquetes.

    simtime_t maxTime; // Tiempo máximo. Si se cumple este tiempo. La ráfaga será ensamblada con el contenido de la cola en ese instante
    int maxSize; // Tamaño Máximo de la ráfaga.
    int numPackets; // Máximo número de paquetes.
    simtime_t minOffset; // Offset mínimo del BCP.
    simtime_t maxOffset; // Offset máximo del BCP.
    int minSizePadding; // Mínimo tamaño que una ráfaga debe tener. Si no logra conseguir este valor, se aumentan bits de relleno. Si es 0, no se aumentan bits de relleno
    bool addLastPacket; // Si es verdadedo, permite que el último paquete se adicione a la ráfaga, incluso si la ráfaga excede su tamaño. Si es falso, la ráfaga se ensambla y el paquete será el primero de la siguiente ráfaga.
    int tamHeader; // Tamaño de la cabecera de la ráfaga.
    int tamHeaderPacket; // Tamaño de la cabecera de cada paquete insertado a la ráfaga.

    //información sobre la ráfaga
    int burstBits; //Tamaño actual de la ráfaga, en bits.
    int numPacketsInBurst; //Número de paquetes de la ráfaga.
    int sourceAddress; //direccion de origen de la rafaga, usada para el calculo de retardo de propagacion --nuevo
    int destAddress; //direccion de destino de la rafaga --nuevo
    int destLabel; // Etiqueta de destino de la ráfaga

    cMessage *maxTime_msg; //Mensaje de tiempo máximo

    //Estadísticas
    int burstCounter;
    cStdDev recvPackSize; //Paquetes recibidos.
    cOutVector recvPackSizeVec; //Tamaño de los paquetes recibidos (en bytes).
    cStdDev timeAssembled;
    cOutVector avgPacketTime; // Promedio de retardo de paquetes, debido al ensamblado de ráfagas.

    simtime_t firstPacket_t; //Tiempo de llegada del primer paquete de la actual ráfaga.

public:

    virtual ~Burstifier();

protected:

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:

    //Construye un objeto de ráfagas.
    void assemblyBurst();
};


#endif /* BURSTIFIER_H_ */
