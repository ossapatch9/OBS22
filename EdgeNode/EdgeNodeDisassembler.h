/*
 * EdgeNodeDisassembler.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef EDGENODEDISASSEMBLER_H_
#define EDGENODEDISASSEMBLER_H_

#include <omnetpp.h>
#include "Burst.h"
#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Libera el contenido de la ráfaga cuando llega a su destino.

class EdgeNodeDisassembler : public cSimpleModule
{
   protected:
float a;
int miDireccion;

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

    double eed1;double eed2;double eed3;double eed4;double eed5;double eed6;double eed7;double eed8;double eed9;double eed10;
    double eed11;double eed12;double eed13;double eed14;

    //Contadores Secuencia Origen-Destino
    int secuencia0101 ; int secuencia0201 ; int secuencia0301 ; int secuencia0401 ; int secuencia0501 ; int secuencia0601 ; int secuencia0701 ; //Destino 01 //Origen XX
    int secuencia0801 ; int secuencia0901 ; int secuencia1001 ; int secuencia1101 ; int secuencia1201 ; int secuencia1301 ; int secuencia1401 ;
    int secuencia0102 ; int secuencia0202 ; int secuencia0302 ; int secuencia0402 ; int secuencia0502 ; int secuencia0602 ; int secuencia0702 ; //Destino 02 //Origen XX
    int secuencia0802 ; int secuencia0902 ; int secuencia1002 ; int secuencia1102 ; int secuencia1202 ; int secuencia1302 ; int secuencia1402 ;
    int secuencia0103 ; int secuencia0203 ; int secuencia0303 ; int secuencia0403 ; int secuencia0503 ; int secuencia0603 ; int secuencia0703 ; //Destino 03 //Origen XX
    int secuencia0803 ; int secuencia0903 ; int secuencia1003 ; int secuencia1103 ; int secuencia1203 ; int secuencia1303 ; int secuencia1403 ;
    int secuencia0104 ; int secuencia0204 ; int secuencia0304 ; int secuencia0404 ; int secuencia0504 ; int secuencia0604 ; int secuencia0704 ; //Destino 04 //Origen XX
    int secuencia0804 ; int secuencia0904 ; int secuencia1004 ; int secuencia1104 ; int secuencia1204 ; int secuencia1304 ; int secuencia1404 ;
    int secuencia0105 ; int secuencia0205 ; int secuencia0305 ; int secuencia0405 ; int secuencia0505 ; int secuencia0605 ; int secuencia0705 ; //Destino 05 //Origen XX
    int secuencia0805 ; int secuencia0905 ; int secuencia1005 ; int secuencia1105 ; int secuencia1205 ; int secuencia1305 ; int secuencia1405 ;
    int secuencia0106 ; int secuencia0206 ; int secuencia0306 ; int secuencia0406 ; int secuencia0506 ; int secuencia0606 ; int secuencia0706 ; //Destino 06 //Origen XX
    int secuencia0806 ; int secuencia0906 ; int secuencia1006 ; int secuencia1106 ; int secuencia1206 ; int secuencia1306 ; int secuencia1406 ;
    int secuencia0107 ; int secuencia0207 ; int secuencia0307 ; int secuencia0407 ; int secuencia0507 ; int secuencia0607 ; int secuencia0707 ; //Destino 07 //Origen XX
    int secuencia0807 ; int secuencia0907 ; int secuencia1007 ; int secuencia1107 ; int secuencia1207 ; int secuencia1307 ; int secuencia1407 ;
    int secuencia0108 ; int secuencia0208 ; int secuencia0308 ; int secuencia0408 ; int secuencia0508 ; int secuencia0608 ; int secuencia0708 ; //Destino 08 //Origen XX
    int secuencia0808 ; int secuencia0908 ; int secuencia1008 ; int secuencia1108 ; int secuencia1208 ; int secuencia1308 ; int secuencia1408 ;
    int secuencia0109 ; int secuencia0209 ; int secuencia0309 ; int secuencia0409 ; int secuencia0509 ; int secuencia0609 ; int secuencia0709 ; //Destino 09 //Origen XX
    int secuencia0809 ; int secuencia0909 ; int secuencia1009 ; int secuencia1109 ; int secuencia1209 ; int secuencia1309 ; int secuencia1409 ;
    int secuencia0110 ; int secuencia0210 ; int secuencia0310 ; int secuencia0410 ; int secuencia0510 ; int secuencia0610 ; int secuencia0710 ; //Destino 10 //Origen XX
    int secuencia0810 ; int secuencia0910 ; int secuencia1010 ; int secuencia1110 ; int secuencia1210 ; int secuencia1310 ; int secuencia1410 ;
    int secuencia0111 ; int secuencia0211 ; int secuencia0311 ; int secuencia0411 ; int secuencia0511 ; int secuencia0611 ; int secuencia0711 ; //Destino 11 //Origen XX
    int secuencia0811 ; int secuencia0911 ; int secuencia1011 ; int secuencia1111 ; int secuencia1211 ; int secuencia1311 ; int secuencia1411 ;
    int secuencia0112 ; int secuencia0212 ; int secuencia0312 ; int secuencia0412 ; int secuencia0512 ; int secuencia0612 ; int secuencia0712 ; //Destino 12 //Origen XX
    int secuencia0812 ; int secuencia0912 ; int secuencia1012 ; int secuencia1112 ; int secuencia1212 ; int secuencia1312 ; int secuencia1412 ;
    int secuencia0113 ; int secuencia0213 ; int secuencia0313 ; int secuencia0413 ; int secuencia0513 ; int secuencia0613 ; int secuencia0713 ; //Destino 13 //Origen XX
    int secuencia0813 ; int secuencia0913 ; int secuencia1013 ; int secuencia1113 ; int secuencia1213 ; int secuencia1313 ; int secuencia1413 ;
    int secuencia0114 ; int secuencia0214 ; int secuencia0314 ; int secuencia0414 ; int secuencia0514 ; int secuencia0614 ; int secuencia0714 ; //Destino 14 //Origen XX
    int secuencia0814 ; int secuencia0914 ; int secuencia1014 ; int secuencia1114 ; int secuencia1214 ; int secuencia1314 ; int secuencia1414 ;

    //contador auxiliar para el calculo de probabilidad de bloqueo
    int count0101 ; int count0201 ; int count0301 ; int count0401 ; int count0501 ; int count0601 ; int count0701 ; //Destino 01 //Origen XX
    int count0801 ; int count0901 ; int count1001 ; int count1101 ; int count1201 ; int count1301 ; int count1401 ;
    int count0102 ; int count0202 ; int count0302 ; int count0402 ; int count0502 ; int count0602 ; int count0702 ; //Destino 02 //Origen XX
    int count0802 ; int count0902 ; int count1002 ; int count1102 ; int count1202 ; int count1302 ; int count1402 ;
    int count0103 ; int count0203 ; int count0303 ; int count0403 ; int count0503 ; int count0603 ; int count0703 ; //Destino 03 //Origen XX
    int count0803 ; int count0903 ; int count1003 ; int count1103 ; int count1203 ; int count1303 ; int count1403 ;
    int count0104 ; int count0204 ; int count0304 ; int count0404 ; int count0504 ; int count0604 ; int count0704 ; //Destino 04 //Origen XX
    int count0804 ; int count0904 ; int count1004 ; int count1104 ; int count1204 ; int count1304 ; int count1404 ;
    int count0105 ; int count0205 ; int count0305 ; int count0405 ; int count0505 ; int count0605 ; int count0705 ; //Destino 05 //Origen XX
    int count0805 ; int count0905 ; int count1005 ; int count1105 ; int count1205 ; int count1305 ; int count1405 ;
    int count0106 ; int count0206 ; int count0306 ; int count0406 ; int count0506 ; int count0606 ; int count0706 ; //Destino 06 //Origen XX
    int count0806 ; int count0906 ; int count1006 ; int count1106 ; int count1206 ; int count1306 ; int count1406 ;
    int count0107 ; int count0207 ; int count0307 ; int count0407 ; int count0507 ; int count0607 ; int count0707 ; //Destino 07 //Origen XX
    int count0807 ; int count0907 ; int count1007 ; int count1107 ; int count1207 ; int count1307 ; int count1407 ;
    int count0108 ; int count0208 ; int count0308 ; int count0408 ; int count0508 ; int count0608 ; int count0708 ; //Destino 08 //Origen XX
    int count0808 ; int count0908 ; int count1008 ; int count1108 ; int count1208 ; int count1308 ; int count1408 ;
    int count0109 ; int count0209 ; int count0309 ; int count0409 ; int count0509 ; int count0609 ; int count0709 ; //Destino 09 //Origen XX
    int count0809 ; int count0909 ; int count1009 ; int count1109 ; int count1209 ; int count1309 ; int count1409 ;
    int count0110 ; int count0210 ; int count0310 ; int count0410 ; int count0510 ; int count0610 ; int count0710 ; //Destino 10 //Origen XX
    int count0810 ; int count0910 ; int count1010 ; int count1110 ; int count1210 ; int count1310 ; int count1410 ;
    int count0111 ; int count0211 ; int count0311 ; int count0411 ; int count0511 ; int count0611 ; int count0711 ; //Destino 11 //Origen XX
    int count0811 ; int count0911 ; int count1011 ; int count1111 ; int count1211 ; int count1311 ; int count1411 ;
    int count0112 ; int count0212 ; int count0312 ; int count0412 ; int count0512 ; int count0612 ; int count0712 ; //Destino 12 //Origen XX
    int count0812 ; int count0912 ; int count1012 ; int count1112 ; int count1212 ; int count1312 ; int count1412 ;
    int count0113 ; int count0213 ; int count0313 ; int count0413 ; int count0513 ; int count0613 ; int count0713 ; //Destino 13 //Origen XX
    int count0813 ; int count0913 ; int count1013 ; int count1113 ; int count1213 ; int count1313 ; int count1413 ;
    int count0114 ; int count0214 ; int count0314 ; int count0414 ; int count0514 ; int count0614 ; int count0714 ; //Destino 14 //Origen XX
    int count0814 ; int count0914 ; int count1014 ; int count1114 ; int count1214 ; int count1314 ; int count1414 ;

    //contador de rafagas que llegan a este modulo de un origen especifico a un destino especifico
    double arriveBurst0101 ; double arriveBurst0201 ; double arriveBurst0301 ; double arriveBurst0401 ; double arriveBurst0501 ; double arriveBurst0601 ; double arriveBurst0701 ; //Destino 01 //Origen XX
    double arriveBurst0801 ; double arriveBurst0901 ; double arriveBurst1001 ; double arriveBurst1101 ; double arriveBurst1201 ; double arriveBurst1301 ; double arriveBurst1401 ;
    double arriveBurst0102 ; double arriveBurst0202 ; double arriveBurst0302 ; double arriveBurst0402 ; double arriveBurst0502 ; double arriveBurst0602 ; double arriveBurst0702 ; //Destino 02 //Origen XX
    double arriveBurst0802 ; double arriveBurst0902 ; double arriveBurst1002 ; double arriveBurst1102 ; double arriveBurst1202 ; double arriveBurst1302 ; double arriveBurst1402 ;
    double arriveBurst0103 ; double arriveBurst0203 ; double arriveBurst0303 ; double arriveBurst0403 ; double arriveBurst0503 ; double arriveBurst0603 ; double arriveBurst0703 ; //Destino 03 //Origen XX
    double arriveBurst0803 ; double arriveBurst0903 ; double arriveBurst1003 ; double arriveBurst1103 ; double arriveBurst1203 ; double arriveBurst1303 ; double arriveBurst1403 ;
    double arriveBurst0104 ; double arriveBurst0204 ; double arriveBurst0304 ; double arriveBurst0404 ; double arriveBurst0504 ; double arriveBurst0604 ; double arriveBurst0704 ; //Destino 04 //Origen XX
    double arriveBurst0804 ; double arriveBurst0904 ; double arriveBurst1004 ; double arriveBurst1104 ; double arriveBurst1204 ; double arriveBurst1304 ; double arriveBurst1404 ;
    double arriveBurst0105 ; double arriveBurst0205 ; double arriveBurst0305 ; double arriveBurst0405 ; double arriveBurst0505 ; double arriveBurst0605 ; double arriveBurst0705 ; //Destino 05 //Origen XX
    double arriveBurst0805 ; double arriveBurst0905 ; double arriveBurst1005 ; double arriveBurst1105 ; double arriveBurst1205 ; double arriveBurst1305 ; double arriveBurst1405 ;
    double arriveBurst0106 ; double arriveBurst0206 ; double arriveBurst0306 ; double arriveBurst0406 ; double arriveBurst0506 ; double arriveBurst0606 ; double arriveBurst0706 ; //Destino 06 //Origen XX
    double arriveBurst0806 ; double arriveBurst0906 ; double arriveBurst1006 ; double arriveBurst1106 ; double arriveBurst1206 ; double arriveBurst1306 ; double arriveBurst1406 ;
    double arriveBurst0107 ; double arriveBurst0207 ; double arriveBurst0307 ; double arriveBurst0407 ; double arriveBurst0507 ; double arriveBurst0607 ; double arriveBurst0707 ; //Destino 07 //Origen XX
    double arriveBurst0807 ; double arriveBurst0907 ; double arriveBurst1007 ; double arriveBurst1107 ; double arriveBurst1207 ; double arriveBurst1307 ; double arriveBurst1407 ;
    double arriveBurst0108 ; double arriveBurst0208 ; double arriveBurst0308 ; double arriveBurst0408 ; double arriveBurst0508 ; double arriveBurst0608 ; double arriveBurst0708 ; //Destino 08 //Origen XX
    double arriveBurst0808 ; double arriveBurst0908 ; double arriveBurst1008 ; double arriveBurst1108 ; double arriveBurst1208 ; double arriveBurst1308 ; double arriveBurst1408 ;
    double arriveBurst0109 ; double arriveBurst0209 ; double arriveBurst0309 ; double arriveBurst0409 ; double arriveBurst0509 ; double arriveBurst0609 ; double arriveBurst0709 ; //Destino 09 //Origen XX
    double arriveBurst0809 ; double arriveBurst0909 ; double arriveBurst1009 ; double arriveBurst1109 ; double arriveBurst1209 ; double arriveBurst1309 ; double arriveBurst1409 ;
    double arriveBurst0110 ; double arriveBurst0210 ; double arriveBurst0310 ; double arriveBurst0410 ; double arriveBurst0510 ; double arriveBurst0610 ; double arriveBurst0710 ; //Destino 10 //Origen XX
    double arriveBurst0810 ; double arriveBurst0910 ; double arriveBurst1010 ; double arriveBurst1110 ; double arriveBurst1210 ; double arriveBurst1310 ; double arriveBurst1410 ;
    double arriveBurst0111 ; double arriveBurst0211 ; double arriveBurst0311 ; double arriveBurst0411 ; double arriveBurst0511 ; double arriveBurst0611 ; double arriveBurst0711 ; //Destino 11 //Origen XX
    double arriveBurst0811 ; double arriveBurst0911 ; double arriveBurst1011 ; double arriveBurst1111 ; double arriveBurst1211 ; double arriveBurst1311 ; double arriveBurst1411 ;
    double arriveBurst0112 ; double arriveBurst0212 ; double arriveBurst0312 ; double arriveBurst0412 ; double arriveBurst0512 ; double arriveBurst0612 ; double arriveBurst0712 ; //Destino 12 //Origen XX
    double arriveBurst0812 ; double arriveBurst0912 ; double arriveBurst1012 ; double arriveBurst1112 ; double arriveBurst1212 ; double arriveBurst1312 ; double arriveBurst1412 ;
    double arriveBurst0113 ; double arriveBurst0213 ; double arriveBurst0313 ; double arriveBurst0413 ; double arriveBurst0513 ; double arriveBurst0613 ; double arriveBurst0713 ; //Destino 13 //Origen XX
    double arriveBurst0813 ; double arriveBurst0913 ; double arriveBurst1013 ; double arriveBurst1113 ; double arriveBurst1213 ; double arriveBurst1313 ; double arriveBurst1413 ;
    double arriveBurst0114 ; double arriveBurst0214 ; double arriveBurst0314 ; double arriveBurst0414 ; double arriveBurst0514 ; double arriveBurst0614 ; double arriveBurst0714 ; //Destino 14 //Origen XX
    double arriveBurst0814 ; double arriveBurst0914 ; double arriveBurst1014 ; double arriveBurst1114 ; double arriveBurst1214 ; double arriveBurst1314 ; double arriveBurst1414 ;

    //variables para rafagas perdidas
    double dropBurst0101 ; double dropBurst0201 ; double dropBurst0301 ; double dropBurst0401 ; double dropBurst0501 ; double dropBurst0601 ; double dropBurst0701 ; //Destino 01 //Origen XX
    double dropBurst0801 ; double dropBurst0901 ; double dropBurst1001 ; double dropBurst1101 ; double dropBurst1201 ; double dropBurst1301 ; double dropBurst1401 ;
    double dropBurst0102 ; double dropBurst0202 ; double dropBurst0302 ; double dropBurst0402 ; double dropBurst0502 ; double dropBurst0602 ; double dropBurst0702 ; //Destino 02 //Origen XX
    double dropBurst0802 ; double dropBurst0902 ; double dropBurst1002 ; double dropBurst1102 ; double dropBurst1202 ; double dropBurst1302 ; double dropBurst1402 ;
    double dropBurst0103 ; double dropBurst0203 ; double dropBurst0303 ; double dropBurst0403 ; double dropBurst0503 ; double dropBurst0603 ; double dropBurst0703 ; //Destino 03 //Origen XX
    double dropBurst0803 ; double dropBurst0903 ; double dropBurst1003 ; double dropBurst1103 ; double dropBurst1203 ; double dropBurst1303 ; double dropBurst1403 ;
    double dropBurst0104 ; double dropBurst0204 ; double dropBurst0304 ; double dropBurst0404 ; double dropBurst0504 ; double dropBurst0604 ; double dropBurst0704 ; //Destino 04 //Origen XX
    double dropBurst0804 ; double dropBurst0904 ; double dropBurst1004 ; double dropBurst1104 ; double dropBurst1204 ; double dropBurst1304 ; double dropBurst1404 ;
    double dropBurst0105 ; double dropBurst0205 ; double dropBurst0305 ; double dropBurst0405 ; double dropBurst0505 ; double dropBurst0605 ; double dropBurst0705 ; //Destino 05 //Origen XX
    double dropBurst0805 ; double dropBurst0905 ; double dropBurst1005 ; double dropBurst1105 ; double dropBurst1205 ; double dropBurst1305 ; double dropBurst1405 ;
    double dropBurst0106 ; double dropBurst0206 ; double dropBurst0306 ; double dropBurst0406 ; double dropBurst0506 ; double dropBurst0606 ; double dropBurst0706 ; //Destino 06 //Origen XX
    double dropBurst0806 ; double dropBurst0906 ; double dropBurst1006 ; double dropBurst1106 ; double dropBurst1206 ; double dropBurst1306 ; double dropBurst1406 ;
    double dropBurst0107 ; double dropBurst0207 ; double dropBurst0307 ; double dropBurst0407 ; double dropBurst0507 ; double dropBurst0607 ; double dropBurst0707 ; //Destino 07 //Origen XX
    double dropBurst0807 ; double dropBurst0907 ; double dropBurst1007 ; double dropBurst1107 ; double dropBurst1207 ; double dropBurst1307 ; double dropBurst1407 ;
    double dropBurst0108 ; double dropBurst0208 ; double dropBurst0308 ; double dropBurst0408 ; double dropBurst0508 ; double dropBurst0608 ; double dropBurst0708 ; //Destino 08 //Origen XX
    double dropBurst0808 ; double dropBurst0908 ; double dropBurst1008 ; double dropBurst1108 ; double dropBurst1208 ; double dropBurst1308 ; double dropBurst1408 ;
    double dropBurst0109 ; double dropBurst0209 ; double dropBurst0309 ; double dropBurst0409 ; double dropBurst0509 ; double dropBurst0609 ; double dropBurst0709 ; //Destino 09 //Origen XX
    double dropBurst0809 ; double dropBurst0909 ; double dropBurst1009 ; double dropBurst1109 ; double dropBurst1209 ; double dropBurst1309 ; double dropBurst1409 ;
    double dropBurst0110 ; double dropBurst0210 ; double dropBurst0310 ; double dropBurst0410 ; double dropBurst0510 ; double dropBurst0610 ; double dropBurst0710 ; //Destino 10 //Origen XX
    double dropBurst0810 ; double dropBurst0910 ; double dropBurst1010 ; double dropBurst1110 ; double dropBurst1210 ; double dropBurst1310 ; double dropBurst1410 ;
    double dropBurst0111 ; double dropBurst0211 ; double dropBurst0311 ; double dropBurst0411 ; double dropBurst0511 ; double dropBurst0611 ; double dropBurst0711 ; //Destino 11 //Origen XX
    double dropBurst0811 ; double dropBurst0911 ; double dropBurst1011 ; double dropBurst1111 ; double dropBurst1211 ; double dropBurst1311 ; double dropBurst1411 ;
    double dropBurst0112 ; double dropBurst0212 ; double dropBurst0312 ; double dropBurst0412 ; double dropBurst0512 ; double dropBurst0612 ; double dropBurst0712 ; //Destino 12 //Origen XX
    double dropBurst0812 ; double dropBurst0912 ; double dropBurst1012 ; double dropBurst1112 ; double dropBurst1212 ; double dropBurst1312 ; double dropBurst1412 ;
    double dropBurst0113 ; double dropBurst0213 ; double dropBurst0313 ; double dropBurst0413 ; double dropBurst0513 ; double dropBurst0613 ; double dropBurst0713 ; //Destino 13 //Origen XX
    double dropBurst0813 ; double dropBurst0913 ; double dropBurst1013 ; double dropBurst1113 ; double dropBurst1213 ; double dropBurst1313 ; double dropBurst1413 ;
    double dropBurst0114 ; double dropBurst0214 ; double dropBurst0314 ; double dropBurst0414 ; double dropBurst0514 ; double dropBurst0614 ; double dropBurst0714 ; //Destino 14 //Origen XX
    double dropBurst0814 ; double dropBurst0914 ; double dropBurst1014 ; double dropBurst1114 ; double dropBurst1214 ; double dropBurst1314 ; double dropBurst1414 ;

    //variable para almacenar la probabilidad de bloqueo en cada enlace end to end
    double pb0101 ; double pb0201 ; double pb0301 ; double pb0401 ; double pb0501 ; double pb0601 ; double pb0701 ; //Destino 01 //Origen XX
    double pb0801 ; double pb0901 ; double pb1001 ; double pb1101 ; double pb1201 ; double pb1301 ; double pb1401 ;
    double pb0102 ; double pb0202 ; double pb0302 ; double pb0402 ; double pb0502 ; double pb0602 ; double pb0702 ; //Destino 02 //Origen XX
    double pb0802 ; double pb0902 ; double pb1002 ; double pb1102 ; double pb1202 ; double pb1302 ; double pb1402 ;
    double pb0103 ; double pb0203 ; double pb0303 ; double pb0403 ; double pb0503 ; double pb0603 ; double pb0703 ; //Destino 03 //Origen XX
    double pb0803 ; double pb0903 ; double pb1003 ; double pb1103 ; double pb1203 ; double pb1303 ; double pb1403 ;
    double pb0104 ; double pb0204 ; double pb0304 ; double pb0404 ; double pb0504 ; double pb0604 ; double pb0704 ; //Destino 04 //Origen XX
    double pb0804 ; double pb0904 ; double pb1004 ; double pb1104 ; double pb1204 ; double pb1304 ; double pb1404 ;
    double pb0105 ; double pb0205 ; double pb0305 ; double pb0405 ; double pb0505 ; double pb0605 ; double pb0705 ; //Destino 05 //Origen XX
    double pb0805 ; double pb0905 ; double pb1005 ; double pb1105 ; double pb1205 ; double pb1305 ; double pb1405 ;
    double pb0106 ; double pb0206 ; double pb0306 ; double pb0406 ; double pb0506 ; double pb0606 ; double pb0706 ; //Destino 06 //Origen XX
    double pb0806 ; double pb0906 ; double pb1006 ; double pb1106 ; double pb1206 ; double pb1306 ; double pb1406 ;
    double pb0107 ; double pb0207 ; double pb0307 ; double pb0407 ; double pb0507 ; double pb0607 ; double pb0707 ; //Destino 07 //Origen XX
    double pb0807 ; double pb0907 ; double pb1007 ; double pb1107 ; double pb1207 ; double pb1307 ; double pb1407 ;
    double pb0108 ; double pb0208 ; double pb0308 ; double pb0408 ; double pb0508 ; double pb0608 ; double pb0708 ; //Destino 08 //Origen XX
    double pb0808 ; double pb0908 ; double pb1008 ; double pb1108 ; double pb1208 ; double pb1308 ; double pb1408 ;
    double pb0109 ; double pb0209 ; double pb0309 ; double pb0409 ; double pb0509 ; double pb0609 ; double pb0709 ; //Destino 09 //Origen XX
    double pb0809 ; double pb0909 ; double pb1009 ; double pb1109 ; double pb1209 ; double pb1309 ; double pb1409 ;
    double pb0110 ; double pb0210 ; double pb0310 ; double pb0410 ; double pb0510 ; double pb0610 ; double pb0710 ; //Destino 10 //Origen XX
    double pb0810 ; double pb0910 ; double pb1010 ; double pb1110 ; double pb1210 ; double pb1310 ; double pb1410 ;
    double pb0111 ; double pb0211 ; double pb0311 ; double pb0411 ; double pb0511 ; double pb0611 ; double pb0711 ; //Destino 11 //Origen XX
    double pb0811 ; double pb0911 ; double pb1011 ; double pb1111 ; double pb1211 ; double pb1311 ; double pb1411 ;
    double pb0112 ; double pb0212 ; double pb0312 ; double pb0412 ; double pb0512 ; double pb0612 ; double pb0712 ; //Destino 12 //Origen XX
    double pb0812 ; double pb0912 ; double pb1012 ; double pb1112 ; double pb1212 ; double pb1312 ; double pb1412 ;
    double pb0113 ; double pb0213 ; double pb0313 ; double pb0413 ; double pb0513 ; double pb0613 ; double pb0713 ; //Destino 13 //Origen XX
    double pb0813 ; double pb0913 ; double pb1013 ; double pb1113 ; double pb1213 ; double pb1313 ; double pb1413 ;
    double pb0114 ; double pb0214 ; double pb0314 ; double pb0414 ; double pb0514 ; double pb0614 ; double pb0714 ; //Destino 14 //Origen XX
    double pb0814 ; double pb0914 ; double pb1014 ; double pb1114 ; double pb1214 ; double pb1314 ; double pb1414 ;

    //variable para almacenar la Cant. Raf. Totales o Generadas
    double BurstTotal0101 ; double BurstTotal0201 ; double BurstTotal0301 ; double BurstTotal0401 ; double BurstTotal0501 ; double BurstTotal0601 ; double BurstTotal0701 ; //Destino 01 //Origen XX
    double BurstTotal0801 ; double BurstTotal0901 ; double BurstTotal1001 ; double BurstTotal1101 ; double BurstTotal1201 ; double BurstTotal1301 ; double BurstTotal1401 ;
    double BurstTotal0102 ; double BurstTotal0202 ; double BurstTotal0302 ; double BurstTotal0402 ; double BurstTotal0502 ; double BurstTotal0602 ; double BurstTotal0702 ; //Destino 02 //Origen XX
    double BurstTotal0802 ; double BurstTotal0902 ; double BurstTotal1002 ; double BurstTotal1102 ; double BurstTotal1202 ; double BurstTotal1302 ; double BurstTotal1402 ;
    double BurstTotal0103 ; double BurstTotal0203 ; double BurstTotal0303 ; double BurstTotal0403 ; double BurstTotal0503 ; double BurstTotal0603 ; double BurstTotal0703 ; //Destino 03 //Origen XX
    double BurstTotal0803 ; double BurstTotal0903 ; double BurstTotal1003 ; double BurstTotal1103 ; double BurstTotal1203 ; double BurstTotal1303 ; double BurstTotal1403 ;
    double BurstTotal0104 ; double BurstTotal0204 ; double BurstTotal0304 ; double BurstTotal0404 ; double BurstTotal0504 ; double BurstTotal0604 ; double BurstTotal0704 ; //Destino 04 //Origen XX
    double BurstTotal0804 ; double BurstTotal0904 ; double BurstTotal1004 ; double BurstTotal1104 ; double BurstTotal1204 ; double BurstTotal1304 ; double BurstTotal1404 ;
    double BurstTotal0105 ; double BurstTotal0205 ; double BurstTotal0305 ; double BurstTotal0405 ; double BurstTotal0505 ; double BurstTotal0605 ; double BurstTotal0705 ; //Destino 05 //Origen XX
    double BurstTotal0805 ; double BurstTotal0905 ; double BurstTotal1005 ; double BurstTotal1105 ; double BurstTotal1205 ; double BurstTotal1305 ; double BurstTotal1405 ;
    double BurstTotal0106 ; double BurstTotal0206 ; double BurstTotal0306 ; double BurstTotal0406 ; double BurstTotal0506 ; double BurstTotal0606 ; double BurstTotal0706 ; //Destino 06 //Origen XX
    double BurstTotal0806 ; double BurstTotal0906 ; double BurstTotal1006 ; double BurstTotal1106 ; double BurstTotal1206 ; double BurstTotal1306 ; double BurstTotal1406 ;
    double BurstTotal0107 ; double BurstTotal0207 ; double BurstTotal0307 ; double BurstTotal0407 ; double BurstTotal0507 ; double BurstTotal0607 ; double BurstTotal0707 ; //Destino 07 //Origen XX
    double BurstTotal0807 ; double BurstTotal0907 ; double BurstTotal1007 ; double BurstTotal1107 ; double BurstTotal1207 ; double BurstTotal1307 ; double BurstTotal1407 ;
    double BurstTotal0108 ; double BurstTotal0208 ; double BurstTotal0308 ; double BurstTotal0408 ; double BurstTotal0508 ; double BurstTotal0608 ; double BurstTotal0708 ; //Destino 08 //Origen XX
    double BurstTotal0808 ; double BurstTotal0908 ; double BurstTotal1008 ; double BurstTotal1108 ; double BurstTotal1208 ; double BurstTotal1308 ; double BurstTotal1408 ;
    double BurstTotal0109 ; double BurstTotal0209 ; double BurstTotal0309 ; double BurstTotal0409 ; double BurstTotal0509 ; double BurstTotal0609 ; double BurstTotal0709 ; //Destino 09 //Origen XX
    double BurstTotal0809 ; double BurstTotal0909 ; double BurstTotal1009 ; double BurstTotal1109 ; double BurstTotal1209 ; double BurstTotal1309 ; double BurstTotal1409 ;
    double BurstTotal0110 ; double BurstTotal0210 ; double BurstTotal0310 ; double BurstTotal0410 ; double BurstTotal0510 ; double BurstTotal0610 ; double BurstTotal0710 ; //Destino 10 //Origen XX
    double BurstTotal0810 ; double BurstTotal0910 ; double BurstTotal1010 ; double BurstTotal1110 ; double BurstTotal1210 ; double BurstTotal1310 ; double BurstTotal1410 ;
    double BurstTotal0111 ; double BurstTotal0211 ; double BurstTotal0311 ; double BurstTotal0411 ; double BurstTotal0511 ; double BurstTotal0611 ; double BurstTotal0711 ; //Destino 11 //Origen XX
    double BurstTotal0811 ; double BurstTotal0911 ; double BurstTotal1011 ; double BurstTotal1111 ; double BurstTotal1211 ; double BurstTotal1311 ; double BurstTotal1411 ;
    double BurstTotal0112 ; double BurstTotal0212 ; double BurstTotal0312 ; double BurstTotal0412 ; double BurstTotal0512 ; double BurstTotal0612 ; double BurstTotal0712 ; //Destino 12 //Origen XX
    double BurstTotal0812 ; double BurstTotal0912 ; double BurstTotal1012 ; double BurstTotal1112 ; double BurstTotal1212 ; double BurstTotal1312 ; double BurstTotal1412 ;
    double BurstTotal0113 ; double BurstTotal0213 ; double BurstTotal0313 ; double BurstTotal0413 ; double BurstTotal0513 ; double BurstTotal0613 ; double BurstTotal0713 ; //Destino 13 //Origen XX
    double BurstTotal0813 ; double BurstTotal0913 ; double BurstTotal1013 ; double BurstTotal1113 ; double BurstTotal1213 ; double BurstTotal1313 ; double BurstTotal1413 ;
    double BurstTotal0114 ; double BurstTotal0214 ; double BurstTotal0314 ; double BurstTotal0414 ; double BurstTotal0514 ; double BurstTotal0614 ; double BurstTotal0714 ; //Destino 14 //Origen XX
    double BurstTotal0814 ; double BurstTotal0914 ; double BurstTotal1014 ; double BurstTotal1114 ; double BurstTotal1214 ; double BurstTotal1314 ; double BurstTotal1414 ;

    double BurstGeneratedXX01; double BurstGeneratedXX02; double BurstGeneratedXX03; double BurstGeneratedXX04; double BurstGeneratedXX05; double BurstGeneratedXX06; double BurstGeneratedXX07;
    double BurstGeneratedXX08; double BurstGeneratedXX09; double BurstGeneratedXX10; double BurstGeneratedXX11; double BurstGeneratedXX12; double BurstGeneratedXX13; double BurstGeneratedXX14;

    double BurstGenerated0101; double BurstGenerated0202; double BurstGenerated0303; double BurstGenerated0404; double BurstGenerated0505; double BurstGenerated0606; double BurstGenerated0707;
    double BurstGenerated0808; double BurstGenerated0909; double BurstGenerated1010; double BurstGenerated1111; double BurstGenerated1212; double BurstGenerated1313; double BurstGenerated1414;

    double BurstReceivedXX01; double BurstReceivedXX02; double BurstReceivedXX03; double BurstReceivedXX04; double BurstReceivedXX05; double BurstReceivedXX06; double BurstReceivedXX07;
    double BurstReceivedXX08; double BurstReceivedXX09; double BurstReceivedXX10; double BurstReceivedXX11; double BurstReceivedXX12; double BurstReceivedXX13; double BurstReceivedXX14;


    double dropBurst1;double dropBurst2;double dropBurst3;double dropBurst4;double dropBurst5;double dropBurst6;double dropBurst7;double dropBurst8;double dropBurst9;double dropBurst10;
    double dropBurst11;double dropBurst12;double dropBurst13;double dropBurst14;

    double BurstDropXX01; double BurstDropXX02; double BurstDropXX03; double BurstDropXX04; double BurstDropXX05; double BurstDropXX06; double BurstDropXX07;
    double BurstDropXX08; double BurstDropXX09; double BurstDropXX10; double BurstDropXX11; double BurstDropXX12; double BurstDropXX13; double BurstDropXX14;

    double PBXX01; double PBXX02; double PBXX03; double PBXX04; double PBXX05; double PBXX06; double PBXX07;
    double PBXX08; double PBXX09; double PBXX10; double PBXX11; double PBXX12; double PBXX13; double PBXX14;

    double pb1;double pb2;double pb3;double pb4;double pb5;double pb6;double pb7;double pb8;double pb9;double pb10;
    double pb11;double pb12;double pb13;double pb14;

    double porcentaje_p1; double porcentaje_p2;double porcentaje_p3;double porcentaje_p4;double porcentaje_p5;double porcentaje_p6;double porcentaje_p7;double porcentaje_p8;double porcentaje_p9;double porcentaje_p10;
    double porcentaje_p11;double porcentaje_p12;double porcentaje_p13;double porcentaje_p14;

    double BurstTotal1;double BurstTotal2;double BurstTotal3;double BurstTotal4;double BurstTotal5;double BurstTotal6;double BurstTotal7;double BurstTotal8;double BurstTotal9;double BurstTotal10;
    double BurstTotal11;double BurstTotal12;double BurstTotal13;double BurstTotal14;

    double arriveBurst1;double arriveBurst2;double arriveBurst3;double arriveBurst4;double arriveBurst5;double arriveBurst6;double arriveBurst7;double arriveBurst8;double arriveBurst9;double arriveBurst10;
    double arriveBurst11;double arriveBurst12;double arriveBurst13;double arriveBurst14;


    int sourceAddress; //direccion de origen de la rafaga
    int destAddress;   //direccion de destino de la rafaga
    int clase; //clase de servicio
    double ganancia0; double ganancia1; double ganancia2; double ganancia;
    double count0; double count1; double count2;  //contadores de rafagas por clase de servicio

    double pDelay;      //retardo de propagacion
    int numSaltos;
    double procesDelay; //retardo de procesamiento
    double OXCDelay;
    double tDelay;
    double delaySim;

      /* estadísticas */
      cOutVector VlistSize; //Vector del tañamo de la lista de ráfagas.

      int listSize;   //Tamaño de la lista de ráfagas.
      int recvBursts; //Contador de ráfagas recibidas.

      virtual void updateDisplay();

      //Variables para almacenar datos de retardo endToend
      cOutVector endToEndDelayVec;   //vector
      cStdDev eedStats;              //escalar

      list<Burst*> receivedBursts; //Cola de ráfagas recibidas.

      //Inicia las estructuras de datos y estadísticas.
      virtual void initialize();
      virtual void handleMessage(cMessage *msg);
      virtual void finish();
   public:
      //Limpia recvBurst.
      virtual ~EdgeNodeDisassembler();
};


#endif /* EDGENODEDISASSEMBLER_H_ */
