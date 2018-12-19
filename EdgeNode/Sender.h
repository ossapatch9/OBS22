/*
 * Sender.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef SENDER_H_
#define SENDER_H_

#include <omnetpp.h>
#include <stdlib.h>
#include <vector>
#include "BurstList.h"
#include "BurstControlPacket_m.h"
#include "BurstifierInfo_m.h"
#include "BurstSenderInfo_m.h"

//Este modulo se encarga de convertir la rafaga en su correspondiente BCP y su contenido en datos, para ser enviada al la unidad de control
//Establece los tiempos de offset y envía el BCP por un canal dedicado y la rafaga por el canal hacia OXC.
//Usa el algoritmo que toma el horizonte mas cercano de una longitud de onda (la que esté libre en el menor tiempo)


class Sender: public cSimpleModule
{
protected:

    enum
    {
        OBS_PROGRAMAR_BCP,
        OBS_PROGRAMAR_FIN_BCP,
        OBS_PROGRAMAR_RAFAGA,
        OBS_PROGRAMAR_FIN_RAFAGA
    };



    int numSaltos; //variable para numero de saltos, para delay de procesamiento

    int* colour; // Implementación de colores en el módulo Sender (En el archivo .cc se encuentra más información).
    int numLambdas; // Número de canales de datos.
    double dataRate; // Velocidad de transmisión del canal óptico.
    int BCPSize; // Tamaño del BCP.
    simtime_t guardTime; // Offset entre la transmisión consectiva de ráfagas.
    int maxSchedBurstSize; // Tamaño máximo de la cola de ráfagas programadas (0 = infinito).

    bool control_is_busy; // Verdadero si el canal de control se encuentra actualmente ocupado.
    simtime_t *horizon; //Este vector muestra el tiempo de simulación en dónde cada canal se encuentra libre.
    std::vector<cOutVector*> horizonVec; //Vector de valor del horizonte. Uno para cada Lambda.
    BurstList scheduleBursts; //Lista de ráfaga programadas (esperando a ser enviadas).
    cQueue waitingBCP;  // Cola de BCPs esperando a ser enviados (porque ellos encontraron el canal para BCPs ocupado).


    //#============================== #============================== #==============================
    //Contadores establecido para propósitos estadisticos
    //#============================== #============================== #==============================
    int burstRecv;     // Contador de ráfagas recibidas.
    int burstSend;     // Contador de ráfagas enviadas.
    int burstSendCore; // Contador de ráfagas enviadas Edge-Core.

    int burstDroppedByOffset; // Número de ráfagas descartadas porque alcanzaron el offset mínimo.
    int burstDroppedByQueue; // Número de ráfagas descartadas porque scheduledBurst está lleno.


    bool testing; // Si es verdadero, el módulo no trata de auto-registrarse.

    cOutVector burstSize; // Este vector almacena los tamaños de las ráfagas recibidas.


    //#============================== #============================== #==============================
    //Dirección de Origen - Destino
    //#============================== #============================== #==============================
    int sourceAddress; //direccion origen  usada para el calculo de probabilidad de bloqueo
    int destAddress;   //direccion destino usada para el calculo de probabilidad de bloqueo


    //#============================== #============================== #==============================
    //Contadores Secuencia Origen-Destino
    //#============================== #============================== #==============================
    int secuencia0101; int secuencia0201; int secuencia0301; int secuencia0401; int secuencia0501; int secuencia0601; int secuencia0701; //Destino 01 //Origen XX
    int secuencia0801; int secuencia0901; int secuencia1001; int secuencia1101; int secuencia1201; int secuencia1301; int secuencia1401;
    int secuencia0102; int secuencia0202; int secuencia0302; int secuencia0402; int secuencia0502; int secuencia0602; int secuencia0702; //Destino 02 //Origen XX
    int secuencia0802; int secuencia0902; int secuencia1002; int secuencia1102; int secuencia1202; int secuencia1302; int secuencia1402;
    int secuencia0103; int secuencia0203; int secuencia0303; int secuencia0403; int secuencia0503; int secuencia0603; int secuencia0703; //Destino 03 //Origen XX
    int secuencia0803; int secuencia0903; int secuencia1003; int secuencia1103; int secuencia1203; int secuencia1303; int secuencia1403;
    int secuencia0104; int secuencia0204; int secuencia0304; int secuencia0404; int secuencia0504; int secuencia0604; int secuencia0704; //Destino 04 //Origen XX
    int secuencia0804; int secuencia0904; int secuencia1004; int secuencia1104; int secuencia1204; int secuencia1304; int secuencia1404;
    int secuencia0105; int secuencia0205; int secuencia0305; int secuencia0405; int secuencia0505; int secuencia0605; int secuencia0705; //Destino 05 //Origen XX
    int secuencia0805; int secuencia0905; int secuencia1005; int secuencia1105; int secuencia1205; int secuencia1305; int secuencia1405;
    int secuencia0106; int secuencia0206; int secuencia0306; int secuencia0406; int secuencia0506; int secuencia0606; int secuencia0706; //Destino 06 //Origen XX
    int secuencia0806; int secuencia0906; int secuencia1006; int secuencia1106; int secuencia1206; int secuencia1306; int secuencia1406;
    int secuencia0107; int secuencia0207; int secuencia0307; int secuencia0407; int secuencia0507; int secuencia0607; int secuencia0707; //Destino 07 //Origen XX
    int secuencia0807; int secuencia0907; int secuencia1007; int secuencia1107; int secuencia1207; int secuencia1307; int secuencia1407;
    int secuencia0108; int secuencia0208; int secuencia0308; int secuencia0408; int secuencia0508; int secuencia0608; int secuencia0708; //Destino 08 //Origen XX
    int secuencia0808; int secuencia0908; int secuencia1008; int secuencia1108; int secuencia1208; int secuencia1308; int secuencia1408;
    int secuencia0109; int secuencia0209; int secuencia0309; int secuencia0409; int secuencia0509; int secuencia0609; int secuencia0709; //Destino 09 //Origen XX
    int secuencia0809; int secuencia0909; int secuencia1009; int secuencia1109; int secuencia1209; int secuencia1309; int secuencia1409;
    int secuencia0110; int secuencia0210; int secuencia0310; int secuencia0410; int secuencia0510; int secuencia0610; int secuencia0710; //Destino 10 //Origen XX
    int secuencia0810; int secuencia0910; int secuencia1010; int secuencia1110; int secuencia1210; int secuencia1310; int secuencia1410;
    int secuencia0111; int secuencia0211; int secuencia0311; int secuencia0411; int secuencia0511; int secuencia0611; int secuencia0711; //Destino 11 //Origen XX
    int secuencia0811; int secuencia0911; int secuencia1011; int secuencia1111; int secuencia1211; int secuencia1311; int secuencia1411;
    int secuencia0112; int secuencia0212; int secuencia0312; int secuencia0412; int secuencia0512; int secuencia0612; int secuencia0712; //Destino 12 //Origen XX
    int secuencia0812; int secuencia0912; int secuencia1012; int secuencia1112; int secuencia1212; int secuencia1312; int secuencia1412;
    int secuencia0113; int secuencia0213; int secuencia0313; int secuencia0413; int secuencia0513; int secuencia0613; int secuencia0713; //Destino 13 //Origen XX
    int secuencia0813; int secuencia0913; int secuencia1013; int secuencia1113; int secuencia1213; int secuencia1313; int secuencia1413;
    int secuencia0114; int secuencia0214; int secuencia0314; int secuencia0414; int secuencia0514; int secuencia0614; int secuencia0714; //Destino 14 //Origen XX
    int secuencia0814; int secuencia0914; int secuencia1014; int secuencia1114; int secuencia1214; int secuencia1314; int secuencia1414;


    //#============================== #============================== #==============================
    //Contadores Raf.Enviada entre el SenderCore OrigenFijo-DestinoTodos
    //#============================== #============================== #==============================
    int burstSender_Core01XX; int burstSender_Core02XX; int burstSender_Core03XX; int burstSender_Core04XX; int burstSender_Core05XX; int burstSender_Core06XX; int burstSender_Core07XX;
    int burstSender_Core08XX; int burstSender_Core09XX; int burstSender_Core10XX; int burstSender_Core11XX; int burstSender_Core12XX; int burstSender_Core13XX; int burstSender_Core14XX;


    //#============================== #============================== #==============================
    //Contadores Raf.Generadas/Recibidas EdgeIn-EdgeOut OrigenTodos-DestinoFijo
    //#============================== #============================== #==============================
    int burstGeneratedXX01; int burstGeneratedXX02; int burstGeneratedXX03; int burstGeneratedXX04; int burstGeneratedXX05; int burstGeneratedXX06; int burstGeneratedXX07;
    int burstGeneratedXX08; int burstGeneratedXX09; int burstGeneratedXX10; int burstGeneratedXX11; int burstGeneratedXX12; int burstGeneratedXX13; int burstGeneratedXX14;


    //#============================== #============================== #==============================
    //Contadores Raf.Generadas/Recibidas EdgeIn-EdgeIn OrigenGenera-OrigenRecibe (mismo Origen-Destino)
    //#============================== #============================== #==============================
    int burstGenerated0101 ;  int burstGenerated0202 ;  int burstGenerated0303 ;  int burstGenerated0404 ;  int burstGenerated0505 ;  int burstGenerated0606 ;  int burstGenerated0707 ;
    int burstGenerated0808 ;  int burstGenerated0909 ;  int burstGenerated1010 ;  int burstGenerated1111 ;  int burstGenerated1212 ;  int burstGenerated1313 ;  int burstGenerated1414 ;

public:

    virtual ~Sender();

protected:

    cOutVector burstTam;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void finish();

private:

    int findNearestHorizon();
};
#endif /* SENDER_H_ */
