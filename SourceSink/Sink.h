/*
 * Sink.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef SINK_H_
#define SINK_H_

//Modulo que elimina los mensajes entrantes (esto no se aplica a eventos reales)

#include <string.h>
#include <omnetpp.h>

class Sink: public cSimpleModule
{
protected:
    virtual void initialize ();
    virtual void handleMessage(cMessage *msg);
    virtual void updateDisplay();
    virtual void finish();

    cOutVector endToEndDelayVec;
    cStdDev eedStats;

    int sourceAddress;
    int destAddress;
    int miDireccion;

    double pDelay;
    double delaySim;
    double tDelay;

    //contadores Retardo extremo a extremo
    double eed0101 ; double eed0201 ; double eed0301 ; double eed0401 ; double eed0501 ; double eed0601 ; double eed0701 ; //Destino 01 //Origen XX
    double eed0801 ; double eed0901 ; double eed1001 ; double eed1101 ; double eed1201 ; double eed1301 ; double eed1401 ;
    double eed0102 ; double eed0202 ; double eed0302 ; double eed0402 ; double eed0502 ; double eed0602 ; double eed0702 ; //Destino 02 //Origen XX
    double eed0802 ; double eed0902 ; double eed1002 ; double eed1102 ; double eed1202 ; double eed1302 ; double eed1402 ;
    double eed0103 ; double eed0203 ; double eed0303 ; double eed0403 ; double eed0503 ; double eed0603 ; double eed0703 ; //Destino 03 //Origen XX
    double eed0803 ; double eed0903 ; double eed1003 ; double eed1103 ; double eed1203 ; double eed1303 ; double eed1403 ;
    double eed0104 ; double eed0204 ; double eed0304 ; double eed0404 ; double eed0504 ; double eed0604 ; double eed0704 ; //Destino 04 //Origen XX
    double eed0804 ; double eed0904 ; double eed1004 ; double eed1104 ; double eed1204 ; double eed1304 ; double eed1404 ;
    double eed0105 ; double eed0205 ; double eed0305 ; double eed0405 ; double eed0505 ; double eed0605 ; double eed0705 ; //Destino 05 //Origen XX
    double eed0805 ; double eed0905 ; double eed1005 ; double eed1105 ; double eed1205 ; double eed1305 ; double eed1405 ;
    double eed0106 ; double eed0206 ; double eed0306 ; double eed0406 ; double eed0506 ; double eed0606 ; double eed0706 ; //Destino 06 //Origen XX
    double eed0806 ; double eed0906 ; double eed1006 ; double eed1106 ; double eed1206 ; double eed1306 ; double eed1406 ;
    double eed0107 ; double eed0207 ; double eed0307 ; double eed0407 ; double eed0507 ; double eed0607 ; double eed0707 ; //Destino 07 //Origen XX
    double eed0807 ; double eed0907 ; double eed1007 ; double eed1107 ; double eed1207 ; double eed1307 ; double eed1407 ;
    double eed0108 ; double eed0208 ; double eed0308 ; double eed0408 ; double eed0508 ; double eed0608 ; double eed0708 ; //Destino 08 //Origen XX
    double eed0808 ; double eed0908 ; double eed1008 ; double eed1108 ; double eed1208 ; double eed1308 ; double eed1408 ;
    double eed0109 ; double eed0209 ; double eed0309 ; double eed0409 ; double eed0509 ; double eed0609 ; double eed0709 ; //Destino 09 //Origen XX
    double eed0809 ; double eed0909 ; double eed1009 ; double eed1109 ; double eed1209 ; double eed1309 ; double eed1409 ;
    double eed0110 ; double eed0210 ; double eed0310 ; double eed0410 ; double eed0510 ; double eed0610 ; double eed0710 ; //Destino 10 //Origen XX
    double eed0810 ; double eed0910 ; double eed1010 ; double eed1110 ; double eed1210 ; double eed1310 ; double eed1410 ;
    double eed0111 ; double eed0211 ; double eed0311 ; double eed0411 ; double eed0511 ; double eed0611 ; double eed0711 ; //Destino 11 //Origen XX
    double eed0811 ; double eed0911 ; double eed1011 ; double eed1111 ; double eed1211 ; double eed1311 ; double eed1411 ;
    double eed0112 ; double eed0212 ; double eed0312 ; double eed0412 ; double eed0512 ; double eed0612 ; double eed0712 ; //Destino 12 //Origen XX
    double eed0812 ; double eed0912 ; double eed1012 ; double eed1112 ; double eed1212 ; double eed1312 ; double eed1412 ;
    double eed0113 ; double eed0213 ; double eed0313 ; double eed0413 ; double eed0513 ; double eed0613 ; double eed0713 ; //Destino 13 //Origen XX
    double eed0813 ; double eed0913 ; double eed1013 ; double eed1113 ; double eed1213 ; double eed1313 ; double eed1413 ;
    double eed0114 ; double eed0214 ; double eed0314 ; double eed0414 ; double eed0514 ; double eed0614 ; double eed0714 ; //Destino 14 //Origen XX
    double eed0814 ; double eed0914 ; double eed1014 ; double eed1114 ; double eed1214 ; double eed1314 ; double eed1414 ;

    //variables para paquetes recibidos
    double arrivePacket0101 ; double arrivePacket0201 ; double arrivePacket0301 ; double arrivePacket0401 ; double arrivePacket0501 ; double arrivePacket0601 ; double arrivePacket0701 ; //Destino 01 //Origen XX
    double arrivePacket0801 ; double arrivePacket0901 ; double arrivePacket1001 ; double arrivePacket1101 ; double arrivePacket1201 ; double arrivePacket1301 ; double arrivePacket1401 ;
    double arrivePacket0102 ; double arrivePacket0202 ; double arrivePacket0302 ; double arrivePacket0402 ; double arrivePacket0502 ; double arrivePacket0602 ; double arrivePacket0702 ; //Destino 02 //Origen XX
    double arrivePacket0802 ; double arrivePacket0902 ; double arrivePacket1002 ; double arrivePacket1102 ; double arrivePacket1202 ; double arrivePacket1302 ; double arrivePacket1402 ;
    double arrivePacket0103 ; double arrivePacket0203 ; double arrivePacket0303 ; double arrivePacket0403 ; double arrivePacket0503 ; double arrivePacket0603 ; double arrivePacket0703 ; //Destino 03 //Origen XX
    double arrivePacket0803 ; double arrivePacket0903 ; double arrivePacket1003 ; double arrivePacket1103 ; double arrivePacket1203 ; double arrivePacket1303 ; double arrivePacket1403 ;
    double arrivePacket0104 ; double arrivePacket0204 ; double arrivePacket0304 ; double arrivePacket0404 ; double arrivePacket0504 ; double arrivePacket0604 ; double arrivePacket0704 ; //Destino 04 //Origen XX
    double arrivePacket0804 ; double arrivePacket0904 ; double arrivePacket1004 ; double arrivePacket1104 ; double arrivePacket1204 ; double arrivePacket1304 ; double arrivePacket1404 ;
    double arrivePacket0105 ; double arrivePacket0205 ; double arrivePacket0305 ; double arrivePacket0405 ; double arrivePacket0505 ; double arrivePacket0605 ; double arrivePacket0705 ; //Destino 05 //Origen XX
    double arrivePacket0805 ; double arrivePacket0905 ; double arrivePacket1005 ; double arrivePacket1105 ; double arrivePacket1205 ; double arrivePacket1305 ; double arrivePacket1405 ;
    double arrivePacket0106 ; double arrivePacket0206 ; double arrivePacket0306 ; double arrivePacket0406 ; double arrivePacket0506 ; double arrivePacket0606 ; double arrivePacket0706 ; //Destino 06 //Origen XX
    double arrivePacket0806 ; double arrivePacket0906 ; double arrivePacket1006 ; double arrivePacket1106 ; double arrivePacket1206 ; double arrivePacket1306 ; double arrivePacket1406 ;
    double arrivePacket0107 ; double arrivePacket0207 ; double arrivePacket0307 ; double arrivePacket0407 ; double arrivePacket0507 ; double arrivePacket0607 ; double arrivePacket0707 ; //Destino 07 //Origen XX
    double arrivePacket0807 ; double arrivePacket0907 ; double arrivePacket1007 ; double arrivePacket1107 ; double arrivePacket1207 ; double arrivePacket1307 ; double arrivePacket1407 ;
    double arrivePacket0108 ; double arrivePacket0208 ; double arrivePacket0308 ; double arrivePacket0408 ; double arrivePacket0508 ; double arrivePacket0608 ; double arrivePacket0708 ; //Destino 08 //Origen XX
    double arrivePacket0808 ; double arrivePacket0908 ; double arrivePacket1008 ; double arrivePacket1108 ; double arrivePacket1208 ; double arrivePacket1308 ; double arrivePacket1408 ;
    double arrivePacket0109 ; double arrivePacket0209 ; double arrivePacket0309 ; double arrivePacket0409 ; double arrivePacket0509 ; double arrivePacket0609 ; double arrivePacket0709 ; //Destino 09 //Origen XX
    double arrivePacket0809 ; double arrivePacket0909 ; double arrivePacket1009 ; double arrivePacket1109 ; double arrivePacket1209 ; double arrivePacket1309 ; double arrivePacket1409 ;
    double arrivePacket0110 ; double arrivePacket0210 ; double arrivePacket0310 ; double arrivePacket0410 ; double arrivePacket0510 ; double arrivePacket0610 ; double arrivePacket0710 ; //Destino 10 //Origen XX
    double arrivePacket0810 ; double arrivePacket0910 ; double arrivePacket1010 ; double arrivePacket1110 ; double arrivePacket1210 ; double arrivePacket1310 ; double arrivePacket1410 ;
    double arrivePacket0111 ; double arrivePacket0211 ; double arrivePacket0311 ; double arrivePacket0411 ; double arrivePacket0511 ; double arrivePacket0611 ; double arrivePacket0711 ; //Destino 11 //Origen XX
    double arrivePacket0811 ; double arrivePacket0911 ; double arrivePacket1011 ; double arrivePacket1111 ; double arrivePacket1211 ; double arrivePacket1311 ; double arrivePacket1411 ;
    double arrivePacket0112 ; double arrivePacket0212 ; double arrivePacket0312 ; double arrivePacket0412 ; double arrivePacket0512 ; double arrivePacket0612 ; double arrivePacket0712 ; //Destino 12 //Origen XX
    double arrivePacket0812 ; double arrivePacket0912 ; double arrivePacket1012 ; double arrivePacket1112 ; double arrivePacket1212 ; double arrivePacket1312 ; double arrivePacket1412 ;
    double arrivePacket0113 ; double arrivePacket0213 ; double arrivePacket0313 ; double arrivePacket0413 ; double arrivePacket0513 ; double arrivePacket0613 ; double arrivePacket0713 ; //Destino 13 //Origen XX
    double arrivePacket0813 ; double arrivePacket0913 ; double arrivePacket1013 ; double arrivePacket1113 ; double arrivePacket1213 ; double arrivePacket1313 ; double arrivePacket1413 ;
    double arrivePacket0114 ; double arrivePacket0214 ; double arrivePacket0314 ; double arrivePacket0414 ; double arrivePacket0514 ; double arrivePacket0614 ; double arrivePacket0714 ; //Destino 14 //Origen XX
    double arrivePacket0814 ; double arrivePacket0914 ; double arrivePacket1014 ; double arrivePacket1114 ; double arrivePacket1214 ; double arrivePacket1314 ; double arrivePacket1414 ;



    double eed1;double eed2;double eed3;double eed4;double eed5;double eed6;double eed7;double eed8;double eed9;double eed10;
    double eed11;double eed12;double eed13;double eed14;

    double numSaltos; //usada para calculo de reatrdo de procesamiento
    double procesDelay;

private:
    long numSent;
    long numReceived;
};


#endif /* SINK_H_ */
