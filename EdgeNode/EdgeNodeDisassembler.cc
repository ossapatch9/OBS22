/*
 * EdgeNodeDisassembler.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */


#include "EdgeNodeDisassembler.h"

Define_Module(EdgeNodeDisassembler);


EdgeNodeDisassembler::~EdgeNodeDisassembler()
{
   //Limpia la cola de las ráfagas recibidas
   list<Burst*>::iterator iter_list;
   Burst *item;
   for(iter_list = receivedBursts.begin();iter_list != receivedBursts.end(); iter_list++){
      item = *iter_list;
      delete item;
   }
   receivedBursts.clear();
}


void EdgeNodeDisassembler::initialize()
{
   OXCDelay = 0.000010; //retardo que introduce un OXC, 10 uS aprox

   recvBursts = 0;

   listSize = 0;
   VlistSize.setName("listSize");

   endToEndDelayVec.setName("End-to-End Delay");
   eedStats.setName("End-to-End Delay");


//   WATCH(secuencia0101); WATCH(secuencia0201); WATCH(secuencia0301); WATCH(secuencia0401); WATCH(secuencia0501); WATCH(secuencia0601); WATCH(secuencia0701); //Destino 01) //Origen XX
//   WATCH(secuencia0801); WATCH(secuencia0901); WATCH(secuencia1001); WATCH(secuencia1101); WATCH(secuencia1201); WATCH(secuencia1301); WATCH(secuencia1401);
//   WATCH(secuencia0102); WATCH(secuencia0202); WATCH(secuencia0302); WATCH(secuencia0402); WATCH(secuencia0502); WATCH(secuencia0602); WATCH(secuencia0702); //Destino 02) //Origen XX
//   WATCH(secuencia0802); WATCH(secuencia0902); WATCH(secuencia1002); WATCH(secuencia1102); WATCH(secuencia1202); WATCH(secuencia1302); WATCH(secuencia1402);
//   WATCH(secuencia0103); WATCH(secuencia0203); WATCH(secuencia0303); WATCH(secuencia0403); WATCH(secuencia0503); WATCH(secuencia0603); WATCH(secuencia0703); //Destino 03) //Origen XX
//   WATCH(secuencia0803); WATCH(secuencia0903); WATCH(secuencia1003); WATCH(secuencia1103); WATCH(secuencia1203); WATCH(secuencia1303); WATCH(secuencia1403);
//   WATCH(secuencia0104); WATCH(secuencia0204); WATCH(secuencia0304); WATCH(secuencia0404); WATCH(secuencia0504); WATCH(secuencia0604); WATCH(secuencia0704); //Destino 04) //Origen XX
//   WATCH(secuencia0804); WATCH(secuencia0904); WATCH(secuencia1004); WATCH(secuencia1104); WATCH(secuencia1204); WATCH(secuencia1304); WATCH(secuencia1404);
//   WATCH(secuencia0105); WATCH(secuencia0205); WATCH(secuencia0305); WATCH(secuencia0405); WATCH(secuencia0505); WATCH(secuencia0605); WATCH(secuencia0705); //Destino 05) //Origen XX
//   WATCH(secuencia0805); WATCH(secuencia0905); WATCH(secuencia1005); WATCH(secuencia1105); WATCH(secuencia1205); WATCH(secuencia1305); WATCH(secuencia1405);
//   WATCH(secuencia0106); WATCH(secuencia0206); WATCH(secuencia0306); WATCH(secuencia0406); WATCH(secuencia0506); WATCH(secuencia0606); WATCH(secuencia0706); //Destino 06) //Origen XX
//   WATCH(secuencia0806); WATCH(secuencia0906); WATCH(secuencia1006); WATCH(secuencia1106); WATCH(secuencia1206); WATCH(secuencia1306); WATCH(secuencia1406);
//   WATCH(secuencia0107); WATCH(secuencia0207); WATCH(secuencia0307); WATCH(secuencia0407); WATCH(secuencia0507); WATCH(secuencia0607); WATCH(secuencia0707); //Destino 07) //Origen XX
//   WATCH(secuencia0807); WATCH(secuencia0907); WATCH(secuencia1007); WATCH(secuencia1107); WATCH(secuencia1207); WATCH(secuencia1307); WATCH(secuencia1407);
//   WATCH(secuencia0108); WATCH(secuencia0208); WATCH(secuencia0308); WATCH(secuencia0408); WATCH(secuencia0508); WATCH(secuencia0608); WATCH(secuencia0708); //Destino 08) //Origen XX
//   WATCH(secuencia0808); WATCH(secuencia0908); WATCH(secuencia1008); WATCH(secuencia1108); WATCH(secuencia1208); WATCH(secuencia1308); WATCH(secuencia1408);
//   WATCH(secuencia0109); WATCH(secuencia0209); WATCH(secuencia0309); WATCH(secuencia0409); WATCH(secuencia0509); WATCH(secuencia0609); WATCH(secuencia0709); //Destino 09) //Origen XX
//   WATCH(secuencia0809); WATCH(secuencia0909); WATCH(secuencia1009); WATCH(secuencia1109); WATCH(secuencia1209); WATCH(secuencia1309); WATCH(secuencia1409);
//   WATCH(secuencia0110); WATCH(secuencia0210); WATCH(secuencia0310); WATCH(secuencia0410); WATCH(secuencia0510); WATCH(secuencia0610); WATCH(secuencia0710); //Destino 10) //Origen XX
//   WATCH(secuencia0810); WATCH(secuencia0910); WATCH(secuencia1010); WATCH(secuencia1110); WATCH(secuencia1210); WATCH(secuencia1310); WATCH(secuencia1410);
//   WATCH(secuencia0111); WATCH(secuencia0211); WATCH(secuencia0311); WATCH(secuencia0411); WATCH(secuencia0511); WATCH(secuencia0611); WATCH(secuencia0711); //Destino 11) //Origen XX
//   WATCH(secuencia0811); WATCH(secuencia0911); WATCH(secuencia1011); WATCH(secuencia1111); WATCH(secuencia1211); WATCH(secuencia1311); WATCH(secuencia1411);
//   WATCH(secuencia0112); WATCH(secuencia0212); WATCH(secuencia0312); WATCH(secuencia0412); WATCH(secuencia0512); WATCH(secuencia0612); WATCH(secuencia0712); //Destino 12) //Origen XX
//   WATCH(secuencia0812); WATCH(secuencia0912); WATCH(secuencia1012); WATCH(secuencia1112); WATCH(secuencia1212); WATCH(secuencia1312); WATCH(secuencia1412);
//   WATCH(secuencia0113); WATCH(secuencia0213); WATCH(secuencia0313); WATCH(secuencia0413); WATCH(secuencia0513); WATCH(secuencia0613); WATCH(secuencia0713); //Destino 13) //Origen XX
//   WATCH(secuencia0813); WATCH(secuencia0913); WATCH(secuencia1013); WATCH(secuencia1113); WATCH(secuencia1213); WATCH(secuencia1313); WATCH(secuencia1413);
//   WATCH(secuencia0114); WATCH(secuencia0214); WATCH(secuencia0314); WATCH(secuencia0414); WATCH(secuencia0514); WATCH(secuencia0614); WATCH(secuencia0714); //Destino 14) //Origen XX
//   WATCH(secuencia0814); WATCH(secuencia0914); WATCH(secuencia1014); WATCH(secuencia1114); WATCH(secuencia1214); WATCH(secuencia1314); WATCH(secuencia1414);



   //inicializacion de variables para End To End Delay
   eed0101 = 0; eed0201 = 0; eed0301 = 0; eed0401 = 0; eed0501 = 0; eed0601 = 0; eed0701 = 0; //Destino 01 //Origen XX
   eed0801 = 0; eed0901 = 0; eed1001 = 0; eed1101 = 0; eed1201 = 0; eed1301 = 0; eed1401 = 0;
   eed0102 = 0; eed0202 = 0; eed0302 = 0; eed0402 = 0; eed0502 = 0; eed0602 = 0; eed0702 = 0; //Destino 02 //Origen XX
   eed0802 = 0; eed0902 = 0; eed1002 = 0; eed1102 = 0; eed1202 = 0; eed1302 = 0; eed1402 = 0;
   eed0103 = 0; eed0203 = 0; eed0303 = 0; eed0403 = 0; eed0503 = 0; eed0603 = 0; eed0703 = 0; //Destino 03 //Origen XX
   eed0803 = 0; eed0903 = 0; eed1003 = 0; eed1103 = 0; eed1203 = 0; eed1303 = 0; eed1403 = 0;
   eed0104 = 0; eed0204 = 0; eed0304 = 0; eed0404 = 0; eed0504 = 0; eed0604 = 0; eed0704 = 0; //Destino 04 //Origen XX
   eed0804 = 0; eed0904 = 0; eed1004 = 0; eed1104 = 0; eed1204 = 0; eed1304 = 0; eed1404 = 0;
   eed0105 = 0; eed0205 = 0; eed0305 = 0; eed0405 = 0; eed0505 = 0; eed0605 = 0; eed0705 = 0; //Destino 05 //Origen XX
   eed0805 = 0; eed0905 = 0; eed1005 = 0; eed1105 = 0; eed1205 = 0; eed1305 = 0; eed1405 = 0;
   eed0106 = 0; eed0206 = 0; eed0306 = 0; eed0406 = 0; eed0506 = 0; eed0606 = 0; eed0706 = 0; //Destino 06 //Origen XX
   eed0806 = 0; eed0906 = 0; eed1006 = 0; eed1106 = 0; eed1206 = 0; eed1306 = 0; eed1406 = 0;
   eed0107 = 0; eed0207 = 0; eed0307 = 0; eed0407 = 0; eed0507 = 0; eed0607 = 0; eed0707 = 0; //Destino 07 //Origen XX
   eed0807 = 0; eed0907 = 0; eed1007 = 0; eed1107 = 0; eed1207 = 0; eed1307 = 0; eed1407 = 0;
   eed0108 = 0; eed0208 = 0; eed0308 = 0; eed0408 = 0; eed0508 = 0; eed0608 = 0; eed0708 = 0; //Destino 08 //Origen XX
   eed0808 = 0; eed0908 = 0; eed1008 = 0; eed1108 = 0; eed1208 = 0; eed1308 = 0; eed1408 = 0;
   eed0109 = 0; eed0209 = 0; eed0309 = 0; eed0409 = 0; eed0509 = 0; eed0609 = 0; eed0709 = 0; //Destino 09 //Origen XX
   eed0809 = 0; eed0909 = 0; eed1009 = 0; eed1109 = 0; eed1209 = 0; eed1309 = 0; eed1409 = 0;
   eed0110 = 0; eed0210 = 0; eed0310 = 0; eed0410 = 0; eed0510 = 0; eed0610 = 0; eed0710 = 0; //Destino 10 //Origen XX
   eed0810 = 0; eed0910 = 0; eed1010 = 0; eed1110 = 0; eed1210 = 0; eed1310 = 0; eed1410 = 0;
   eed0111 = 0; eed0211 = 0; eed0311 = 0; eed0411 = 0; eed0511 = 0; eed0611 = 0; eed0711 = 0; //Destino 11 //Origen XX
   eed0811 = 0; eed0911 = 0; eed1011 = 0; eed1111 = 0; eed1211 = 0; eed1311 = 0; eed1411 = 0;
   eed0112 = 0; eed0212 = 0; eed0312 = 0; eed0412 = 0; eed0512 = 0; eed0612 = 0; eed0712 = 0; //Destino 12 //Origen XX
   eed0812 = 0; eed0912 = 0; eed1012 = 0; eed1112 = 0; eed1212 = 0; eed1312 = 0; eed1412 = 0;
   eed0113 = 0; eed0213 = 0; eed0313 = 0; eed0413 = 0; eed0513 = 0; eed0613 = 0; eed0713 = 0; //Destino 13 //Origen XX
   eed0813 = 0; eed0913 = 0; eed1013 = 0; eed1113 = 0; eed1213 = 0; eed1313 = 0; eed1413 = 0;
   eed0114 = 0; eed0214 = 0; eed0314 = 0; eed0414 = 0; eed0514 = 0; eed0614 = 0; eed0714 = 0; //Destino 14 //Origen XX
   eed0814 = 0; eed0914 = 0; eed1014 = 0; eed1114 = 0; eed1214 = 0; eed1314 = 0; eed1414 = 0;


   //inicializacion de variables para probabilidad de bloqueo
   count0101 = 0; count0201 = 0; count0301 = 0; count0401 = 0; count0501 = 0; count0601 = 0; count0701 = 0; //Destino 01 //Origen XX
   count0801 = 0; count0901 = 0; count1001 = 0; count1101 = 0; count1201 = 0; count1301 = 0; count1401 = 0;
   count0102 = 0; count0202 = 0; count0302 = 0; count0402 = 0; count0502 = 0; count0602 = 0; count0702 = 0; //Destino 02 //Origen XX
   count0802 = 0; count0902 = 0; count1002 = 0; count1102 = 0; count1202 = 0; count1302 = 0; count1402 = 0;
   count0103 = 0; count0203 = 0; count0303 = 0; count0403 = 0; count0503 = 0; count0603 = 0; count0703 = 0; //Destino 03 //Origen XX
   count0803 = 0; count0903 = 0; count1003 = 0; count1103 = 0; count1203 = 0; count1303 = 0; count1403 = 0;
   count0104 = 0; count0204 = 0; count0304 = 0; count0404 = 0; count0504 = 0; count0604 = 0; count0704 = 0; //Destino 04 //Origen XX
   count0804 = 0; count0904 = 0; count1004 = 0; count1104 = 0; count1204 = 0; count1304 = 0; count1404 = 0;
   count0105 = 0; count0205 = 0; count0305 = 0; count0405 = 0; count0505 = 0; count0605 = 0; count0705 = 0; //Destino 05 //Origen XX
   count0805 = 0; count0905 = 0; count1005 = 0; count1105 = 0; count1205 = 0; count1305 = 0; count1405 = 0;
   count0106 = 0; count0206 = 0; count0306 = 0; count0406 = 0; count0506 = 0; count0606 = 0; count0706 = 0; //Destino 06 //Origen XX
   count0806 = 0; count0906 = 0; count1006 = 0; count1106 = 0; count1206 = 0; count1306 = 0; count1406 = 0;
   count0107 = 0; count0207 = 0; count0307 = 0; count0407 = 0; count0507 = 0; count0607 = 0; count0707 = 0; //Destino 07 //Origen XX
   count0807 = 0; count0907 = 0; count1007 = 0; count1107 = 0; count1207 = 0; count1307 = 0; count1407 = 0;
   count0108 = 0; count0208 = 0; count0308 = 0; count0408 = 0; count0508 = 0; count0608 = 0; count0708 = 0; //Destino 08 //Origen XX
   count0808 = 0; count0908 = 0; count1008 = 0; count1108 = 0; count1208 = 0; count1308 = 0; count1408 = 0;
   count0109 = 0; count0209 = 0; count0309 = 0; count0409 = 0; count0509 = 0; count0609 = 0; count0709 = 0; //Destino 09 //Origen XX
   count0809 = 0; count0909 = 0; count1009 = 0; count1109 = 0; count1209 = 0; count1309 = 0; count1409 = 0;
   count0110 = 0; count0210 = 0; count0310 = 0; count0410 = 0; count0510 = 0; count0610 = 0; count0710 = 0; //Destino 10 //Origen XX
   count0810 = 0; count0910 = 0; count1010 = 0; count1110 = 0; count1210 = 0; count1310 = 0; count1410 = 0;
   count0111 = 0; count0211 = 0; count0311 = 0; count0411 = 0; count0511 = 0; count0611 = 0; count0711 = 0; //Destino 11 //Origen XX
   count0811 = 0; count0911 = 0; count1011 = 0; count1111 = 0; count1211 = 0; count1311 = 0; count1411 = 0;
   count0112 = 0; count0212 = 0; count0312 = 0; count0412 = 0; count0512 = 0; count0612 = 0; count0712 = 0; //Destino 12 //Origen XX
   count0812 = 0; count0912 = 0; count1012 = 0; count1112 = 0; count1212 = 0; count1312 = 0; count1412 = 0;
   count0113 = 0; count0213 = 0; count0313 = 0; count0413 = 0; count0513 = 0; count0613 = 0; count0713 = 0; //Destino 13 //Origen XX
   count0813 = 0; count0913 = 0; count1013 = 0; count1113 = 0; count1213 = 0; count1313 = 0; count1413 = 0;
   count0114 = 0; count0214 = 0; count0314 = 0; count0414 = 0; count0514 = 0; count0614 = 0; count0714 = 0; //Destino 14 //Origen XX
   count0814 = 0; count0914 = 0; count1014 = 0; count1114 = 0; count1214 = 0; count1314 = 0; count1414 = 0;


   arriveBurst0101 = 0.000000000001; arriveBurst0201 = 0.000000000001; arriveBurst0301 = 0.000000000001; arriveBurst0401 = 0.000000000001; arriveBurst0501 = 0.000000000001; arriveBurst0601 = 0.000000000001; arriveBurst0701 = 0.000000000001; //Destino 01 //Origen XX
   arriveBurst0801 = 0.000000000001; arriveBurst0901 = 0.000000000001; arriveBurst1001 = 0.000000000001; arriveBurst1101 = 0.000000000001; arriveBurst1201 = 0.000000000001; arriveBurst1301 = 0.000000000001; arriveBurst1401 = 0.000000000001;
   arriveBurst0102 = 0.000000000001; arriveBurst0202 = 0.000000000001; arriveBurst0302 = 0.000000000001; arriveBurst0402 = 0.000000000001; arriveBurst0502 = 0.000000000001; arriveBurst0602 = 0.000000000001; arriveBurst0702 = 0.000000000001; //Destino 02 //Origen XX
   arriveBurst0802 = 0.000000000001; arriveBurst0902 = 0.000000000001; arriveBurst1002 = 0.000000000001; arriveBurst1102 = 0.000000000001; arriveBurst1202 = 0.000000000001; arriveBurst1302 = 0.000000000001; arriveBurst1402 = 0.000000000001;
   arriveBurst0103 = 0.000000000001; arriveBurst0203 = 0.000000000001; arriveBurst0303 = 0.000000000001; arriveBurst0403 = 0.000000000001; arriveBurst0503 = 0.000000000001; arriveBurst0603 = 0.000000000001; arriveBurst0703 = 0.000000000001; //Destino 03 //Origen XX
   arriveBurst0803 = 0.000000000001; arriveBurst0903 = 0.000000000001; arriveBurst1003 = 0.000000000001; arriveBurst1103 = 0.000000000001; arriveBurst1203 = 0.000000000001; arriveBurst1303 = 0.000000000001; arriveBurst1403 = 0.000000000001;
   arriveBurst0104 = 0.000000000001; arriveBurst0204 = 0.000000000001; arriveBurst0304 = 0.000000000001; arriveBurst0404 = 0.000000000001; arriveBurst0504 = 0.000000000001; arriveBurst0604 = 0.000000000001; arriveBurst0704 = 0.000000000001; //Destino 04 //Origen XX
   arriveBurst0804 = 0.000000000001; arriveBurst0904 = 0.000000000001; arriveBurst1004 = 0.000000000001; arriveBurst1104 = 0.000000000001; arriveBurst1204 = 0.000000000001; arriveBurst1304 = 0.000000000001; arriveBurst1404 = 0.000000000001;
   arriveBurst0105 = 0.000000000001; arriveBurst0205 = 0.000000000001; arriveBurst0305 = 0.000000000001; arriveBurst0405 = 0.000000000001; arriveBurst0505 = 0.000000000001; arriveBurst0605 = 0.000000000001; arriveBurst0705 = 0.000000000001; //Destino 05 //Origen XX
   arriveBurst0805 = 0.000000000001; arriveBurst0905 = 0.000000000001; arriveBurst1005 = 0.000000000001; arriveBurst1105 = 0.000000000001; arriveBurst1205 = 0.000000000001; arriveBurst1305 = 0.000000000001; arriveBurst1405 = 0.000000000001;
   arriveBurst0106 = 0.000000000001; arriveBurst0206 = 0.000000000001; arriveBurst0306 = 0.000000000001; arriveBurst0406 = 0.000000000001; arriveBurst0506 = 0.000000000001; arriveBurst0606 = 0.000000000001; arriveBurst0706 = 0.000000000001; //Destino 06 //Origen XX
   arriveBurst0806 = 0.000000000001; arriveBurst0906 = 0.000000000001; arriveBurst1006 = 0.000000000001; arriveBurst1106 = 0.000000000001; arriveBurst1206 = 0.000000000001; arriveBurst1306 = 0.000000000001; arriveBurst1406 = 0.000000000001;
   arriveBurst0107 = 0.000000000001; arriveBurst0207 = 0.000000000001; arriveBurst0307 = 0.000000000001; arriveBurst0407 = 0.000000000001; arriveBurst0507 = 0.000000000001; arriveBurst0607 = 0.000000000001; arriveBurst0707 = 0.000000000001; //Destino 07 //Origen XX
   arriveBurst0807 = 0.000000000001; arriveBurst0907 = 0.000000000001; arriveBurst1007 = 0.000000000001; arriveBurst1107 = 0.000000000001; arriveBurst1207 = 0.000000000001; arriveBurst1307 = 0.000000000001; arriveBurst1407 = 0.000000000001;
   arriveBurst0108 = 0.000000000001; arriveBurst0208 = 0.000000000001; arriveBurst0308 = 0.000000000001; arriveBurst0408 = 0.000000000001; arriveBurst0508 = 0.000000000001; arriveBurst0608 = 0.000000000001; arriveBurst0708 = 0.000000000001; //Destino 08 //Origen XX
   arriveBurst0808 = 0.000000000001; arriveBurst0908 = 0.000000000001; arriveBurst1008 = 0.000000000001; arriveBurst1108 = 0.000000000001; arriveBurst1208 = 0.000000000001; arriveBurst1308 = 0.000000000001; arriveBurst1408 = 0.000000000001;
   arriveBurst0109 = 0.000000000001; arriveBurst0209 = 0.000000000001; arriveBurst0309 = 0.000000000001; arriveBurst0409 = 0.000000000001; arriveBurst0509 = 0.000000000001; arriveBurst0609 = 0.000000000001; arriveBurst0709 = 0.000000000001; //Destino 09 //Origen XX
   arriveBurst0809 = 0.000000000001; arriveBurst0909 = 0.000000000001; arriveBurst1009 = 0.000000000001; arriveBurst1109 = 0.000000000001; arriveBurst1209 = 0.000000000001; arriveBurst1309 = 0.000000000001; arriveBurst1409 = 0.000000000001;
   arriveBurst0110 = 0.000000000001; arriveBurst0210 = 0.000000000001; arriveBurst0310 = 0.000000000001; arriveBurst0410 = 0.000000000001; arriveBurst0510 = 0.000000000001; arriveBurst0610 = 0.000000000001; arriveBurst0710 = 0.000000000001; //Destino 10 //Origen XX
   arriveBurst0810 = 0.000000000001; arriveBurst0910 = 0.000000000001; arriveBurst1010 = 0.000000000001; arriveBurst1110 = 0.000000000001; arriveBurst1210 = 0.000000000001; arriveBurst1310 = 0.000000000001; arriveBurst1410 = 0.000000000001;
   arriveBurst0111 = 0.000000000001; arriveBurst0211 = 0.000000000001; arriveBurst0311 = 0.000000000001; arriveBurst0411 = 0.000000000001; arriveBurst0511 = 0.000000000001; arriveBurst0611 = 0.000000000001; arriveBurst0711 = 0.000000000001; //Destino 11 //Origen XX
   arriveBurst0811 = 0.000000000001; arriveBurst0911 = 0.000000000001; arriveBurst1011 = 0.000000000001; arriveBurst1111 = 0.000000000001; arriveBurst1211 = 0.000000000001; arriveBurst1311 = 0.000000000001; arriveBurst1411 = 0.000000000001;
   arriveBurst0112 = 0.000000000001; arriveBurst0212 = 0.000000000001; arriveBurst0312 = 0.000000000001; arriveBurst0412 = 0.000000000001; arriveBurst0512 = 0.000000000001; arriveBurst0612 = 0.000000000001; arriveBurst0712 = 0.000000000001; //Destino 12 //Origen XX
   arriveBurst0812 = 0.000000000001; arriveBurst0912 = 0.000000000001; arriveBurst1012 = 0.000000000001; arriveBurst1112 = 0.000000000001; arriveBurst1212 = 0.000000000001; arriveBurst1312 = 0.000000000001; arriveBurst1412 = 0.000000000001;
   arriveBurst0113 = 0.000000000001; arriveBurst0213 = 0.000000000001; arriveBurst0313 = 0.000000000001; arriveBurst0413 = 0.000000000001; arriveBurst0513 = 0.000000000001; arriveBurst0613 = 0.000000000001; arriveBurst0713 = 0.000000000001; //Destino 13 //Origen XX
   arriveBurst0813 = 0.000000000001; arriveBurst0913 = 0.000000000001; arriveBurst1013 = 0.000000000001; arriveBurst1113 = 0.000000000001; arriveBurst1213 = 0.000000000001; arriveBurst1313 = 0.000000000001; arriveBurst1413 = 0.000000000001;
   arriveBurst0114 = 0.000000000001; arriveBurst0214 = 0.000000000001; arriveBurst0314 = 0.000000000001; arriveBurst0414 = 0.000000000001; arriveBurst0514 = 0.000000000001; arriveBurst0614 = 0.000000000001; arriveBurst0714 = 0.000000000001; //Destino 14 //Origen XX
   arriveBurst0814 = 0.000000000001; arriveBurst0914 = 0.000000000001; arriveBurst1014 = 0.000000000001; arriveBurst1114 = 0.000000000001; arriveBurst1214 = 0.000000000001; arriveBurst1314 = 0.000000000001; arriveBurst1414 = 0.000000000001;


   //inicializacion de variables para rafagas perdidas
   dropBurst0101 = 0; dropBurst0201 = 0; dropBurst0301 = 0; dropBurst0401 = 0; dropBurst0501 = 0; dropBurst0601 = 0; dropBurst0701 = 0; //Destino 01 //Origen XX
   dropBurst0801 = 0; dropBurst0901 = 0; dropBurst1001 = 0; dropBurst1101 = 0; dropBurst1201 = 0; dropBurst1301 = 0; dropBurst1401 = 0;
   dropBurst0102 = 0; dropBurst0202 = 0; dropBurst0302 = 0; dropBurst0402 = 0; dropBurst0502 = 0; dropBurst0602 = 0; dropBurst0702 = 0; //Destino 02 //Origen XX
   dropBurst0802 = 0; dropBurst0902 = 0; dropBurst1002 = 0; dropBurst1102 = 0; dropBurst1202 = 0; dropBurst1302 = 0; dropBurst1402 = 0;
   dropBurst0103 = 0; dropBurst0203 = 0; dropBurst0303 = 0; dropBurst0403 = 0; dropBurst0503 = 0; dropBurst0603 = 0; dropBurst0703 = 0; //Destino 03 //Origen XX
   dropBurst0803 = 0; dropBurst0903 = 0; dropBurst1003 = 0; dropBurst1103 = 0; dropBurst1203 = 0; dropBurst1303 = 0; dropBurst1403 = 0;
   dropBurst0104 = 0; dropBurst0204 = 0; dropBurst0304 = 0; dropBurst0404 = 0; dropBurst0504 = 0; dropBurst0604 = 0; dropBurst0704 = 0; //Destino 04 //Origen XX
   dropBurst0804 = 0; dropBurst0904 = 0; dropBurst1004 = 0; dropBurst1104 = 0; dropBurst1204 = 0; dropBurst1304 = 0; dropBurst1404 = 0;
   dropBurst0105 = 0; dropBurst0205 = 0; dropBurst0305 = 0; dropBurst0405 = 0; dropBurst0505 = 0; dropBurst0605 = 0; dropBurst0705 = 0; //Destino 05 //Origen XX
   dropBurst0805 = 0; dropBurst0905 = 0; dropBurst1005 = 0; dropBurst1105 = 0; dropBurst1205 = 0; dropBurst1305 = 0; dropBurst1405 = 0;
   dropBurst0106 = 0; dropBurst0206 = 0; dropBurst0306 = 0; dropBurst0406 = 0; dropBurst0506 = 0; dropBurst0606 = 0; dropBurst0706 = 0; //Destino 06 //Origen XX
   dropBurst0806 = 0; dropBurst0906 = 0; dropBurst1006 = 0; dropBurst1106 = 0; dropBurst1206 = 0; dropBurst1306 = 0; dropBurst1406 = 0;
   dropBurst0107 = 0; dropBurst0207 = 0; dropBurst0307 = 0; dropBurst0407 = 0; dropBurst0507 = 0; dropBurst0607 = 0; dropBurst0707 = 0; //Destino 07 //Origen XX
   dropBurst0807 = 0; dropBurst0907 = 0; dropBurst1007 = 0; dropBurst1107 = 0; dropBurst1207 = 0; dropBurst1307 = 0; dropBurst1407 = 0;
   dropBurst0108 = 0; dropBurst0208 = 0; dropBurst0308 = 0; dropBurst0408 = 0; dropBurst0508 = 0; dropBurst0608 = 0; dropBurst0708 = 0; //Destino 08 //Origen XX
   dropBurst0808 = 0; dropBurst0908 = 0; dropBurst1008 = 0; dropBurst1108 = 0; dropBurst1208 = 0; dropBurst1308 = 0; dropBurst1408 = 0;
   dropBurst0109 = 0; dropBurst0209 = 0; dropBurst0309 = 0; dropBurst0409 = 0; dropBurst0509 = 0; dropBurst0609 = 0; dropBurst0709 = 0; //Destino 09 //Origen XX
   dropBurst0809 = 0; dropBurst0909 = 0; dropBurst1009 = 0; dropBurst1109 = 0; dropBurst1209 = 0; dropBurst1309 = 0; dropBurst1409 = 0;
   dropBurst0110 = 0; dropBurst0210 = 0; dropBurst0310 = 0; dropBurst0410 = 0; dropBurst0510 = 0; dropBurst0610 = 0; dropBurst0710 = 0; //Destino 10 //Origen XX
   dropBurst0810 = 0; dropBurst0910 = 0; dropBurst1010 = 0; dropBurst1110 = 0; dropBurst1210 = 0; dropBurst1310 = 0; dropBurst1410 = 0;
   dropBurst0111 = 0; dropBurst0211 = 0; dropBurst0311 = 0; dropBurst0411 = 0; dropBurst0511 = 0; dropBurst0611 = 0; dropBurst0711 = 0; //Destino 11 //Origen XX
   dropBurst0811 = 0; dropBurst0911 = 0; dropBurst1011 = 0; dropBurst1111 = 0; dropBurst1211 = 0; dropBurst1311 = 0; dropBurst1411 = 0;
   dropBurst0112 = 0; dropBurst0212 = 0; dropBurst0312 = 0; dropBurst0412 = 0; dropBurst0512 = 0; dropBurst0612 = 0; dropBurst0712 = 0; //Destino 12 //Origen XX
   dropBurst0812 = 0; dropBurst0912 = 0; dropBurst1012 = 0; dropBurst1112 = 0; dropBurst1212 = 0; dropBurst1312 = 0; dropBurst1412 = 0;
   dropBurst0113 = 0; dropBurst0213 = 0; dropBurst0313 = 0; dropBurst0413 = 0; dropBurst0513 = 0; dropBurst0613 = 0; dropBurst0713 = 0; //Destino 13 //Origen XX
   dropBurst0813 = 0; dropBurst0913 = 0; dropBurst1013 = 0; dropBurst1113 = 0; dropBurst1213 = 0; dropBurst1313 = 0; dropBurst1413 = 0;
   dropBurst0114 = 0; dropBurst0214 = 0; dropBurst0314 = 0; dropBurst0414 = 0; dropBurst0514 = 0; dropBurst0614 = 0; dropBurst0714 = 0; //Destino 14 //Origen XX
   dropBurst0814 = 0; dropBurst0914 = 0; dropBurst1014 = 0; dropBurst1114 = 0; dropBurst1214 = 0; dropBurst1314 = 0; dropBurst1414 = 0;


   count0 = 0;
   count1 = 0;
   count2 = 0;
   ganancia0 = 0; ganancia1 = 0; ganancia2 = 0; ganancia = 0;
}



void EdgeNodeDisassembler::handleMessage(cMessage *msg)
{
   if(dynamic_cast< Burst *> (msg) == NULL){ delete msg; return; } //El paquete de control de la ráfaga no debería pasar en este punto


   if(msg->getKind() == 1){ //Inicio de la ráfaga. Coloca este mensaje en la cola
      take(msg);//toma posesión
      Burst *recvBurst = check_and_cast < Burst*> (msg);

      receivedBursts.push_back(recvBurst);

      //Adiciona la ráfaga en el contador de ráfagas recibidas
      recvBursts++;

      updateDisplay(); //llama la funcion para mostar el numero de rafagas recibidas

      listSize++;
      VlistSize.record(listSize);

      //codigo nuevo para el calculo de los retardos

      //obtenemos la direccion de origen de la rafaga
      sourceAddress = recvBurst->getSourceAddress();
      //WATCH(sourceAddress);

      //obtenemos la direccion de destino de la rafaga
      destAddress = recvBurst->getDestAddress();
      //WATCH(destAddress);

      //obtenemos numero de saltos (numero de CoreNode por donde paso la rafaga) para obtener retardo de procesameinto
      numSaltos = recvBurst->getNumSaltos();
      //WATCH(numSaltos);


      //retardo simulado
      delaySim = (simTime().dbl() - msg->getCreationTime().dbl()); WATCH(delaySim);

      //codigo para calcular el retardo de procesamiento
      procesDelay = numSaltos*OXCDelay;
      //WATCH(procesDelay);

      //codigo para calcular retardo de transmision
      tDelay = 0.000011776;
      //WATCH(tDelay);


      //codigo para calcular el retardo de propagacion
      if      (destAddress == 1   && sourceAddress == 1)   { pDelay = 0; eed0101 = eed0101 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 2)   { pDelay = 0.003776667; eed0201 = eed0201 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 3)   { pDelay = 0.005716667; eed0301 = eed0301 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 4)   { pDelay = 0.007093333; eed0401 = eed0401 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 5)   { pDelay = 0.00899; eed0501 = eed0501 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 6)   { pDelay = 0.0127; eed0601 = eed0601 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 7)   { pDelay = 0.011846667; eed0701 = eed0701 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 8)   { pDelay = 0.009443333; eed0801 = eed0801 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 9)   { pDelay = 0.01176; eed0901 = eed0901 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 10)  { pDelay = 0.014926667; eed1001 = eed1001 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 11)  { pDelay = 0.013263333; eed1101 = eed1101 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 12)  { pDelay = 0.019276667; eed1201 = eed1201 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 13)  { pDelay = 0.00693; eed1301 = eed1301 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 1   && sourceAddress == 14)  { pDelay = 0.014343333; eed1401 = eed1401 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 2   && sourceAddress == 1)   { pDelay = 0.003776667; eed0102 = eed0102 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 2)   { pDelay = 0; eed0202 = eed0202 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 3)   { pDelay = 0.002333333; eed0302 = eed0302 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 4)   { pDelay = 0.003316667; eed0402 = eed0402 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 5)   { pDelay = 0.005213333; eed0502 = eed0502 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 6)   { pDelay = 0.009316667; eed0602 = eed0602 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 7)   { pDelay = 0.007713333; eed0702 = eed0702 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 8)   { pDelay = 0.01322; eed0802 = eed0802 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 9)   { pDelay = 0.015536667; eed0902 = eed0902 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 10)  { pDelay = 0.01115; eed1002 = eed1002 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 11)  { pDelay = 0.01378; eed1102 = eed1102 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 12)  { pDelay = 0.014496667; eed1202 = eed1202 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 13)  { pDelay = 0.01308; eed1302 = eed1302 + delaySim + pDelay + procesDelay + tDelay;}
      else if (destAddress == 2   && sourceAddress == 14)  { pDelay = 0.01313; eed1402 = eed1402 + delaySim + pDelay + procesDelay + tDelay;}

      if      (destAddress == 3   && sourceAddress == 1)   { pDelay = 0.005716667; eed0103 = eed0103 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 2)   { pDelay = 0.002333333; eed0203 = eed0203 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 3)   { pDelay = 0; eed0303 = eed0303 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 4)   { pDelay = 0.00565; eed0403 = eed0403 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 5)   { pDelay = 0.011823333; eed0503 = eed0503 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 6)   { pDelay = 0.006983333; eed0603 = eed0603 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 7)   { pDelay = 0.014323333; eed0703 = eed0703 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 8)   { pDelay = 0.01516; eed0803 = eed0803 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 9)   { pDelay = 0.013543333; eed0903 = eed0903 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 10)  { pDelay = 0.013483333; eed1003 = eed1003 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 11)  { pDelay = 0.01438; eed1103 = eed1103 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 12)  { pDelay = 0.01356; eed1203 = eed1203 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 13)  { pDelay = 0.010746667; eed1303 = eed1303 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 3   && sourceAddress == 14)  { pDelay = 0.014926667; eed1403 = eed1403 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 4   && sourceAddress == 1)   { pDelay = 0.007093333; eed0104 = eed0104 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 2)   { pDelay = 0.003316667; eed0204 = eed0204 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 3)   { pDelay = 0.00565; eed0304 = eed0304 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 4)   { pDelay = 0; eed0404 = eed0404 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 5)   { pDelay = 0.001896667; eed0504 = eed0504 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 6)   { pDelay = 0.006736667; eed0604 = eed0604 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 7)   { pDelay = 0.004396667; eed0704 = eed0704 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 8)   { pDelay = 0.0068; eed0804 = eed0804 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 9)   { pDelay = 0.011966667; eed0904 = eed0904 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 10)  { pDelay = 0.007833333; eed1004 = eed1004 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 11)  { pDelay = 0.010463333; eed1104 = eed1104 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 12)  { pDelay = 0.01118; eed1204 = eed1204 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 13)  { pDelay = 0.0105; eed1304 = eed1304 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 4   && sourceAddress == 14)  { pDelay = 0.009813333; eed1404 = eed1404 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 5   && sourceAddress == 1)   { pDelay = 0.00899; eed0105 = eed0105 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 2)   { pDelay = 0.005213333; eed0205 = eed0205 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 3)   { pDelay = 0.011823333; eed0305 = eed0305 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 4)   { pDelay = 0.001896667; eed0405 = eed0405 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 5)   { pDelay = 0; eed0505 = eed0505 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 6)   { pDelay = 0.00484; eed0605 = eed0605 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 7)   { pDelay = 0.0025; eed0705 = eed0705 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 8)   { pDelay = 0.004903333; eed0805 = eed0805 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 9)   { pDelay = 0.00722; eed0905 = eed0905 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 10)  { pDelay = 0.00973; eed1005 = eed1005 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 11)  { pDelay = 0.010463333; eed1105 = eed1105 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 12)  { pDelay = 0.011416667; eed1205 = eed1205 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 13)  { pDelay = 0.008603333; eed1305 = eed1305 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 5   && sourceAddress == 14)  { pDelay = 0.01171; eed1405 = eed1405 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 6   && sourceAddress == 1)   { pDelay = 0.013093333; eed0106 = eed0106 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 2)   { pDelay = 0.009316667; eed0206 = eed0206 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 3)   { pDelay = 0.006983333; eed0306 = eed0306 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 4)   { pDelay = 0.006736667; eed0406 = eed0406 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 5)   { pDelay = 0.00484; eed0506 = eed0506 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 6)   { pDelay = 0; eed0606 = eed0606 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 7)   { pDelay = 0.00734; eed0706 = eed0706 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 8)   { pDelay = 0.008876667; eed0806 = eed0806 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 9)   { pDelay = 0.00656; eed0906 = eed0906 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 10)  { pDelay = 0.009923333; eed1006 = eed1006 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 11)  { pDelay = 0.007396667; eed1106 = eed1106 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 12)  { pDelay = 0.006576667; eed1206 = eed1206 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 13)  { pDelay = 0.003763333; eed1306 = eed1306 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 6   && sourceAddress == 14)  { pDelay = 0.007943333; eed1406 = eed1406 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 7   && sourceAddress == 1)   { pDelay = 0.011846667; eed0107 = eed0107 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 2)   { pDelay = 0.007713333; eed0207 = eed0207 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 3)   { pDelay = 0.014323333; eed0307 = eed0307 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 4)   { pDelay = 0.004396667; eed0407 = eed0407 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 5)   { pDelay = 0.0025; eed0507 = eed0507 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 6)   { pDelay = 0.00734; eed0607 = eed0607 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 7)   { pDelay = 0; eed0707 = eed0707 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 8)   { pDelay = 0.002403333; eed0807 = eed0807 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 9)   { pDelay = 0.00472; eed0907 = eed0907 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 10)  { pDelay = 0.01223; eed1007 = eed1007 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 11)  { pDelay = 0.006223333; eed1107 = eed1107 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 12)  { pDelay = 0.013916667; eed1207 = eed1207 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 13)  { pDelay = 0.007516667; eed1307 = eed1307 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 7   && sourceAddress == 14)  { pDelay = 0.007303333; eed1407 = eed1407 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 8   && sourceAddress == 1)   { pDelay = 0.009443333; eed0108 = eed0108 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 2)   { pDelay = 0.01322; eed0208 = eed0208 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 3)   { pDelay = 0.01516; eed0308 = eed0308 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 4)   { pDelay = 0.0068; eed0408 = eed0408 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 5)   { pDelay = 0.004903333; eed0508 = eed0508 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 6)   { pDelay = 0.008876667; eed0608 = eed0608 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 7)   { pDelay = 0.002403333; eed0708 = eed0708 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 8)   { pDelay = 0; eed0808 = eed0808 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 9)   { pDelay = 0.002316667; eed0908 = eed0908 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 10)  { pDelay = 0.00645; eed1008 = eed1008 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 11)  { pDelay = 0.00382; eed1108 = eed1108 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 12)  { pDelay = 0.00464; eed1208 = eed1208 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 13)  { pDelay = 0.005113333; eed1308 = eed1308 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 8   && sourceAddress == 14)  { pDelay = 0.0049; eed1408 = eed1408 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 9   && sourceAddress == 1)   { pDelay = 0.01176; eed0109 = eed0109 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 2)   { pDelay = 0.015536667; eed0209 = eed0209 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 3)   { pDelay = 0.013543333; eed0309 = eed0309 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 4)   { pDelay = 0.011966667; eed0409 = eed0409 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 5)   { pDelay = 0.00722; eed0509 = eed0509 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 6)   { pDelay = 0.00656; eed0609 = eed0609 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 7)   { pDelay = 0.00472; eed0709 = eed0709 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 8)   { pDelay = 0.002316667; eed0809 = eed0809 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 9)   { pDelay = 0; eed0909 = eed0909 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 10)  { pDelay = 0.004133333; eed1009 = eed1009 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 11)  { pDelay = 0.001503333; eed1109 = eed1109 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 12)  { pDelay = 0.002323333; eed1209 = eed1209 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 13)  { pDelay = 0.002796667; eed1309 = eed1309 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 9   && sourceAddress == 14)  { pDelay = 0.002583333; eed1409 = eed1409 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 10   && sourceAddress == 1)   { pDelay = 0.014926667; eed0110 = eed0110 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 2)   { pDelay = 0.01115; eed0210 = eed0210 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 3)   { pDelay = 0.013483333; eed0310 = eed0310 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 4)   { pDelay = 0.007833333; eed0410 = eed0410 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 5)   { pDelay = 0.00973; eed0510 = eed0510 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 6)   { pDelay = 0.010026667; eed0610 = eed0610 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 7)   { pDelay = 0.01223; eed0710 = eed0710 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 8)   { pDelay = 0.00645; eed0810 = eed0810 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 9)   { pDelay = 0.004133333; eed0910 = eed0910 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 10)  { pDelay = 0; eed1010 = eed1010 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 11)  { pDelay = 0.00263; eed1110 = eed1110 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 12)  { pDelay = 0.003346667; eed1210 = eed1210 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 13)  { pDelay = 0.00693; eed1310 = eed1310 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 10   && sourceAddress == 14)  { pDelay = 0.00198; eed1410 = eed1410 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 11   && sourceAddress == 1)   { pDelay = 0.013263333; eed0111 = eed0111 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 2)   { pDelay = 0.016713333; eed0211 = eed0211 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 3)   { pDelay = 0.01438; eed0311 = eed0311 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 4)   { pDelay = 0.010463333; eed0411 = eed0411 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 5)   { pDelay = 0.012236667; eed0511 = eed0511 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 6)   { pDelay = 0.007396667; eed0611 = eed0611 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 7)   { pDelay = 0.006223333; eed0711 = eed0711 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 8)   { pDelay = 0.00382; eed0811 = eed0811 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 9)   { pDelay = 0.001503333; eed0911 = eed0911 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 10)  { pDelay = 0.00263; eed1011 = eed1011 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 11)  { pDelay = 0; eed1111 = eed1111 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 12)  { pDelay = 0.00082; eed1211 = eed1211 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 13)  { pDelay = 0.0043; eed1311 = eed1311 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 11   && sourceAddress == 14)  { pDelay = 0.004086667; eed1411 = eed1411 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 12   && sourceAddress == 1)   { pDelay = 0.019276667; eed0112 = eed0112 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 2)   { pDelay = 0.015893333; eed0212 = eed0212 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 3)   { pDelay = 0.01356; eed0312 = eed0312 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 4)   { pDelay = 0.013313333; eed0412 = eed0412 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 5)   { pDelay = 0.011416667; eed0512 = eed0512 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 6)   { pDelay = 0.006576667; eed0612 = eed0612 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 7)   { pDelay = 0.013916667; eed0712 = eed0712 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 8)   { pDelay = 0.00464; eed0812 = eed0812 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 9)   { pDelay = 0.002323333; eed0912 = eed0912 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 10)  { pDelay = 0.003346667; eed1012 = eed1012 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 11)  { pDelay = 0.00082; eed1112 = eed1112 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 12)  { pDelay = 0; eed1212 = eed1212 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 13)  { pDelay = 0.01034; eed1312 = eed1312 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 12   && sourceAddress == 14)  { pDelay = 0.001366667; eed1412 = eed1412 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 13   && sourceAddress == 1)   { pDelay = 0.014556667; eed0113 = eed0113 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 2)   { pDelay = 0.01308; eed0213 = eed0213 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 3)   { pDelay = 0.010746667; eed0313 = eed0313 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 4)   { pDelay = 0.0105; eed0413 = eed0413 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 5)   { pDelay = 0.008603333; eed0513 = eed0513 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 6)   { pDelay = 0.003763333; eed0613 = eed0613 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 7)   { pDelay = 0.007516667; eed0713 = eed0713 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 8)   { pDelay = 0.005113333; eed0813 = eed0813 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 9)   { pDelay = 0.002796667; eed0913 = eed0913 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 10)  { pDelay = 0.00736; eed1013 = eed1013 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 11)  { pDelay = 0.0043; eed1113 = eed1113 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 12)  { pDelay = 0.01034; eed1213 = eed1213 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 13)  { pDelay = 0; eed1313 = eed1313 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 13   && sourceAddress == 14)  { pDelay = 0.00538; eed1413 = eed1413 + delaySim + pDelay + procesDelay + tDelay; }

      if      (destAddress == 14   && sourceAddress == 1)   { pDelay = 0.014343333; eed0114 = eed0114 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 2)   { pDelay = 0.01313; eed0214 = eed0214 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 3)   { pDelay = 0.00835; eed0314 = eed0314 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 4)   { pDelay = 0.009813333; eed0414 = eed0414 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 5)   { pDelay = 0.01171; eed0514 = eed0514 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 6)   { pDelay = 0.007943333; eed0614 = eed0614 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 7)   { pDelay = 0.007303333; eed0714 = eed0714 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 8)   { pDelay = 0.0049; eed0814 = eed0814 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 9)   { pDelay = 0.002583333; eed0914 = eed0914 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 10)  { pDelay = 0.00198; eed1014 = eed1014 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 11)  { pDelay = 0.002186667; eed1114 = eed1114 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 12)  { pDelay = 0.001366667; eed1214 = eed1214 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 13)  { pDelay = 0.00538; eed1314 = eed1314 + delaySim + pDelay + procesDelay + tDelay; }
      else if (destAddress == 14   && sourceAddress == 14)  { pDelay = 0; eed1414 = eed1414 + delaySim + pDelay + procesDelay + tDelay; }




      //codigo para calcular el retardo extremo a extremo de la rafaga
       simtime_t eed = (simTime() - msg->getCreationTime()) + pDelay + procesDelay + tDelay;
       endToEndDelayVec.record(eed);
       eedStats.collect(eed);


       //============================== #============================== #==============================
             //codigo para probabilidad de bloqueo de rafagas
       //============================== #============================== #==============================
             //   if   (destAddress == 1  && sourceAddress == 1)  {secuencia0101 = recvBurst->getSecuencia(); count0101++; arriveBurst0101++; WATCH(arriveBurst0101);
             //   if   (count0101 == secuencia0101){dropBurst0101 = dropBurst0101; pb0101 = (dropBurst0101/(BurstTotal0101=(arriveBurst0101 + dropBurst0101)))*100; WATCH(pb0101);}
             //   else {dropBurst0101 = dropBurst0101 + (secuencia0101 - count0101); WATCH(dropBurst0101); count0101 = secuencia0101; pb0101 = (dropBurst0101/(arriveBurst0101 + dropBurst0101))*100; WATCH(pb0101);} }
              if        (destAddress == 1  && sourceAddress == 2)  {secuencia0201 = recvBurst->getSecuencia(); count0201++; arriveBurst0201++; WATCH(arriveBurst0201);
                   if   (count0201 == secuencia0201){dropBurst0201 = dropBurst0201; pb0201 = (dropBurst0201/(arriveBurst0201 + dropBurst0201))*100; WATCH(pb0201);}
                   else {dropBurst0201 = dropBurst0201 + (secuencia0201 - count0201); WATCH(dropBurst0201); count0201 = secuencia0201; pb0201 = (dropBurst0201/(arriveBurst0201 + dropBurst0201))*100; WATCH(pb0201);} }
              else if   (destAddress == 1  && sourceAddress == 3)  {secuencia0301 = recvBurst->getSecuencia(); count0301++; arriveBurst0301++; WATCH(arriveBurst0301);
                   if   (count0301 == secuencia0301){dropBurst0301 = dropBurst0301; pb0301 = (dropBurst0301/(arriveBurst0301 + dropBurst0301))*100; WATCH(pb0301);}
                   else {dropBurst0301 = dropBurst0301 + (secuencia0301 - count0301); WATCH(dropBurst0301); count0301 = secuencia0301; pb0301 = (dropBurst0301/(arriveBurst0301 + dropBurst0301))*100; WATCH(pb0301);} }
              else if   (destAddress == 1  && sourceAddress == 4)  {secuencia0401 = recvBurst->getSecuencia(); count0401++; arriveBurst0401++; WATCH(arriveBurst0401);
                   if   (count0401 == secuencia0401){dropBurst0401 = dropBurst0401; pb0401 = (dropBurst0401/(arriveBurst0401 + dropBurst0401))*100; WATCH(pb0401);}
                   else {dropBurst0401 = dropBurst0401 + (secuencia0401 - count0401); WATCH(dropBurst0401); count0401 = secuencia0401; pb0401 = (dropBurst0401/(arriveBurst0401 + dropBurst0401))*100; WATCH(pb0401);} }
              else if   (destAddress == 1  && sourceAddress == 5)  {secuencia0501 = recvBurst->getSecuencia(); count0501++; arriveBurst0501++; WATCH(arriveBurst0501);
                   if   (count0501 == secuencia0501){dropBurst0501 = dropBurst0501; pb0501 = (dropBurst0501/(arriveBurst0501 + dropBurst0501))*100; WATCH(pb0501);}
                   else {dropBurst0501 = dropBurst0501 + (secuencia0501 - count0501); WATCH(dropBurst0501); count0501 = secuencia0501; pb0501 = (dropBurst0501/(arriveBurst0501 + dropBurst0501))*100; WATCH(pb0501);} }
              else if   (destAddress == 1  && sourceAddress == 6)  {secuencia0601 = recvBurst->getSecuencia(); count0601++; arriveBurst0601++; WATCH(arriveBurst0601);
                   if   (count0601 == secuencia0601){dropBurst0601 = dropBurst0601; pb0601 = (dropBurst0601/(arriveBurst0601 + dropBurst0601))*100; WATCH(pb0601);}
                   else {dropBurst0601 = dropBurst0601 + (secuencia0601 - count0601); WATCH(dropBurst0601); count0601 = secuencia0601; pb0601 = (dropBurst0601/(arriveBurst0601 + dropBurst0601))*100; WATCH(pb0601);} }
              else if   (destAddress == 1  && sourceAddress == 7)  {secuencia0701 = recvBurst->getSecuencia(); count0701++; arriveBurst0701++; WATCH(arriveBurst0701);
                   if   (count0701 == secuencia0701){dropBurst0701 = dropBurst0701; pb0701 = (dropBurst0701/(arriveBurst0701 + dropBurst0701))*100; WATCH(pb0701);}
                   else {dropBurst0701 = dropBurst0701 + (secuencia0701 - count0701); WATCH(dropBurst0701); count0701 = secuencia0701; pb0701 = (dropBurst0701/(arriveBurst0701 + dropBurst0701))*100; WATCH(pb0701);} }
              else if   (destAddress == 1  && sourceAddress == 8)  {secuencia0801 = recvBurst->getSecuencia(); count0801++; arriveBurst0801++; WATCH(arriveBurst0801);
                   if   (count0801 == secuencia0801){dropBurst0801 = dropBurst0801; pb0801 = (dropBurst0801/(arriveBurst0801 + dropBurst0801))*100; WATCH(pb0801);}
                   else {dropBurst0801 = dropBurst0801 + (secuencia0801 - count0801); WATCH(dropBurst0801); count0801 = secuencia0801; pb0801 = (dropBurst0801/(arriveBurst0801 + dropBurst0801))*100; WATCH(pb0801);} }
              else if   (destAddress == 1  && sourceAddress == 9)  {secuencia0901 = recvBurst->getSecuencia(); count0901++; arriveBurst0901++; WATCH(arriveBurst0901);
                   if   (count0901 == secuencia0901){dropBurst0901 = dropBurst0901; pb0901 = (dropBurst0901/(arriveBurst0901 + dropBurst0901))*100; WATCH(pb0901);}
                   else {dropBurst0901 = dropBurst0901 + (secuencia0901 - count0901); WATCH(dropBurst0901); count0901 = secuencia0901; pb0901 = (dropBurst0901/(arriveBurst0901 + dropBurst0901))*100; WATCH(pb0901);} }
              else if   (destAddress == 1  && sourceAddress == 10) {secuencia1001 = recvBurst->getSecuencia(); count1001++; arriveBurst1001++; WATCH(arriveBurst1001);
                   if   (count1001 == secuencia1001){dropBurst1001 = dropBurst1001; pb1001 = (dropBurst1001/(arriveBurst1001 + dropBurst1001))*100; WATCH(pb1001);}
                   else {dropBurst1001 = dropBurst1001 + (secuencia1001 - count1001); WATCH(dropBurst1001); count1001 = secuencia1001; pb1001 = (dropBurst1001/(arriveBurst1001 + dropBurst1001))*100; WATCH(pb1001);} }
              else if   (destAddress == 1  && sourceAddress == 11) {secuencia1101 = recvBurst->getSecuencia(); count1101++; arriveBurst1101++; WATCH(arriveBurst1101);
                   if   (count1101 == secuencia1101){dropBurst1101 = dropBurst1101; pb1101 = (dropBurst1101/(arriveBurst1101 + dropBurst1101))*100; WATCH(pb1101);}
                   else {dropBurst1101 = dropBurst1101 + (secuencia1101 - count1101); WATCH(dropBurst1101); count1101 = secuencia1101; pb1101 = (dropBurst1101/(arriveBurst1101 + dropBurst1101))*100; WATCH(pb1101);} }
              else if   (destAddress == 1  && sourceAddress == 12) {secuencia1201 = recvBurst->getSecuencia(); count1201++; arriveBurst1201++; WATCH(arriveBurst1201);
                   if   (count1201 == secuencia1201){dropBurst1201 = dropBurst1201; pb1201 = (dropBurst1201/(arriveBurst1201 + dropBurst1201))*100; WATCH(pb1201);}
                   else {dropBurst1201 = dropBurst1201 + (secuencia1201 - count1201); WATCH(dropBurst1201); count1201 = secuencia1201; pb1201 = (dropBurst1201/(arriveBurst1201 + dropBurst1201))*100; WATCH(pb1201);} }
              else if   (destAddress == 1  && sourceAddress == 13) {secuencia1301 = recvBurst->getSecuencia(); count1301++; arriveBurst1301++; WATCH(arriveBurst1301);
                   if   (count1301 == secuencia1301){dropBurst1301 = dropBurst1301; pb1301 = (dropBurst1301/(arriveBurst1301 + dropBurst1301))*100; WATCH(pb1301);}
                   else {dropBurst1301 = dropBurst1301 + (secuencia1301 - count1301); WATCH(dropBurst1301); count1301 = secuencia1301; pb1301 = (dropBurst1301/(arriveBurst1301 + dropBurst1301))*100; WATCH(pb1301);} }
              else if   (destAddress == 1  && sourceAddress == 14) {secuencia1401 = recvBurst->getSecuencia(); count1401++; arriveBurst1401++; WATCH(arriveBurst1401);
                   if   (count1401 == secuencia1401){dropBurst1401 = dropBurst1401; pb1401 = (dropBurst1401/(arriveBurst1401 + dropBurst1401))*100; WATCH(pb1401);}
                   else {dropBurst1401 = dropBurst1401 + (secuencia1401 - count1401); WATCH(dropBurst1401); count1401 = secuencia1401; pb1401 = (dropBurst1401/(arriveBurst1401 + dropBurst1401))*100; WATCH(pb1401);} }


             //   if   (destAddress == 2  && sourceAddress == 2)  {secuencia0202 = recvBurst->getSecuencia(); count0202++; arriveBurst0202++; WATCH(arriveBurst0202);
             //   if   (count0202 == secuencia0202){dropBurst0202 = dropBurst0202; pb0202 = (dropBurst0202/(arriveBurst0202 + dropBurst0202))*100; WATCH(pb0202);}
             //   else {dropBurst0202 = dropBurst0202 + (secuencia0202 - count0202); WATCH(dropBurst0202); count0202 = secuencia0202; pb0202 = (dropBurst0202/(arriveBurst0202 + dropBurst0202))*100; WATCH(pb0202);} }
             if        (destAddress == 2  && sourceAddress == 1)  {secuencia0102 = recvBurst->getSecuencia(); count0102++; arriveBurst0102++; WATCH(arriveBurst0102);
                  if   (count0102 == secuencia0102){dropBurst0102 = dropBurst0102; pb0102 = (dropBurst0102/(arriveBurst0102 + dropBurst0102))*100; WATCH(pb0102);}
                  else {dropBurst0102 = dropBurst0102 + (secuencia0102 - count0102); WATCH(dropBurst0102); count0102 = secuencia0102; pb0102 = (dropBurst0102/(arriveBurst0102 + dropBurst0102))*100; WATCH(pb0102);} }
             else if   (destAddress == 2  && sourceAddress == 3)  {secuencia0302 = recvBurst->getSecuencia(); count0302++; arriveBurst0302++; WATCH(arriveBurst0302);
                  if   (count0302 == secuencia0302){dropBurst0302 = dropBurst0302; pb0302 = (dropBurst0302/(arriveBurst0302 + dropBurst0302))*100; WATCH(pb0302);}
                  else {dropBurst0302 = dropBurst0302 + (secuencia0302 - count0302); WATCH(dropBurst0302); count0302 = secuencia0302; pb0302 = (dropBurst0302/(arriveBurst0302 + dropBurst0302))*100; WATCH(pb0302);} }
             else if   (destAddress == 2  && sourceAddress == 4)  {secuencia0402 = recvBurst->getSecuencia(); count0402++; arriveBurst0402++; WATCH(arriveBurst0402);
                  if   (count0402 == secuencia0402){dropBurst0402 = dropBurst0402; pb0402 = (dropBurst0402/(arriveBurst0402 + dropBurst0402))*100; WATCH(pb0402);}
                  else {dropBurst0402 = dropBurst0402 + (secuencia0402 - count0402); WATCH(dropBurst0402); count0402 = secuencia0402; pb0402 = (dropBurst0402/(arriveBurst0402 + dropBurst0402))*100; WATCH(pb0402);} }
             else if   (destAddress == 2  && sourceAddress == 5)  {secuencia0502 = recvBurst->getSecuencia(); count0502++; arriveBurst0502++; WATCH(arriveBurst0502);
                  if   (count0502 == secuencia0502){dropBurst0502 = dropBurst0502; pb0502 = (dropBurst0502/(arriveBurst0502 + dropBurst0502))*100; WATCH(pb0502);}
                  else {dropBurst0502 = dropBurst0502 + (secuencia0502 - count0502); WATCH(dropBurst0502); count0502 = secuencia0502; pb0502 = (dropBurst0502/(arriveBurst0502 + dropBurst0502))*100; WATCH(pb0502);} }
             else if   (destAddress == 2  && sourceAddress == 6)  {secuencia0602 = recvBurst->getSecuencia(); count0602++; arriveBurst0602++; WATCH(arriveBurst0602);
                  if   (count0602 == secuencia0602){dropBurst0602 = dropBurst0602; pb0602 = (dropBurst0602/(arriveBurst0602 + dropBurst0602))*100; WATCH(pb0602);}
                  else {dropBurst0602 = dropBurst0602 + (secuencia0602 - count0602); WATCH(dropBurst0602); count0602 = secuencia0602; pb0602 = (dropBurst0602/(arriveBurst0602 + dropBurst0602))*100; WATCH(pb0602);} }
             else if   (destAddress == 2  && sourceAddress == 7)  {secuencia0702 = recvBurst->getSecuencia(); count0702++; arriveBurst0702++; WATCH(arriveBurst0702);
                  if   (count0702 == secuencia0702){dropBurst0702 = dropBurst0702; pb0702 = (dropBurst0702/(arriveBurst0702 + dropBurst0702))*100; WATCH(pb0702);}
                  else {dropBurst0702 = dropBurst0702 + (secuencia0702 - count0702); WATCH(dropBurst0702); count0702 = secuencia0702; pb0702 = (dropBurst0702/(arriveBurst0702 + dropBurst0702))*100; WATCH(pb0702);} }
             else if   (destAddress == 2  && sourceAddress == 8)  {secuencia0802 = recvBurst->getSecuencia(); count0802++; arriveBurst0802++; WATCH(arriveBurst0802);
                  if   (count0802 == secuencia0802){dropBurst0802 = dropBurst0802; pb0802 = (dropBurst0802/(arriveBurst0802 + dropBurst0802))*100; WATCH(pb0802);}
                  else {dropBurst0802 = dropBurst0802 + (secuencia0802 - count0802); WATCH(dropBurst0802); count0802 = secuencia0802; pb0802 = (dropBurst0802/(arriveBurst0802 + dropBurst0802))*100; WATCH(pb0802);} }
             else if   (destAddress == 2  && sourceAddress == 9)  {secuencia0902 = recvBurst->getSecuencia(); count0902++; arriveBurst0902++; WATCH(arriveBurst0902);
                  if   (count0902 == secuencia0902){dropBurst0902 = dropBurst0902; pb0902 = (dropBurst0902/(arriveBurst0902 + dropBurst0902))*100; WATCH(pb0902);}
                  else {dropBurst0902 = dropBurst0902 + (secuencia0902 - count0902); WATCH(dropBurst0902); count0902 = secuencia0902; pb0902 = (dropBurst0902/(arriveBurst0902 + dropBurst0902))*100; WATCH(pb0902);} }
             else if   (destAddress == 2  && sourceAddress == 10) {secuencia1002 = recvBurst->getSecuencia(); count1002++; arriveBurst1002++; WATCH(arriveBurst1002);
                  if   (count1002 == secuencia1002){dropBurst1002 = dropBurst1002; pb1002 = (dropBurst1002/(arriveBurst1002 + dropBurst1002))*100; WATCH(pb1002);}
                  else {dropBurst1002 = dropBurst1002 + (secuencia1002 - count1002); WATCH(dropBurst1002); count1002 = secuencia1002; pb1002 = (dropBurst1002/(arriveBurst1002 + dropBurst1002))*100; WATCH(pb1002);} }
             else if   (destAddress == 2  && sourceAddress == 11) {secuencia1102 = recvBurst->getSecuencia(); count1102++; arriveBurst1102++; WATCH(arriveBurst1102);
                  if   (count1102 == secuencia1102){dropBurst1102 = dropBurst1102; pb1102 = (dropBurst1102/(arriveBurst1102 + dropBurst1102))*100; WATCH(pb1102);}
                  else {dropBurst1102 = dropBurst1102 + (secuencia1102 - count1102); WATCH(dropBurst1102); count1102 = secuencia1102; pb1102 = (dropBurst1102/(arriveBurst1102 + dropBurst1102))*100; WATCH(pb1102);} }
             else if   (destAddress == 2  && sourceAddress == 12) {secuencia1202 = recvBurst->getSecuencia(); count1202++; arriveBurst1202++; WATCH(arriveBurst1202);
                  if   (count1202 == secuencia1202){dropBurst1202 = dropBurst1202; pb1202 = (dropBurst1202/(arriveBurst1202 + dropBurst1202))*100; WATCH(pb1202);}
                  else {dropBurst1202 = dropBurst1202 + (secuencia1202 - count1202); WATCH(dropBurst1202); count1202 = secuencia1202; pb1202 = (dropBurst1202/(arriveBurst1202 + dropBurst1202))*100; WATCH(pb1202);} }
             else if   (destAddress == 2  && sourceAddress == 13) {secuencia1302 = recvBurst->getSecuencia(); count1302++; arriveBurst1302++; WATCH(arriveBurst1302);
                  if   (count1302 == secuencia1302){dropBurst1302 = dropBurst1302; pb1302 = (dropBurst1302/(arriveBurst1302 + dropBurst1302))*100; WATCH(pb1302);}
                  else {dropBurst1302 = dropBurst1302 + (secuencia1302 - count1302); WATCH(dropBurst1302); count1302 = secuencia1302; pb1302 = (dropBurst1302/(arriveBurst1302 + dropBurst1302))*100; WATCH(pb1302);} }
             else if   (destAddress == 2  && sourceAddress == 14) {secuencia1402 = recvBurst->getSecuencia(); count1402++; arriveBurst1402++; WATCH(arriveBurst1402);
                  if   (count1402 == secuencia1402){dropBurst1402 = dropBurst1402; pb1402 = (dropBurst1402/(arriveBurst1402 + dropBurst1402))*100; WATCH(pb1402);}
                  else {dropBurst1402 = dropBurst1402 + (secuencia1402 - count1402); WATCH(dropBurst1402); count1402 = secuencia1402; pb1402 = (dropBurst1402/(arriveBurst1402 + dropBurst1402))*100; WATCH(pb1402);} }


             //   if   (destAddress == 3  && sourceAddress == 3)  {secuencia0303 = recvBurst->getSecuencia(); count0303++; arriveBurst0303++; WATCH(arriveBurst0303);
             //   if   (count0303 == secuencia0303){dropBurst0303 = dropBurst0303; pb0303 = (dropBurst0303/(arriveBurst0303 + dropBurst0303))*100; WATCH(pb0303);}
             //   else {dropBurst0303 = dropBurst0303 + (secuencia0303 - count0303); WATCH(dropBurst0303); count0303 = secuencia0303; pb0303 = (dropBurst0303/(arriveBurst0303 + dropBurst0303))*100; WATCH(pb0303);} }
             if        (destAddress == 3  && sourceAddress == 1)  {secuencia0103 = recvBurst->getSecuencia(); count0103++; arriveBurst0103++; WATCH(arriveBurst0103);
                  if   (count0103 == secuencia0103){dropBurst0103 = dropBurst0103; pb0103 = (dropBurst0103/(arriveBurst0103 + dropBurst0103))*100; WATCH(pb0103);}
                  else {dropBurst0103 = dropBurst0103 + (secuencia0103 - count0103); WATCH(dropBurst0103); count0103 = secuencia0103; pb0103 = (dropBurst0103/(arriveBurst0103 + dropBurst0103))*100; WATCH(pb0103);} }
             else if   (destAddress == 3  && sourceAddress == 2)  {secuencia0203 = recvBurst->getSecuencia(); count0203++; arriveBurst0203++; WATCH(arriveBurst0203);
                  if   (count0203 == secuencia0203){dropBurst0203 = dropBurst0203; pb0203 = (dropBurst0203/(arriveBurst0203 + dropBurst0203))*100; WATCH(pb0203);}
                  else {dropBurst0203 = dropBurst0203 + (secuencia0203 - count0203); WATCH(dropBurst0203); count0203 = secuencia0203; pb0203 = (dropBurst0203/(arriveBurst0203 + dropBurst0203))*100; WATCH(pb0203);} }
             else if   (destAddress == 3  && sourceAddress == 4)  {secuencia0403 = recvBurst->getSecuencia(); count0403++; arriveBurst0403++; WATCH(arriveBurst0403);
                  if   (count0403 == secuencia0403){dropBurst0403 = dropBurst0403; pb0403 = (dropBurst0403/(arriveBurst0403 + dropBurst0403))*100; WATCH(pb0403);}
                  else {dropBurst0403 = dropBurst0403 + (secuencia0403 - count0403); WATCH(dropBurst0403); count0403 = secuencia0403; pb0403 = (dropBurst0403/(arriveBurst0403 + dropBurst0403))*100; WATCH(pb0403);} }
             else if   (destAddress == 3  && sourceAddress == 5)  {secuencia0503 = recvBurst->getSecuencia(); count0503++; arriveBurst0503++; WATCH(arriveBurst0503);
                  if   (count0503 == secuencia0503){dropBurst0503 = dropBurst0503; pb0503 = (dropBurst0503/(arriveBurst0503 + dropBurst0503))*100; WATCH(pb0503);}
                  else {dropBurst0503 = dropBurst0503 + (secuencia0503 - count0503); WATCH(dropBurst0503); count0503 = secuencia0503; pb0503 = (dropBurst0503/(arriveBurst0503 + dropBurst0503))*100; WATCH(pb0503);} }
             else if   (destAddress == 3  && sourceAddress == 6)  {secuencia0603 = recvBurst->getSecuencia(); count0603++; arriveBurst0603++; WATCH(arriveBurst0603);
                  if   (count0603 == secuencia0603){dropBurst0603 = dropBurst0603; pb0603 = (dropBurst0603/(arriveBurst0603 + dropBurst0603))*100; WATCH(pb0603);}
                  else {dropBurst0603 = dropBurst0603 + (secuencia0603 - count0603); WATCH(dropBurst0603); count0603 = secuencia0603; pb0603 = (dropBurst0603/(arriveBurst0603 + dropBurst0603))*100; WATCH(pb0603);} }
             else if   (destAddress == 3  && sourceAddress == 7)  {secuencia0703 = recvBurst->getSecuencia(); count0703++; arriveBurst0703++; WATCH(arriveBurst0703);
                  if   (count0703 == secuencia0703){dropBurst0703 = dropBurst0703; pb0703 = (dropBurst0703/(arriveBurst0703 + dropBurst0703))*100; WATCH(pb0703);}
                  else {dropBurst0703 = dropBurst0703 + (secuencia0703 - count0703); WATCH(dropBurst0703); count0703 = secuencia0703; pb0703 = (dropBurst0703/(arriveBurst0703 + dropBurst0703))*100; WATCH(pb0703);} }
             else if   (destAddress == 3  && sourceAddress == 8)  {secuencia0803 = recvBurst->getSecuencia(); count0803++; arriveBurst0803++; WATCH(arriveBurst0803);
                  if   (count0803 == secuencia0803){dropBurst0803 = dropBurst0803; pb0803 = (dropBurst0803/(arriveBurst0803 + dropBurst0803))*100; WATCH(pb0803);}
                  else {dropBurst0803 = dropBurst0803 + (secuencia0803 - count0803); WATCH(dropBurst0803); count0803 = secuencia0803; pb0803 = (dropBurst0803/(arriveBurst0803 + dropBurst0803))*100; WATCH(pb0803);} }
             else if   (destAddress == 3  && sourceAddress == 9)  {secuencia0903 = recvBurst->getSecuencia(); count0903++; arriveBurst0903++; WATCH(arriveBurst0903);
                  if   (count0903 == secuencia0903){dropBurst0903 = dropBurst0903; pb0903 = (dropBurst0903/(arriveBurst0903 + dropBurst0903))*100; WATCH(pb0903);}
                  else {dropBurst0903 = dropBurst0903 + (secuencia0903 - count0903); WATCH(dropBurst0903); count0903 = secuencia0903; pb0903 = (dropBurst0903/(arriveBurst0903 + dropBurst0903))*100; WATCH(pb0903);} }
             else if   (destAddress == 3  && sourceAddress == 10) {secuencia1003 = recvBurst->getSecuencia(); count1003++; arriveBurst1003++; WATCH(arriveBurst1003);
                  if   (count1003 == secuencia1003){dropBurst1003 = dropBurst1003; pb1003 = (dropBurst1003/(arriveBurst1003 + dropBurst1003))*100; WATCH(pb1003);}
                  else {dropBurst1003 = dropBurst1003 + (secuencia1003 - count1003); WATCH(dropBurst1003); count1003 = secuencia1003; pb1003 = (dropBurst1003/(arriveBurst1003 + dropBurst1003))*100; WATCH(pb1003);} }
             else if   (destAddress == 3  && sourceAddress == 11) {secuencia1103 = recvBurst->getSecuencia(); count1103++; arriveBurst1103++; WATCH(arriveBurst1103);
                  if   (count1103 == secuencia1103){dropBurst1103 = dropBurst1103; pb1103 = (dropBurst1103/(arriveBurst1103 + dropBurst1103))*100; WATCH(pb1103);}
                  else {dropBurst1103 = dropBurst1103 + (secuencia1103 - count1103); WATCH(dropBurst1103); count1103 = secuencia1103; pb1103 = (dropBurst1103/(arriveBurst1103 + dropBurst1103))*100; WATCH(pb1103);} }
             else if   (destAddress == 3  && sourceAddress == 12) {secuencia1203 = recvBurst->getSecuencia(); count1203++; arriveBurst1203++; WATCH(arriveBurst1203);
                  if   (count1203 == secuencia1203){dropBurst1203 = dropBurst1203; pb1203 = (dropBurst1203/(arriveBurst1203 + dropBurst1203))*100; WATCH(pb1203);}
                  else {dropBurst1203 = dropBurst1203 + (secuencia1203 - count1203); WATCH(dropBurst1203); count1203 = secuencia1203; pb1203 = (dropBurst1203/(arriveBurst1203 + dropBurst1203))*100; WATCH(pb1203);} }
             else if   (destAddress == 3  && sourceAddress == 13) {secuencia1303 = recvBurst->getSecuencia(); count1303++; arriveBurst1303++; WATCH(arriveBurst1303);
                  if   (count1303 == secuencia1303){dropBurst1303 = dropBurst1303; pb1303 = (dropBurst1303/(arriveBurst1303 + dropBurst1303))*100; WATCH(pb1303);}
                  else {dropBurst1303 = dropBurst1303 + (secuencia1303 - count1303); WATCH(dropBurst1303); count1303 = secuencia1303; pb1303 = (dropBurst1303/(arriveBurst1303 + dropBurst1303))*100; WATCH(pb1303);} }
             else if   (destAddress == 3  && sourceAddress == 14) {secuencia1403 = recvBurst->getSecuencia(); count1403++; arriveBurst1403++; WATCH(arriveBurst1403);
                  if   (count1403 == secuencia1403){dropBurst1403 = dropBurst1403; pb1403 = (dropBurst1403/(arriveBurst1403 + dropBurst1403))*100; WATCH(pb1403);}
                  else {dropBurst1403 = dropBurst1403 + (secuencia1403 - count1403); WATCH(dropBurst1403); count1403 = secuencia1403; pb1403 = (dropBurst1403/(arriveBurst1403 + dropBurst1403))*100; WATCH(pb1403);} }


             //   if   (destAddress == 4  && sourceAddress == 4)  {secuencia0404 = recvBurst->getSecuencia(); count0404++; arriveBurst0404++; WATCH(arriveBurst0404);
             //   if   (count0404 == secuencia0404){dropBurst0404 = dropBurst0404; pb0404 = (dropBurst0404/(arriveBurst0404 + dropBurst0404))*100; WATCH(pb0404);}
             //   else {dropBurst0404 = dropBurst0404 + (secuencia0404 - count0404); WATCH(dropBurst0404); count0404 = secuencia0404; pb0404 = (dropBurst0404/(arriveBurst0404 + dropBurst0404))*100; WATCH(pb0404);} }
             if        (destAddress == 4  && sourceAddress == 1)  {secuencia0104 = recvBurst->getSecuencia(); count0104++; arriveBurst0104++; WATCH(arriveBurst0104);
                  if   (count0104 == secuencia0104){dropBurst0104 = dropBurst0104; pb0104 = (dropBurst0104/(arriveBurst0104 + dropBurst0104))*100; WATCH(pb0104);}
                  else {dropBurst0104 = dropBurst0104 + (secuencia0104 - count0104); WATCH(dropBurst0104); count0104 = secuencia0104; pb0104 = (dropBurst0104/(arriveBurst0104 + dropBurst0104))*100; WATCH(pb0104);} }
             else if   (destAddress == 4  && sourceAddress == 2)  {secuencia0204 = recvBurst->getSecuencia(); count0204++; arriveBurst0204++; WATCH(arriveBurst0204);
                  if   (count0204 == secuencia0204){dropBurst0204 = dropBurst0204; pb0204 = (dropBurst0204/(arriveBurst0204 + dropBurst0204))*100; WATCH(pb0204);}
                  else {dropBurst0204 = dropBurst0204 + (secuencia0204 - count0204); WATCH(dropBurst0204); count0204 = secuencia0204; pb0204 = (dropBurst0204/(arriveBurst0204 + dropBurst0204))*100; WATCH(pb0204);} }
             else if   (destAddress == 4  && sourceAddress == 3)  {secuencia0304 = recvBurst->getSecuencia(); count0304++; arriveBurst0304++; WATCH(arriveBurst0304);
                  if   (count0304 == secuencia0304){dropBurst0304 = dropBurst0304; pb0304 = (dropBurst0304/(arriveBurst0304 + dropBurst0304))*100; WATCH(pb0304);}
                  else {dropBurst0304 = dropBurst0304 + (secuencia0304 - count0304); WATCH(dropBurst0304); count0304 = secuencia0304; pb0304 = (dropBurst0304/(arriveBurst0304 + dropBurst0304))*100; WATCH(pb0304);} }
             else if   (destAddress == 4  && sourceAddress == 5)  {secuencia0504 = recvBurst->getSecuencia(); count0504++; arriveBurst0504++; WATCH(arriveBurst0504);
                  if   (count0504 == secuencia0504){dropBurst0504 = dropBurst0504; pb0504 = (dropBurst0504/(arriveBurst0504 + dropBurst0504))*100; WATCH(pb0504);}
                  else {dropBurst0504 = dropBurst0504 + (secuencia0504 - count0504); WATCH(dropBurst0504); count0504 = secuencia0504; pb0504 = (dropBurst0504/(arriveBurst0504 + dropBurst0504))*100; WATCH(pb0504);} }
             else if   (destAddress == 4  && sourceAddress == 6)  {secuencia0604 = recvBurst->getSecuencia(); count0604++; arriveBurst0604++; WATCH(arriveBurst0604);
                  if   (count0604 == secuencia0604){dropBurst0604 = dropBurst0604; pb0604 = (dropBurst0604/(arriveBurst0604 + dropBurst0604))*100; WATCH(pb0604);}
                  else {dropBurst0604 = dropBurst0604 + (secuencia0604 - count0604); WATCH(dropBurst0604); count0604 = secuencia0604; pb0604 = (dropBurst0604/(arriveBurst0604 + dropBurst0604))*100; WATCH(pb0604);} }
             else if   (destAddress == 4  && sourceAddress == 7)  {secuencia0704 = recvBurst->getSecuencia(); count0704++; arriveBurst0704++; WATCH(arriveBurst0704);
                  if   (count0704 == secuencia0704){dropBurst0704 = dropBurst0704; pb0704 = (dropBurst0704/(arriveBurst0704 + dropBurst0704))*100; WATCH(pb0704);}
                  else {dropBurst0704 = dropBurst0704 + (secuencia0704 - count0704); WATCH(dropBurst0704); count0704 = secuencia0704; pb0704 = (dropBurst0704/(arriveBurst0704 + dropBurst0704))*100; WATCH(pb0704);} }
             else if   (destAddress == 4  && sourceAddress == 8)  {secuencia0804 = recvBurst->getSecuencia(); count0804++; arriveBurst0804++; WATCH(arriveBurst0804);
                  if   (count0804 == secuencia0804){dropBurst0804 = dropBurst0804; pb0804 = (dropBurst0804/(arriveBurst0804 + dropBurst0804))*100; WATCH(pb0804);}
                  else {dropBurst0804 = dropBurst0804 + (secuencia0804 - count0804); WATCH(dropBurst0804); count0804 = secuencia0804; pb0804 = (dropBurst0804/(arriveBurst0804 + dropBurst0804))*100; WATCH(pb0804);} }
             else if   (destAddress == 4  && sourceAddress == 9)  {secuencia0904 = recvBurst->getSecuencia(); count0904++; arriveBurst0904++; WATCH(arriveBurst0904);
                  if   (count0904 == secuencia0904){dropBurst0904 = dropBurst0904; pb0904 = (dropBurst0904/(arriveBurst0904 + dropBurst0904))*100; WATCH(pb0904);}
                  else {dropBurst0904 = dropBurst0904 + (secuencia0904 - count0904); WATCH(dropBurst0904); count0904 = secuencia0904; pb0904 = (dropBurst0904/(arriveBurst0904 + dropBurst0904))*100; WATCH(pb0904);} }
             else if   (destAddress == 4  && sourceAddress == 10) {secuencia1004 = recvBurst->getSecuencia(); count1004++; arriveBurst1004++; WATCH(arriveBurst1004);
                  if   (count1004 == secuencia1004){dropBurst1004 = dropBurst1004; pb1004 = (dropBurst1004/(arriveBurst1004 + dropBurst1004))*100; WATCH(pb1004);}
                  else {dropBurst1004 = dropBurst1004 + (secuencia1004 - count1004); WATCH(dropBurst1004); count1004 = secuencia1004; pb1004 = (dropBurst1004/(arriveBurst1004 + dropBurst1004))*100; WATCH(pb1004);} }
             else if   (destAddress == 4  && sourceAddress == 11) {secuencia1104 = recvBurst->getSecuencia(); count1104++; arriveBurst1104++; WATCH(arriveBurst1104);
                  if   (count1104 == secuencia1104){dropBurst1104 = dropBurst1104; pb1104 = (dropBurst1104/(arriveBurst1104 + dropBurst1104))*100; WATCH(pb1104);}
                  else {dropBurst1104 = dropBurst1104 + (secuencia1104 - count1104); WATCH(dropBurst1104); count1104 = secuencia1104; pb1104 = (dropBurst1104/(arriveBurst1104 + dropBurst1104))*100; WATCH(pb1104);} }
             else if   (destAddress == 4  && sourceAddress == 12) {secuencia1204 = recvBurst->getSecuencia(); count1204++; arriveBurst1204++; WATCH(arriveBurst1204);
                  if   (count1204 == secuencia1204){dropBurst1204 = dropBurst1204; pb1204 = (dropBurst1204/(arriveBurst1204 + dropBurst1204))*100; WATCH(pb1204);}
                  else {dropBurst1204 = dropBurst1204 + (secuencia1204 - count1204); WATCH(dropBurst1204); count1204 = secuencia1204; pb1204 = (dropBurst1204/(arriveBurst1204 + dropBurst1204))*100; WATCH(pb1204);} }
             else if   (destAddress == 4  && sourceAddress == 13) {secuencia1304 = recvBurst->getSecuencia(); count1304++; arriveBurst1304++; WATCH(arriveBurst1304);
                  if   (count1304 == secuencia1304){dropBurst1304 = dropBurst1304; pb1304 = (dropBurst1304/(arriveBurst1304 + dropBurst1304))*100; WATCH(pb1304);}
                  else {dropBurst1304 = dropBurst1304 + (secuencia1304 - count1304); WATCH(dropBurst1304); count1304 = secuencia1304; pb1304 = (dropBurst1304/(arriveBurst1304 + dropBurst1304))*100; WATCH(pb1304);} }
             else if   (destAddress == 4  && sourceAddress == 14) {secuencia1404 = recvBurst->getSecuencia(); count1404++; arriveBurst1404++; WATCH(arriveBurst1404);
                  if   (count1404 == secuencia1404){dropBurst1404 = dropBurst1404; pb1404 = (dropBurst1404/(arriveBurst1404 + dropBurst1404))*100; WATCH(pb1404);}
                  else {dropBurst1404 = dropBurst1404 + (secuencia1404 - count1404); WATCH(dropBurst1404); count1404 = secuencia1404; pb1404 = (dropBurst1404/(arriveBurst1404 + dropBurst1404))*100; WATCH(pb1404);} }


             //   if   (destAddress == 5  && sourceAddress == 5)  {secuencia0505 = recvBurst->getSecuencia(); count0505++; arriveBurst0505++; WATCH(arriveBurst0505);
             //   if   (count0505 == secuencia0505){dropBurst0505 = dropBurst0505; pb0505 = (dropBurst0505/(arriveBurst0505 + dropBurst0505))*100; WATCH(pb0505);}
             //   else {dropBurst0505 = dropBurst0505 + (secuencia0505 - count0505); WATCH(dropBurst0505); count0505 = secuencia0505; pb0505 = (dropBurst0505/(arriveBurst0505 + dropBurst0505))*100; WATCH(pb0505);} }
             if        (destAddress == 5  && sourceAddress == 1)  {secuencia0105 = recvBurst->getSecuencia(); count0105++; arriveBurst0105++; WATCH(arriveBurst0105);
                  if   (count0105 == secuencia0105){dropBurst0105 = dropBurst0105; pb0105 = (dropBurst0105/(arriveBurst0105 + dropBurst0105))*100; WATCH(pb0105);}
                  else {dropBurst0105 = dropBurst0105 + (secuencia0105 - count0105); WATCH(dropBurst0105); count0105 = secuencia0105; pb0105 = (dropBurst0105/(arriveBurst0105 + dropBurst0105))*100; WATCH(pb0105);} }
             else if   (destAddress == 5  && sourceAddress == 2)  {secuencia0205 = recvBurst->getSecuencia(); count0205++; arriveBurst0205++; WATCH(arriveBurst0205);
                  if   (count0205 == secuencia0205){dropBurst0205 = dropBurst0205; pb0205 = (dropBurst0205/(arriveBurst0205 + dropBurst0205))*100; WATCH(pb0205);}
                  else {dropBurst0205 = dropBurst0205 + (secuencia0205 - count0205); WATCH(dropBurst0205); count0205 = secuencia0205; pb0205 = (dropBurst0205/(arriveBurst0205 + dropBurst0205))*100; WATCH(pb0205);} }
             else if   (destAddress == 5  && sourceAddress == 3)  {secuencia0305 = recvBurst->getSecuencia(); count0305++; arriveBurst0305++; WATCH(arriveBurst0305);
                  if   (count0305 == secuencia0305){dropBurst0305 = dropBurst0305; pb0305 = (dropBurst0305/(arriveBurst0305 + dropBurst0305))*100; WATCH(pb0305);}
                  else {dropBurst0305 = dropBurst0305 + (secuencia0305 - count0305); WATCH(dropBurst0305); count0305 = secuencia0305; pb0305 = (dropBurst0305/(arriveBurst0305 + dropBurst0305))*100; WATCH(pb0305);} }
             else if   (destAddress == 5  && sourceAddress == 4)  {secuencia0405 = recvBurst->getSecuencia(); count0405++; arriveBurst0405++; WATCH(arriveBurst0405);
                  if   (count0405 == secuencia0405){dropBurst0405 = dropBurst0405; pb0405 = (dropBurst0405/(arriveBurst0405 + dropBurst0405))*100; WATCH(pb0405);}
                  else {dropBurst0405 = dropBurst0405 + (secuencia0405 - count0405); WATCH(dropBurst0405); count0405 = secuencia0405; pb0405 = (dropBurst0405/(arriveBurst0405 + dropBurst0405))*100; WATCH(pb0405);} }
             else if   (destAddress == 5  && sourceAddress == 6)  {secuencia0605 = recvBurst->getSecuencia(); count0605++; arriveBurst0605++; WATCH(arriveBurst0605);
                  if   (count0605 == secuencia0605){dropBurst0605 = dropBurst0605; pb0605 = (dropBurst0605/(arriveBurst0605 + dropBurst0605))*100; WATCH(pb0605);}
                  else {dropBurst0605 = dropBurst0605 + (secuencia0605 - count0605); WATCH(dropBurst0605); count0605 = secuencia0605; pb0605 = (dropBurst0605/(arriveBurst0605 + dropBurst0605))*100; WATCH(pb0605);} }
             else if   (destAddress == 5  && sourceAddress == 7)  {secuencia0705 = recvBurst->getSecuencia(); count0705++; arriveBurst0705++; WATCH(arriveBurst0705);
                  if   (count0705 == secuencia0705){dropBurst0705 = dropBurst0705; pb0705 = (dropBurst0705/(arriveBurst0705 + dropBurst0705))*100; WATCH(pb0705);}
                  else {dropBurst0705 = dropBurst0705 + (secuencia0705 - count0705); WATCH(dropBurst0705); count0705 = secuencia0705; pb0705 = (dropBurst0705/(arriveBurst0705 + dropBurst0705))*100; WATCH(pb0705);} }
             else if   (destAddress == 5  && sourceAddress == 8)  {secuencia0805 = recvBurst->getSecuencia(); count0805++; arriveBurst0805++; WATCH(arriveBurst0805);
                  if   (count0805 == secuencia0805){dropBurst0805 = dropBurst0805; pb0805 = (dropBurst0805/(arriveBurst0805 + dropBurst0805))*100; WATCH(pb0805);}
                  else {dropBurst0805 = dropBurst0805 + (secuencia0805 - count0805); WATCH(dropBurst0805); count0805 = secuencia0805; pb0805 = (dropBurst0805/(arriveBurst0805 + dropBurst0805))*100; WATCH(pb0805);} }
             else if   (destAddress == 5  && sourceAddress == 9)  {secuencia0905 = recvBurst->getSecuencia(); count0905++; arriveBurst0905++; WATCH(arriveBurst0905);
                  if   (count0905 == secuencia0905){dropBurst0905 = dropBurst0905; pb0905 = (dropBurst0905/(arriveBurst0905 + dropBurst0905))*100; WATCH(pb0905);}
                  else {dropBurst0905 = dropBurst0905 + (secuencia0905 - count0905); WATCH(dropBurst0905); count0905 = secuencia0905; pb0905 = (dropBurst0905/(arriveBurst0905 + dropBurst0905))*100; WATCH(pb0905);} }
             else if   (destAddress == 5  && sourceAddress == 10) {secuencia1005 = recvBurst->getSecuencia(); count1005++; arriveBurst1005++; WATCH(arriveBurst1005);
                  if   (count1005 == secuencia1005){dropBurst1005 = dropBurst1005; pb1005 = (dropBurst1005/(arriveBurst1005 + dropBurst1005))*100; WATCH(pb1005);}
                  else {dropBurst1005 = dropBurst1005 + (secuencia1005 - count1005); WATCH(dropBurst1005); count1005 = secuencia1005; pb1005 = (dropBurst1005/(arriveBurst1005 + dropBurst1005))*100; WATCH(pb1005);} }
             else if   (destAddress == 5  && sourceAddress == 11) {secuencia1105 = recvBurst->getSecuencia(); count1105++; arriveBurst1105++; WATCH(arriveBurst1105);
                  if   (count1105 == secuencia1105){dropBurst1105 = dropBurst1105; pb1105 = (dropBurst1105/(arriveBurst1105 + dropBurst1105))*100; WATCH(pb1105);}
                  else {dropBurst1105 = dropBurst1105 + (secuencia1105 - count1105); WATCH(dropBurst1105); count1105 = secuencia1105; pb1105 = (dropBurst1105/(arriveBurst1105 + dropBurst1105))*100; WATCH(pb1105);} }
             else if   (destAddress == 5  && sourceAddress == 12) {secuencia1205 = recvBurst->getSecuencia(); count1205++; arriveBurst1205++; WATCH(arriveBurst1205);
                  if   (count1205 == secuencia1205){dropBurst1205 = dropBurst1205; pb1205 = (dropBurst1205/(arriveBurst1205 + dropBurst1205))*100; WATCH(pb1205);}
                  else {dropBurst1205 = dropBurst1205 + (secuencia1205 - count1205); WATCH(dropBurst1205); count1205 = secuencia1205; pb1205 = (dropBurst1205/(arriveBurst1205 + dropBurst1205))*100; WATCH(pb1205);} }
             else if   (destAddress == 5  && sourceAddress == 13) {secuencia1305 = recvBurst->getSecuencia(); count1305++; arriveBurst1305++; WATCH(arriveBurst1305);
                  if   (count1305 == secuencia1305){dropBurst1305 = dropBurst1305; pb1305 = (dropBurst1305/(arriveBurst1305 + dropBurst1305))*100; WATCH(pb1305);}
                  else {dropBurst1305 = dropBurst1305 + (secuencia1305 - count1305); WATCH(dropBurst1305); count1305 = secuencia1305; pb1305 = (dropBurst1305/(arriveBurst1305 + dropBurst1305))*100; WATCH(pb1305);} }
             else if   (destAddress == 5  && sourceAddress == 14) {secuencia1405 = recvBurst->getSecuencia(); count1405++; arriveBurst1405++; WATCH(arriveBurst1405);
                  if   (count1405 == secuencia1405){dropBurst1405 = dropBurst1405; pb1405 = (dropBurst1405/(arriveBurst1405 + dropBurst1405))*100; WATCH(pb1405);}
                  else {dropBurst1405 = dropBurst1405 + (secuencia1405 - count1405); WATCH(dropBurst1405); count1405 = secuencia1405; pb1405 = (dropBurst1405/(arriveBurst1405 + dropBurst1405))*100; WATCH(pb1405);} }


             //   if   (destAddress == 6  && sourceAddress == 6)  {secuencia0606 = recvBurst->getSecuencia(); count0606++; arriveBurst0606++; WATCH(arriveBurst0606);
             //   if   (count0606 == secuencia0606){dropBurst0606 = dropBurst0606; pb0606 = (dropBurst0606/(arriveBurst0606 + dropBurst0606))*100; WATCH(pb0606);}
             //   else {dropBurst0606 = dropBurst0606 + (secuencia0606 - count0606); WATCH(dropBurst0606); count0606 = secuencia0606; pb0606 = (dropBurst0606/(arriveBurst0606 + dropBurst0606))*100; WATCH(pb0606);} }
             if        (destAddress == 6  && sourceAddress == 1)  {secuencia0106 = recvBurst->getSecuencia(); count0106++; arriveBurst0106++; WATCH(arriveBurst0106);
                  if   (count0106 == secuencia0106){dropBurst0106 = dropBurst0106; pb0106 = (dropBurst0106/(arriveBurst0106 + dropBurst0106))*100; WATCH(pb0106);}
                  else {dropBurst0106 = dropBurst0106 + (secuencia0106 - count0106); WATCH(dropBurst0106); count0106 = secuencia0106; pb0106 = (dropBurst0106/(arriveBurst0106 + dropBurst0106))*100; WATCH(pb0106);} }
             else if   (destAddress == 6  && sourceAddress == 2)  {secuencia0206 = recvBurst->getSecuencia(); count0206++; arriveBurst0206++; WATCH(arriveBurst0206);
                  if   (count0206 == secuencia0206){dropBurst0206 = dropBurst0206; pb0206 = (dropBurst0206/(arriveBurst0206 + dropBurst0206))*100; WATCH(pb0206);}
                  else {dropBurst0206 = dropBurst0206 + (secuencia0206 - count0206); WATCH(dropBurst0206); count0206 = secuencia0206; pb0206 = (dropBurst0206/(arriveBurst0206 + dropBurst0206))*100; WATCH(pb0206);} }
             else if   (destAddress == 6  && sourceAddress == 3)  {secuencia0306 = recvBurst->getSecuencia(); count0306++; arriveBurst0306++; WATCH(arriveBurst0306);
                  if   (count0306 == secuencia0306){dropBurst0306 = dropBurst0306; pb0306 = (dropBurst0306/(arriveBurst0306 + dropBurst0306))*100; WATCH(pb0306);}
                  else {dropBurst0306 = dropBurst0306 + (secuencia0306 - count0306); WATCH(dropBurst0306); count0306 = secuencia0306; pb0306 = (dropBurst0306/(arriveBurst0306 + dropBurst0306))*100; WATCH(pb0306);} }
             else if   (destAddress == 6  && sourceAddress == 4)  {secuencia0406 = recvBurst->getSecuencia(); count0406++; arriveBurst0406++; WATCH(arriveBurst0406);
                  if   (count0406 == secuencia0406){dropBurst0406 = dropBurst0406; pb0406 = (dropBurst0406/(arriveBurst0406 + dropBurst0406))*100; WATCH(pb0406);}
                  else {dropBurst0406 = dropBurst0406 + (secuencia0406 - count0406); WATCH(dropBurst0406); count0406 = secuencia0406; pb0406 = (dropBurst0406/(arriveBurst0406 + dropBurst0406))*100; WATCH(pb0406);} }
             else if   (destAddress == 6  && sourceAddress == 5)  {secuencia0506 = recvBurst->getSecuencia(); count0506++; arriveBurst0506++; WATCH(arriveBurst0506);
                  if   (count0506 == secuencia0506){dropBurst0506 = dropBurst0506; pb0506 = (dropBurst0506/(arriveBurst0506 + dropBurst0506))*100; WATCH(pb0506);}
                  else {dropBurst0506 = dropBurst0506 + (secuencia0506 - count0506); WATCH(dropBurst0506); count0506 = secuencia0506; pb0506 = (dropBurst0506/(arriveBurst0506 + dropBurst0506))*100; WATCH(pb0506);} }
             else if   (destAddress == 6  && sourceAddress == 7)  {secuencia0706 = recvBurst->getSecuencia(); count0706++; arriveBurst0706++; WATCH(arriveBurst0706);
                  if   (count0706 == secuencia0706){dropBurst0706 = dropBurst0706; pb0706 = (dropBurst0706/(arriveBurst0706 + dropBurst0706))*100; WATCH(pb0706);}
                  else {dropBurst0706 = dropBurst0706 + (secuencia0706 - count0706); WATCH(dropBurst0706); count0706 = secuencia0706; pb0706 = (dropBurst0706/(arriveBurst0706 + dropBurst0706))*100; WATCH(pb0706);} }
             else if   (destAddress == 6  && sourceAddress == 8)  {secuencia0806 = recvBurst->getSecuencia(); count0806++; arriveBurst0806++; WATCH(arriveBurst0806);
                  if   (count0806 == secuencia0806){dropBurst0806 = dropBurst0806; pb0806 = (dropBurst0806/(arriveBurst0806 + dropBurst0806))*100; WATCH(pb0806);}
                  else {dropBurst0806 = dropBurst0806 + (secuencia0806 - count0806); WATCH(dropBurst0806); count0806 = secuencia0806; pb0806 = (dropBurst0806/(arriveBurst0806 + dropBurst0806))*100; WATCH(pb0806);} }
             else if   (destAddress == 6  && sourceAddress == 9)  {secuencia0906 = recvBurst->getSecuencia(); count0906++; arriveBurst0906++; WATCH(arriveBurst0906);
                  if   (count0906 == secuencia0906){dropBurst0906 = dropBurst0906; pb0906 = (dropBurst0906/(arriveBurst0906 + dropBurst0906))*100; WATCH(pb0906);}
                  else {dropBurst0906 = dropBurst0906 + (secuencia0906 - count0906); WATCH(dropBurst0906); count0906 = secuencia0906; pb0906 = (dropBurst0906/(arriveBurst0906 + dropBurst0906))*100; WATCH(pb0906);} }
             else if   (destAddress == 6  && sourceAddress == 10) {secuencia1006 = recvBurst->getSecuencia(); count1006++; arriveBurst1006++; WATCH(arriveBurst1006);
                  if   (count1006 == secuencia1006){dropBurst1006 = dropBurst1006; pb1006 = (dropBurst1006/(arriveBurst1006 + dropBurst1006))*100; WATCH(pb1006);}
                  else {dropBurst1006 = dropBurst1006 + (secuencia1006 - count1006); WATCH(dropBurst1006); count1006 = secuencia1006; pb1006 = (dropBurst1006/(arriveBurst1006 + dropBurst1006))*100; WATCH(pb1006);} }
             else if   (destAddress == 6  && sourceAddress == 11) {secuencia1106 = recvBurst->getSecuencia(); count1106++; arriveBurst1106++; WATCH(arriveBurst1106);
                  if   (count1106 == secuencia1106){dropBurst1106 = dropBurst1106; pb1106 = (dropBurst1106/(arriveBurst1106 + dropBurst1106))*100; WATCH(pb1106);}
                  else {dropBurst1106 = dropBurst1106 + (secuencia1106 - count1106); WATCH(dropBurst1106); count1106 = secuencia1106; pb1106 = (dropBurst1106/(arriveBurst1106 + dropBurst1106))*100; WATCH(pb1106);} }
             else if   (destAddress == 6  && sourceAddress == 12) {secuencia1206 = recvBurst->getSecuencia(); count1206++; arriveBurst1206++; WATCH(arriveBurst1206);
                  if   (count1206 == secuencia1206){dropBurst1206 = dropBurst1206; pb1206 = (dropBurst1206/(arriveBurst1206 + dropBurst1206))*100; WATCH(pb1206);}
                  else {dropBurst1206 = dropBurst1206 + (secuencia1206 - count1206); WATCH(dropBurst1206); count1206 = secuencia1206; pb1206 = (dropBurst1206/(arriveBurst1206 + dropBurst1206))*100; WATCH(pb1206);} }
             else if   (destAddress == 6  && sourceAddress == 13) {secuencia1306 = recvBurst->getSecuencia(); count1306++; arriveBurst1306++; WATCH(arriveBurst1306);
                  if   (count1306 == secuencia1306){dropBurst1306 = dropBurst1306; pb1306 = (dropBurst1306/(arriveBurst1306 + dropBurst1306))*100; WATCH(pb1306);}
                  else {dropBurst1306 = dropBurst1306 + (secuencia1306 - count1306); WATCH(dropBurst1306); count1306 = secuencia1306; pb1306 = (dropBurst1306/(arriveBurst1306 + dropBurst1306))*100; WATCH(pb1306);} }
             else if   (destAddress == 6  && sourceAddress == 14) {secuencia1406 = recvBurst->getSecuencia(); count1406++; arriveBurst1406++; WATCH(arriveBurst1406);
                  if   (count1406 == secuencia1406){dropBurst1406 = dropBurst1406; pb1406 = (dropBurst1406/(arriveBurst1406 + dropBurst1406))*100; WATCH(pb1406);}
                  else {dropBurst1406 = dropBurst1406 + (secuencia1406 - count1406); WATCH(dropBurst1406); count1406 = secuencia1406; pb1406 = (dropBurst1406/(arriveBurst1406 + dropBurst1406))*100; WATCH(pb1406);} }


             //   if   (destAddress == 7  && sourceAddress == 7)  {secuencia0707 = recvBurst->getSecuencia(); count0707++; arriveBurst0707++; WATCH(arriveBurst0707);
             //   if   (count0707 == secuencia0707){dropBurst0707 = dropBurst0707; pb0707 = (dropBurst0707/(arriveBurst0707 + dropBurst0707))*100; WATCH(pb0707);}
             //   else {dropBurst0707 = dropBurst0707 + (secuencia0707 - count0707); WATCH(dropBurst0707); count0707 = secuencia0707; pb0707 = (dropBurst0707/(arriveBurst0707 + dropBurst0707))*100; WATCH(pb0707);} }
             if        (destAddress == 7  && sourceAddress == 1)  {secuencia0107 = recvBurst->getSecuencia(); count0107++; arriveBurst0107++; WATCH(arriveBurst0107);
                  if   (count0107 == secuencia0107){dropBurst0107 = dropBurst0107; pb0107 = (dropBurst0107/(arriveBurst0107 + dropBurst0107))*100; WATCH(pb0107);}
                  else {dropBurst0107 = dropBurst0107 + (secuencia0107 - count0107); WATCH(dropBurst0107); count0107 = secuencia0107; pb0107 = (dropBurst0107/(arriveBurst0107 + dropBurst0107))*100; WATCH(pb0107);} }
             else if   (destAddress == 7  && sourceAddress == 2)  {secuencia0207 = recvBurst->getSecuencia(); count0207++; arriveBurst0207++; WATCH(arriveBurst0207);
                  if   (count0207 == secuencia0207){dropBurst0207 = dropBurst0207; pb0207 = (dropBurst0207/(arriveBurst0207 + dropBurst0207))*100; WATCH(pb0207);}
                  else {dropBurst0207 = dropBurst0207 + (secuencia0207 - count0207); WATCH(dropBurst0207); count0207 = secuencia0207; pb0207 = (dropBurst0207/(arriveBurst0207 + dropBurst0207))*100; WATCH(pb0207);} }
             else if   (destAddress == 7  && sourceAddress == 3)  {secuencia0307 = recvBurst->getSecuencia(); count0307++; arriveBurst0307++; WATCH(arriveBurst0307);
                  if   (count0307 == secuencia0307){dropBurst0307 = dropBurst0307; pb0307 = (dropBurst0307/(arriveBurst0307 + dropBurst0307))*100; WATCH(pb0307);}
                  else {dropBurst0307 = dropBurst0307 + (secuencia0307 - count0307); WATCH(dropBurst0307); count0307 = secuencia0307; pb0307 = (dropBurst0307/(arriveBurst0307 + dropBurst0307))*100; WATCH(pb0307);} }
             else if   (destAddress == 7  && sourceAddress == 4)  {secuencia0407 = recvBurst->getSecuencia(); count0407++; arriveBurst0407++; WATCH(arriveBurst0407);
                  if   (count0407 == secuencia0407){dropBurst0407 = dropBurst0407; pb0407 = (dropBurst0407/(arriveBurst0407 + dropBurst0407))*100; WATCH(pb0407);}
                  else {dropBurst0407 = dropBurst0407 + (secuencia0407 - count0407); WATCH(dropBurst0407); count0407 = secuencia0407; pb0407 = (dropBurst0407/(arriveBurst0407 + dropBurst0407))*100; WATCH(pb0407);} }
             else if   (destAddress == 7  && sourceAddress == 5)  {secuencia0507 = recvBurst->getSecuencia(); count0507++; arriveBurst0507++; WATCH(arriveBurst0507);
                  if   (count0507 == secuencia0507){dropBurst0507 = dropBurst0507; pb0507 = (dropBurst0507/(arriveBurst0507 + dropBurst0507))*100; WATCH(pb0507);}
                  else {dropBurst0507 = dropBurst0507 + (secuencia0507 - count0507); WATCH(dropBurst0507); count0507 = secuencia0507; pb0507 = (dropBurst0507/(arriveBurst0507 + dropBurst0507))*100; WATCH(pb0507);} }
             else if   (destAddress == 7  && sourceAddress == 6)  {secuencia0607 = recvBurst->getSecuencia(); count0607++; arriveBurst0607++; WATCH(arriveBurst0607);
                  if   (count0607 == secuencia0607){dropBurst0607 = dropBurst0607; pb0607 = (dropBurst0607/(arriveBurst0607 + dropBurst0607))*100; WATCH(pb0607);}
                  else {dropBurst0607 = dropBurst0607 + (secuencia0607 - count0607); WATCH(dropBurst0607); count0607 = secuencia0607; pb0607 = (dropBurst0607/(arriveBurst0607 + dropBurst0607))*100; WATCH(pb0607);} }
             else if   (destAddress == 7  && sourceAddress == 8)  {secuencia0807 = recvBurst->getSecuencia(); count0807++; arriveBurst0807++; WATCH(arriveBurst0807);
                  if   (count0807 == secuencia0807){dropBurst0807 = dropBurst0807; pb0807 = (dropBurst0807/(arriveBurst0807 + dropBurst0807))*100; WATCH(pb0807);}
                  else {dropBurst0807 = dropBurst0807 + (secuencia0807 - count0807); WATCH(dropBurst0807); count0807 = secuencia0807; pb0807 = (dropBurst0807/(arriveBurst0807 + dropBurst0807))*100; WATCH(pb0807);} }
             else if   (destAddress == 7  && sourceAddress == 9)  {secuencia0907 = recvBurst->getSecuencia(); count0907++; arriveBurst0907++; WATCH(arriveBurst0907);
                  if   (count0907 == secuencia0907){dropBurst0907 = dropBurst0907; pb0907 = (dropBurst0907/(arriveBurst0907 + dropBurst0907))*100; WATCH(pb0907);}
                  else {dropBurst0907 = dropBurst0907 + (secuencia0907 - count0907); WATCH(dropBurst0907); count0907 = secuencia0907; pb0907 = (dropBurst0907/(arriveBurst0907 + dropBurst0907))*100; WATCH(pb0907);} }
             else if   (destAddress == 7  && sourceAddress == 10) {secuencia1007 = recvBurst->getSecuencia(); count1007++; arriveBurst1007++; WATCH(arriveBurst1007);
                  if   (count1007 == secuencia1007){dropBurst1007 = dropBurst1007; pb1007 = (dropBurst1007/(arriveBurst1007 + dropBurst1007))*100; WATCH(pb1007);}
                  else {dropBurst1007 = dropBurst1007 + (secuencia1007 - count1007); WATCH(dropBurst1007); count1007 = secuencia1007; pb1007 = (dropBurst1007/(arriveBurst1007 + dropBurst1007))*100; WATCH(pb1007);} }
             else if   (destAddress == 7  && sourceAddress == 11) {secuencia1107 = recvBurst->getSecuencia(); count1107++; arriveBurst1107++; WATCH(arriveBurst1107);
                  if   (count1107 == secuencia1107){dropBurst1107 = dropBurst1107; pb1107 = (dropBurst1107/(arriveBurst1107 + dropBurst1107))*100; WATCH(pb1107);}
                  else {dropBurst1107 = dropBurst1107 + (secuencia1107 - count1107); WATCH(dropBurst1107); count1107 = secuencia1107; pb1107 = (dropBurst1107/(arriveBurst1107 + dropBurst1107))*100; WATCH(pb1107);} }
             else if   (destAddress == 7  && sourceAddress == 12) {secuencia1207 = recvBurst->getSecuencia(); count1207++; arriveBurst1207++; WATCH(arriveBurst1207);
                  if   (count1207 == secuencia1207){dropBurst1207 = dropBurst1207; pb1207 = (dropBurst1207/(arriveBurst1207 + dropBurst1207))*100; WATCH(pb1207);}
                  else {dropBurst1207 = dropBurst1207 + (secuencia1207 - count1207); WATCH(dropBurst1207); count1207 = secuencia1207; pb1207 = (dropBurst1207/(arriveBurst1207 + dropBurst1207))*100; WATCH(pb1207);} }
             else if   (destAddress == 7  && sourceAddress == 13) {secuencia1307 = recvBurst->getSecuencia(); count1307++; arriveBurst1307++; WATCH(arriveBurst1307);
                  if   (count1307 == secuencia1307){dropBurst1307 = dropBurst1307; pb1307 = (dropBurst1307/(arriveBurst1307 + dropBurst1307))*100; WATCH(pb1307);}
                  else {dropBurst1307 = dropBurst1307 + (secuencia1307 - count1307); WATCH(dropBurst1307); count1307 = secuencia1307; pb1307 = (dropBurst1307/(arriveBurst1307 + dropBurst1307))*100; WATCH(pb1307);} }
             else if   (destAddress == 7  && sourceAddress == 14) {secuencia1407 = recvBurst->getSecuencia(); count1407++; arriveBurst1407++; WATCH(arriveBurst1407);
                  if   (count1407 == secuencia1407){dropBurst1407 = dropBurst1407; pb1407 = (dropBurst1407/(arriveBurst1407 + dropBurst1407))*100; WATCH(pb1407);}
                  else {dropBurst1407 = dropBurst1407 + (secuencia1407 - count1407); WATCH(dropBurst1407); count1407 = secuencia1407; pb1407 = (dropBurst1407/(arriveBurst1407 + dropBurst1407))*100; WATCH(pb1407);} }


             //   if   (destAddress == 8  && sourceAddress == 8)  {secuencia0808 = recvBurst->getSecuencia(); count0808++; arriveBurst0808++; WATCH(arriveBurst0808);
             //   if   (count0808 == secuencia0808){dropBurst0808 = dropBurst0808; pb0808 = (dropBurst0808/(arriveBurst0808 + dropBurst0808))*100; WATCH(pb0808);}
             //   else {dropBurst0808 = dropBurst0808 + (secuencia0808 - count0808); WATCH(dropBurst0808); count0808 = secuencia0808; pb0808 = (dropBurst0808/(arriveBurst0808 + dropBurst0808))*100; WATCH(pb0808);} }
             if        (destAddress == 8  && sourceAddress == 1)  {secuencia0108 = recvBurst->getSecuencia(); count0108++; arriveBurst0108++; WATCH(arriveBurst0108);
                  if   (count0108 == secuencia0108){dropBurst0108 = dropBurst0108; pb0108 = (dropBurst0108/(arriveBurst0108 + dropBurst0108))*100; WATCH(pb0108);}
                  else {dropBurst0108 = dropBurst0108 + (secuencia0108 - count0108); WATCH(dropBurst0108); count0108 = secuencia0108; pb0108 = (dropBurst0108/(arriveBurst0108 + dropBurst0108))*100; WATCH(pb0108);} }
             else if   (destAddress == 8  && sourceAddress == 2)  {secuencia0208 = recvBurst->getSecuencia(); count0208++; arriveBurst0208++; WATCH(arriveBurst0208);
                  if   (count0208 == secuencia0208){dropBurst0208 = dropBurst0208; pb0208 = (dropBurst0208/(arriveBurst0208 + dropBurst0208))*100; WATCH(pb0208);}
                  else {dropBurst0208 = dropBurst0208 + (secuencia0208 - count0208); WATCH(dropBurst0208); count0208 = secuencia0208; pb0208 = (dropBurst0208/(arriveBurst0208 + dropBurst0208))*100; WATCH(pb0208);} }
             else if   (destAddress == 8  && sourceAddress == 3)  {secuencia0308 = recvBurst->getSecuencia(); count0308++; arriveBurst0308++; WATCH(arriveBurst0308);
                  if   (count0308 == secuencia0308){dropBurst0308 = dropBurst0308; pb0308 = (dropBurst0308/(arriveBurst0308 + dropBurst0308))*100; WATCH(pb0308);}
                  else {dropBurst0308 = dropBurst0308 + (secuencia0308 - count0308); WATCH(dropBurst0308); count0308 = secuencia0308; pb0308 = (dropBurst0308/(arriveBurst0308 + dropBurst0308))*100; WATCH(pb0308);} }
             else if   (destAddress == 8  && sourceAddress == 4)  {secuencia0408 = recvBurst->getSecuencia(); count0408++; arriveBurst0408++; WATCH(arriveBurst0408);
                  if   (count0408 == secuencia0408){dropBurst0408 = dropBurst0408; pb0408 = (dropBurst0408/(arriveBurst0408 + dropBurst0408))*100; WATCH(pb0408);}
                  else {dropBurst0408 = dropBurst0408 + (secuencia0408 - count0408); WATCH(dropBurst0408); count0408 = secuencia0408; pb0408 = (dropBurst0408/(arriveBurst0408 + dropBurst0408))*100; WATCH(pb0408);} }
             else if   (destAddress == 8  && sourceAddress == 5)  {secuencia0508 = recvBurst->getSecuencia(); count0508++; arriveBurst0508++; WATCH(arriveBurst0508);
                  if   (count0508 == secuencia0508){dropBurst0508 = dropBurst0508; pb0508 = (dropBurst0508/(arriveBurst0508 + dropBurst0508))*100; WATCH(pb0508);}
                  else {dropBurst0508 = dropBurst0508 + (secuencia0508 - count0508); WATCH(dropBurst0508); count0508 = secuencia0508; pb0508 = (dropBurst0508/(arriveBurst0508 + dropBurst0508))*100; WATCH(pb0508);} }
             else if   (destAddress == 8  && sourceAddress == 6)  {secuencia0608 = recvBurst->getSecuencia(); count0608++; arriveBurst0608++; WATCH(arriveBurst0608);
                  if   (count0608 == secuencia0608){dropBurst0608 = dropBurst0608; pb0608 = (dropBurst0608/(arriveBurst0608 + dropBurst0608))*100; WATCH(pb0608);}
                  else {dropBurst0608 = dropBurst0608 + (secuencia0608 - count0608); WATCH(dropBurst0608); count0608 = secuencia0608; pb0608 = (dropBurst0608/(arriveBurst0608 + dropBurst0608))*100; WATCH(pb0608);} }
             else if   (destAddress == 8  && sourceAddress == 7)  {secuencia0708 = recvBurst->getSecuencia(); count0708++; arriveBurst0708++; WATCH(arriveBurst0708);
                  if   (count0708 == secuencia0708){dropBurst0708 = dropBurst0708; pb0708 = (dropBurst0708/(arriveBurst0708 + dropBurst0708))*100; WATCH(pb0708);}
                  else {dropBurst0708 = dropBurst0708 + (secuencia0708 - count0708); WATCH(dropBurst0708); count0708 = secuencia0708; pb0708 = (dropBurst0708/(arriveBurst0708 + dropBurst0708))*100; WATCH(pb0708);} }
             else if   (destAddress == 8  && sourceAddress == 9)  {secuencia0908 = recvBurst->getSecuencia(); count0908++; arriveBurst0908++; WATCH(arriveBurst0908);
                  if   (count0908 == secuencia0908){dropBurst0908 = dropBurst0908; pb0908 = (dropBurst0908/(arriveBurst0908 + dropBurst0908))*100; WATCH(pb0908);}
                  else {dropBurst0908 = dropBurst0908 + (secuencia0908 - count0908); WATCH(dropBurst0908); count0908 = secuencia0908; pb0908 = (dropBurst0908/(arriveBurst0908 + dropBurst0908))*100; WATCH(pb0908);} }
             else if   (destAddress == 8  && sourceAddress == 10) {secuencia1008 = recvBurst->getSecuencia(); count1008++; arriveBurst1008++; WATCH(arriveBurst1008);
                  if   (count1008 == secuencia1008){dropBurst1008 = dropBurst1008; pb1008 = (dropBurst1008/(arriveBurst1008 + dropBurst1008))*100; WATCH(pb1008);}
                  else {dropBurst1008 = dropBurst1008 + (secuencia1008 - count1008); WATCH(dropBurst1008); count1008 = secuencia1008; pb1008 = (dropBurst1008/(arriveBurst1008 + dropBurst1008))*100; WATCH(pb1008);} }
             else if   (destAddress == 8  && sourceAddress == 11) {secuencia1108 = recvBurst->getSecuencia(); count1108++; arriveBurst1108++; WATCH(arriveBurst1108);
                  if   (count1108 == secuencia1108){dropBurst1108 = dropBurst1108; pb1108 = (dropBurst1108/(arriveBurst1108 + dropBurst1108))*100; WATCH(pb1108);}
                  else {dropBurst1108 = dropBurst1108 + (secuencia1108 - count1108); WATCH(dropBurst1108); count1108 = secuencia1108; pb1108 = (dropBurst1108/(arriveBurst1108 + dropBurst1108))*100; WATCH(pb1108);} }
             else if   (destAddress == 8  && sourceAddress == 12) {secuencia1208 = recvBurst->getSecuencia(); count1208++; arriveBurst1208++; WATCH(arriveBurst1208);
                  if   (count1208 == secuencia1208){dropBurst1208 = dropBurst1208; pb1208 = (dropBurst1208/(arriveBurst1208 + dropBurst1208))*100; WATCH(pb1208);}
                  else {dropBurst1208 = dropBurst1208 + (secuencia1208 - count1208); WATCH(dropBurst1208); count1208 = secuencia1208; pb1208 = (dropBurst1208/(arriveBurst1208 + dropBurst1208))*100; WATCH(pb1208);} }
             else if   (destAddress == 8  && sourceAddress == 13) {secuencia1308 = recvBurst->getSecuencia(); count1308++; arriveBurst1308++; WATCH(arriveBurst1308);
                  if   (count1308 == secuencia1308){dropBurst1308 = dropBurst1308; pb1308 = (dropBurst1308/(arriveBurst1308 + dropBurst1308))*100; WATCH(pb1308);}
                  else {dropBurst1308 = dropBurst1308 + (secuencia1308 - count1308); WATCH(dropBurst1308); count1308 = secuencia1308; pb1308 = (dropBurst1308/(arriveBurst1308 + dropBurst1308))*100; WATCH(pb1308);} }
             else if   (destAddress == 8  && sourceAddress == 14) {secuencia1408 = recvBurst->getSecuencia(); count1408++; arriveBurst1408++; WATCH(arriveBurst1408);
                  if   (count1408 == secuencia1408){dropBurst1408 = dropBurst1408; pb1408 = (dropBurst1408/(arriveBurst1408 + dropBurst1408))*100; WATCH(pb1408);}
                  else {dropBurst1408 = dropBurst1408 + (secuencia1408 - count1408); WATCH(dropBurst1408); count1408 = secuencia1408; pb1408 = (dropBurst1408/(arriveBurst1408 + dropBurst1408))*100; WATCH(pb1408);} }


             //   if   (destAddress == 9  && sourceAddress == 9)  {secuencia0909 = recvBurst->getSecuencia(); count0909++; arriveBurst0909++; WATCH(arriveBurst0909);
             //   if   (count0909 == secuencia0909){dropBurst0909 = dropBurst0909; pb0909 = (dropBurst0909/(arriveBurst0909 + dropBurst0909))*100; WATCH(pb0909);}
             //   else {dropBurst0909 = dropBurst0909 + (secuencia0909 - count0909); WATCH(dropBurst0909); count0909 = secuencia0909; pb0909 = (dropBurst0909/(arriveBurst0909 + dropBurst0909))*100; WATCH(pb0909);} }
             if        (destAddress == 9  && sourceAddress == 1)  {secuencia0109 = recvBurst->getSecuencia(); count0109++; arriveBurst0109++; WATCH(arriveBurst0109);
                  if   (count0109 == secuencia0109){dropBurst0109 = dropBurst0109; pb0109 = (dropBurst0109/(arriveBurst0109 + dropBurst0109))*100; WATCH(pb0109);}
                  else {dropBurst0109 = dropBurst0109 + (secuencia0109 - count0109); WATCH(dropBurst0109); count0109 = secuencia0109; pb0109 = (dropBurst0109/(arriveBurst0109 + dropBurst0109))*100; WATCH(pb0109);} }
             else if   (destAddress == 9  && sourceAddress == 2)  {secuencia0209 = recvBurst->getSecuencia(); count0209++; arriveBurst0209++; WATCH(arriveBurst0209);
                  if   (count0209 == secuencia0209){dropBurst0209 = dropBurst0209; pb0209 = (dropBurst0209/(arriveBurst0209 + dropBurst0209))*100; WATCH(pb0209);}
                  else {dropBurst0209 = dropBurst0209 + (secuencia0209 - count0209); WATCH(dropBurst0209); count0209 = secuencia0209; pb0209 = (dropBurst0209/(arriveBurst0209 + dropBurst0209))*100; WATCH(pb0209);} }
             else if   (destAddress == 9  && sourceAddress == 3)  {secuencia0309 = recvBurst->getSecuencia(); count0309++; arriveBurst0309++; WATCH(arriveBurst0309);
                  if   (count0309 == secuencia0309){dropBurst0309 = dropBurst0309; pb0309 = (dropBurst0309/(arriveBurst0309 + dropBurst0309))*100; WATCH(pb0309);}
                  else {dropBurst0309 = dropBurst0309 + (secuencia0309 - count0309); WATCH(dropBurst0309); count0309 = secuencia0309; pb0309 = (dropBurst0309/(arriveBurst0309 + dropBurst0309))*100; WATCH(pb0309);} }
             else if   (destAddress == 9  && sourceAddress == 4)  {secuencia0409 = recvBurst->getSecuencia(); count0409++; arriveBurst0409++; WATCH(arriveBurst0409);
                  if   (count0409 == secuencia0409){dropBurst0409 = dropBurst0409; pb0409 = (dropBurst0409/(arriveBurst0409 + dropBurst0409))*100; WATCH(pb0409);}
                  else {dropBurst0409 = dropBurst0409 + (secuencia0409 - count0409); WATCH(dropBurst0409); count0409 = secuencia0409; pb0409 = (dropBurst0409/(arriveBurst0409 + dropBurst0409))*100; WATCH(pb0409);} }
             else if   (destAddress == 9  && sourceAddress == 5)  {secuencia0509 = recvBurst->getSecuencia(); count0509++; arriveBurst0509++; WATCH(arriveBurst0509);
                  if   (count0509 == secuencia0509){dropBurst0509 = dropBurst0509; pb0509 = (dropBurst0509/(arriveBurst0509 + dropBurst0509))*100; WATCH(pb0509);}
                  else {dropBurst0509 = dropBurst0509 + (secuencia0509 - count0509); WATCH(dropBurst0509); count0509 = secuencia0509; pb0509 = (dropBurst0509/(arriveBurst0509 + dropBurst0509))*100; WATCH(pb0509);} }
             else if   (destAddress == 9  && sourceAddress == 6)  {secuencia0609 = recvBurst->getSecuencia(); count0609++; arriveBurst0609++; WATCH(arriveBurst0609);
                  if   (count0609 == secuencia0609){dropBurst0609 = dropBurst0609; pb0609 = (dropBurst0609/(arriveBurst0609 + dropBurst0609))*100; WATCH(pb0609);}
                  else {dropBurst0609 = dropBurst0609 + (secuencia0609 - count0609); WATCH(dropBurst0609); count0609 = secuencia0609; pb0609 = (dropBurst0609/(arriveBurst0609 + dropBurst0609))*100; WATCH(pb0609);} }
             else if   (destAddress == 9  && sourceAddress == 7)  {secuencia0709 = recvBurst->getSecuencia(); count0709++; arriveBurst0709++; WATCH(arriveBurst0709);
                  if   (count0709 == secuencia0709){dropBurst0709 = dropBurst0709; pb0709 = (dropBurst0709/(arriveBurst0709 + dropBurst0709))*100; WATCH(pb0709);}
                  else {dropBurst0709 = dropBurst0709 + (secuencia0709 - count0709); WATCH(dropBurst0709); count0709 = secuencia0709; pb0709 = (dropBurst0709/(arriveBurst0709 + dropBurst0709))*100; WATCH(pb0709);} }
             else if   (destAddress == 9  && sourceAddress == 8)  {secuencia0809 = recvBurst->getSecuencia(); count0809++; arriveBurst0809++; WATCH(arriveBurst0809);
                  if   (count0809 == secuencia0809){dropBurst0809 = dropBurst0809; pb0809 = (dropBurst0809/(arriveBurst0809 + dropBurst0809))*100; WATCH(pb0809);}
                  else {dropBurst0809 = dropBurst0809 + (secuencia0809 - count0809); WATCH(dropBurst0809); count0809 = secuencia0809; pb0809 = (dropBurst0809/(arriveBurst0809 + dropBurst0809))*100; WATCH(pb0809);} }
             else if   (destAddress == 9  && sourceAddress == 10) {secuencia1009 = recvBurst->getSecuencia(); count1009++; arriveBurst1009++; WATCH(arriveBurst1009);
                  if   (count1009 == secuencia1009){dropBurst1009 = dropBurst1009; pb1009 = (dropBurst1009/(arriveBurst1009 + dropBurst1009))*100; WATCH(pb1009);}
                  else {dropBurst1009 = dropBurst1009 + (secuencia1009 - count1009); WATCH(dropBurst1009); count1009 = secuencia1009; pb1009 = (dropBurst1009/(arriveBurst1009 + dropBurst1009))*100; WATCH(pb1009);} }
             else if   (destAddress == 9  && sourceAddress == 11) {secuencia1109 = recvBurst->getSecuencia(); count1109++; arriveBurst1109++; WATCH(arriveBurst1109);
                  if   (count1109 == secuencia1109){dropBurst1109 = dropBurst1109; pb1109 = (dropBurst1109/(arriveBurst1109 + dropBurst1109))*100; WATCH(pb1109);}
                  else {dropBurst1109 = dropBurst1109 + (secuencia1109 - count1109); WATCH(dropBurst1109); count1109 = secuencia1109; pb1109 = (dropBurst1109/(arriveBurst1109 + dropBurst1109))*100; WATCH(pb1109);} }
             else if   (destAddress == 9  && sourceAddress == 12) {secuencia1209 = recvBurst->getSecuencia(); count1209++; arriveBurst1209++; WATCH(arriveBurst1209);
                  if   (count1209 == secuencia1209){dropBurst1209 = dropBurst1209; pb1209 = (dropBurst1209/(arriveBurst1209 + dropBurst1209))*100; WATCH(pb1209);}
                  else {dropBurst1209 = dropBurst1209 + (secuencia1209 - count1209); WATCH(dropBurst1209); count1209 = secuencia1209; pb1209 = (dropBurst1209/(arriveBurst1209 + dropBurst1209))*100; WATCH(pb1209);} }
             else if   (destAddress == 9  && sourceAddress == 13) {secuencia1309 = recvBurst->getSecuencia(); count1309++; arriveBurst1309++; WATCH(arriveBurst1309);
                  if   (count1309 == secuencia1309){dropBurst1309 = dropBurst1309; pb1309 = (dropBurst1309/(arriveBurst1309 + dropBurst1309))*100; WATCH(pb1309);}
                  else {dropBurst1309 = dropBurst1309 + (secuencia1309 - count1309); WATCH(dropBurst1309); count1309 = secuencia1309; pb1309 = (dropBurst1309/(arriveBurst1309 + dropBurst1309))*100; WATCH(pb1309);} }
             else if   (destAddress == 9  && sourceAddress == 14) {secuencia1409 = recvBurst->getSecuencia(); count1409++; arriveBurst1409++; WATCH(arriveBurst1409);
                  if   (count1409 == secuencia1409){dropBurst1409 = dropBurst1409; pb1409 = (dropBurst1409/(arriveBurst1409 + dropBurst1409))*100; WATCH(pb1409);}
                  else {dropBurst1409 = dropBurst1409 + (secuencia1409 - count1409); WATCH(dropBurst1409); count1409 = secuencia1409; pb1409 = (dropBurst1409/(arriveBurst1409 + dropBurst1409))*100; WATCH(pb1409);} }

             //   if   (destAddress == 10 && sourceAddress == 10) {secuencia1010 = recvBurst->getSecuencia(); count1010++; arriveBurst1010++; WATCH(arriveBurst1010);
             //   if   (count1010 == secuencia1010){dropBurst1010 = dropBurst1010; pb1010 = (dropBurst1010/(arriveBurst1010 + dropBurst1010))*100; WATCH(pb1010);}
             //   else {dropBurst1010 = dropBurst1010 + (secuencia1010 - count1010); WATCH(dropBurst1010); count1010 = secuencia1010; pb1010 = (dropBurst1010/(arriveBurst1010 + dropBurst1010))*100; WATCH(pb1010);} }
             if        (destAddress == 10 && sourceAddress == 1)  {secuencia0110 = recvBurst->getSecuencia(); count0110++; arriveBurst0110++; WATCH(arriveBurst0110);
                  if   (count0110 == secuencia0110){dropBurst0110 = dropBurst0110; pb0110 = (dropBurst0110/(arriveBurst0110 + dropBurst0110))*100; WATCH(pb0110);}
                  else {dropBurst0110 = dropBurst0110 + (secuencia0110 - count0110); WATCH(dropBurst0110); count0110 = secuencia0110; pb0110 = (dropBurst0110/(arriveBurst0110 + dropBurst0110))*100; WATCH(pb0110);} }
             else if   (destAddress == 10 && sourceAddress == 2)  {secuencia0210 = recvBurst->getSecuencia(); count0210++; arriveBurst0210++; WATCH(arriveBurst0210);
                  if   (count0210 == secuencia0210){dropBurst0210 = dropBurst0210; pb0210 = (dropBurst0210/(arriveBurst0210 + dropBurst0210))*100; WATCH(pb0210);}
                  else {dropBurst0210 = dropBurst0210 + (secuencia0210 - count0210); WATCH(dropBurst0210); count0210 = secuencia0210; pb0210 = (dropBurst0210/(arriveBurst0210 + dropBurst0210))*100; WATCH(pb0210);} }
             else if   (destAddress == 10 && sourceAddress == 3)  {secuencia0310 = recvBurst->getSecuencia(); count0310++; arriveBurst0310++; WATCH(arriveBurst0310);
                  if   (count0310 == secuencia0310){dropBurst0310 = dropBurst0310; pb0310 = (dropBurst0310/(arriveBurst0310 + dropBurst0310))*100; WATCH(pb0310);}
                  else {dropBurst0310 = dropBurst0310 + (secuencia0310 - count0310); WATCH(dropBurst0310); count0310 = secuencia0310; pb0310 = (dropBurst0310/(arriveBurst0310 + dropBurst0310))*100; WATCH(pb0310);} }
             else if   (destAddress == 10 && sourceAddress == 4)  {secuencia0410 = recvBurst->getSecuencia(); count0410++; arriveBurst0410++; WATCH(arriveBurst0410);
                  if   (count0410 == secuencia0410){dropBurst0410 = dropBurst0410; pb0410 = (dropBurst0410/(arriveBurst0410 + dropBurst0410))*100; WATCH(pb0410);}
                  else {dropBurst0410 = dropBurst0410 + (secuencia0410 - count0410); WATCH(dropBurst0410); count0410 = secuencia0410; pb0410 = (dropBurst0410/(arriveBurst0410 + dropBurst0410))*100; WATCH(pb0410);} }
             else if   (destAddress == 10 && sourceAddress == 5)  {secuencia0510 = recvBurst->getSecuencia(); count0510++; arriveBurst0510++; WATCH(arriveBurst0510);
                  if   (count0510 == secuencia0510){dropBurst0510 = dropBurst0510; pb0510 = (dropBurst0510/(arriveBurst0510 + dropBurst0510))*100; WATCH(pb0510);}
                  else {dropBurst0510 = dropBurst0510 + (secuencia0510 - count0510); WATCH(dropBurst0510); count0510 = secuencia0510; pb0510 = (dropBurst0510/(arriveBurst0510 + dropBurst0510))*100; WATCH(pb0510);} }
             else if   (destAddress == 10 && sourceAddress == 6)  {secuencia0610 = recvBurst->getSecuencia(); count0610++; arriveBurst0610++; WATCH(arriveBurst0610);
                  if   (count0610 == secuencia0610){dropBurst0610 = dropBurst0610; pb0610 = (dropBurst0610/(arriveBurst0610 + dropBurst0610))*100; WATCH(pb0610);}
                  else {dropBurst0610 = dropBurst0610 + (secuencia0610 - count0610); WATCH(dropBurst0610); count0610 = secuencia0610; pb0610 = (dropBurst0610/(arriveBurst0610 + dropBurst0610))*100; WATCH(pb0610);} }
             else if   (destAddress == 10 && sourceAddress == 7)  {secuencia0710 = recvBurst->getSecuencia(); count0710++; arriveBurst0710++; WATCH(arriveBurst0710);
                  if   (count0710 == secuencia0710){dropBurst0710 = dropBurst0710; pb0710 = (dropBurst0710/(arriveBurst0710 + dropBurst0710))*100; WATCH(pb0710);}
                  else {dropBurst0710 = dropBurst0710 + (secuencia0710 - count0710); WATCH(dropBurst0710); count0710 = secuencia0710; pb0710 = (dropBurst0710/(arriveBurst0710 + dropBurst0710))*100; WATCH(pb0710);} }
             else if   (destAddress == 10 && sourceAddress == 8)  {secuencia0810 = recvBurst->getSecuencia(); count0810++; arriveBurst0810++; WATCH(arriveBurst0810);
                  if   (count0810 == secuencia0810){dropBurst0810 = dropBurst0810; pb0810 = (dropBurst0810/(arriveBurst0810 + dropBurst0810))*100; WATCH(pb0810);}
                  else {dropBurst0810 = dropBurst0810 + (secuencia0810 - count0810); WATCH(dropBurst0810); count0810 = secuencia0810; pb0810 = (dropBurst0810/(arriveBurst0810 + dropBurst0810))*100; WATCH(pb0810);} }
             else if   (destAddress == 10 && sourceAddress == 9)  {secuencia0910 = recvBurst->getSecuencia(); count0910++; arriveBurst0910++; WATCH(arriveBurst0910);
                  if   (count0910 == secuencia0910){dropBurst0910 = dropBurst0910; pb0910 = (dropBurst0910/(arriveBurst0910 + dropBurst0910))*100; WATCH(pb0910);}
                  else {dropBurst0910 = dropBurst0910 + (secuencia0910 - count0910); WATCH(dropBurst0910); count0910 = secuencia0910; pb0910 = (dropBurst0910/(arriveBurst0910 + dropBurst0910))*100; WATCH(pb0910);} }
             else if   (destAddress == 10 && sourceAddress == 11) {secuencia1110 = recvBurst->getSecuencia(); count1110++; arriveBurst1110++; WATCH(arriveBurst1110);
                  if   (count1110 == secuencia1110){dropBurst1110 = dropBurst1110; pb1110 = (dropBurst1110/(arriveBurst1110 + dropBurst1110))*100; WATCH(pb1110);}
                  else {dropBurst1110 = dropBurst1110 + (secuencia1110 - count1110); WATCH(dropBurst1110); count1110 = secuencia1110; pb1110 = (dropBurst1110/(arriveBurst1110 + dropBurst1110))*100; WATCH(pb1110);} }
             else if   (destAddress == 10 && sourceAddress == 12) {secuencia1210 = recvBurst->getSecuencia(); count1210++; arriveBurst1210++; WATCH(arriveBurst1210);
                  if   (count1210 == secuencia1210){dropBurst1210 = dropBurst1210; pb1210 = (dropBurst1210/(arriveBurst1210 + dropBurst1210))*100; WATCH(pb1210);}
                  else {dropBurst1210 = dropBurst1210 + (secuencia1210 - count1210); WATCH(dropBurst1210); count1210 = secuencia1210; pb1210 = (dropBurst1210/(arriveBurst1210 + dropBurst1210))*100; WATCH(pb1210);} }
             else if   (destAddress == 10 && sourceAddress == 13) {secuencia1310 = recvBurst->getSecuencia(); count1310++; arriveBurst1310++; WATCH(arriveBurst1310);
                  if   (count1310 == secuencia1310){dropBurst1310 = dropBurst1310; pb1310 = (dropBurst1310/(arriveBurst1310 + dropBurst1310))*100; WATCH(pb1310);}
                  else {dropBurst1310 = dropBurst1310 + (secuencia1310 - count1310); WATCH(dropBurst1310); count1310 = secuencia1310; pb1310 = (dropBurst1310/(arriveBurst1310 + dropBurst1310))*100; WATCH(pb1310);} }
             else if   (destAddress == 10 && sourceAddress == 14) {secuencia1410 = recvBurst->getSecuencia(); count1410++; arriveBurst1410++; WATCH(arriveBurst1410);
                  if   (count1410 == secuencia1410){dropBurst1410 = dropBurst1410; pb1410 = (dropBurst1410/(arriveBurst1410 + dropBurst1410))*100; WATCH(pb1410);}
                  else {dropBurst1410 = dropBurst1410 + (secuencia1410 - count1410); WATCH(dropBurst1410); count1410 = secuencia1410; pb1410 = (dropBurst1410/(arriveBurst1410 + dropBurst1410))*100; WATCH(pb1410);} }


             //   if   (destAddress == 11 && sourceAddress == 11) {secuencia1111 = recvBurst->getSecuencia(); count1111++; arriveBurst1111++; WATCH(arriveBurst1111);
             //   if   (count1111 == secuencia1111){dropBurst1111 = dropBurst1111; pb1111 = (dropBurst1111/(arriveBurst1111 + dropBurst1111))*100; WATCH(pb1111);}
             //   else {dropBurst1111 = dropBurst1111 + (secuencia1111 - count1111); WATCH(dropBurst1111); count1111 = secuencia1111; pb1111 = (dropBurst1111/(arriveBurst1111 + dropBurst1111))*100; WATCH(pb1111);} }
             if        (destAddress == 11 && sourceAddress == 1)  {secuencia0111 = recvBurst->getSecuencia(); count0111++; arriveBurst0111++; WATCH(arriveBurst0111);
                  if   (count0111 == secuencia0111){dropBurst0111 = dropBurst0111; pb0111 = (dropBurst0111/(arriveBurst0111 + dropBurst0111))*100; WATCH(pb0111);}
                  else {dropBurst0111 = dropBurst0111 + (secuencia0111 - count0111); WATCH(dropBurst0111); count0111 = secuencia0111; pb0111 = (dropBurst0111/(arriveBurst0111 + dropBurst0111))*100; WATCH(pb0111);} }
             else if   (destAddress == 11 && sourceAddress == 2)  {secuencia0211 = recvBurst->getSecuencia(); count0211++; arriveBurst0211++; WATCH(arriveBurst0211);
                  if   (count0211 == secuencia0211){dropBurst0211 = dropBurst0211; pb0211 = (dropBurst0211/(arriveBurst0211 + dropBurst0211))*100; WATCH(pb0211);}
                  else {dropBurst0211 = dropBurst0211 + (secuencia0211 - count0211); WATCH(dropBurst0211); count0211 = secuencia0211; pb0211 = (dropBurst0211/(arriveBurst0211 + dropBurst0211))*100; WATCH(pb0211);} }
             else if   (destAddress == 11 && sourceAddress == 3)  {secuencia0311 = recvBurst->getSecuencia(); count0311++; arriveBurst0311++; WATCH(arriveBurst0311);
                  if   (count0311 == secuencia0311){dropBurst0311 = dropBurst0311; pb0311 = (dropBurst0311/(arriveBurst0311 + dropBurst0311))*100; WATCH(pb0311);}
                  else {dropBurst0311 = dropBurst0311 + (secuencia0311 - count0311); WATCH(dropBurst0311); count0311 = secuencia0311; pb0311 = (dropBurst0311/(arriveBurst0311 + dropBurst0311))*100; WATCH(pb0311);} }
             else if   (destAddress == 11 && sourceAddress == 4)  {secuencia0411 = recvBurst->getSecuencia(); count0411++; arriveBurst0411++; WATCH(arriveBurst0411);
                  if   (count0411 == secuencia0411){dropBurst0411 = dropBurst0411; pb0411 = (dropBurst0411/(arriveBurst0411 + dropBurst0411))*100; WATCH(pb0411);}
                  else {dropBurst0411 = dropBurst0411 + (secuencia0411 - count0411); WATCH(dropBurst0411); count0411 = secuencia0411; pb0411 = (dropBurst0411/(arriveBurst0411 + dropBurst0411))*100; WATCH(pb0411);} }
             else if   (destAddress == 11 && sourceAddress == 5)  {secuencia0511 = recvBurst->getSecuencia(); count0511++; arriveBurst0511++; WATCH(arriveBurst0511);
                  if   (count0511 == secuencia0511){dropBurst0511 = dropBurst0511; pb0511 = (dropBurst0511/(arriveBurst0511 + dropBurst0511))*100; WATCH(pb0511);}
                  else {dropBurst0511 = dropBurst0511 + (secuencia0511 - count0511); WATCH(dropBurst0511); count0511 = secuencia0511; pb0511 = (dropBurst0511/(arriveBurst0511 + dropBurst0511))*100; WATCH(pb0511);} }
             else if   (destAddress == 11 && sourceAddress == 6)  {secuencia0611 = recvBurst->getSecuencia(); count0611++; arriveBurst0611++; WATCH(arriveBurst0611);
                  if   (count0611 == secuencia0611){dropBurst0611 = dropBurst0611; pb0611 = (dropBurst0611/(arriveBurst0611 + dropBurst0611))*100; WATCH(pb0611);}
                  else {dropBurst0611 = dropBurst0611 + (secuencia0611 - count0611); WATCH(dropBurst0611); count0611 = secuencia0611; pb0611 = (dropBurst0611/(arriveBurst0611 + dropBurst0611))*100; WATCH(pb0611);} }
             else if   (destAddress == 11 && sourceAddress == 7)  {secuencia0711 = recvBurst->getSecuencia(); count0711++; arriveBurst0711++; WATCH(arriveBurst0711);
                  if   (count0711 == secuencia0711){dropBurst0711 = dropBurst0711; pb0711 = (dropBurst0711/(arriveBurst0711 + dropBurst0711))*100; WATCH(pb0711);}
                  else {dropBurst0711 = dropBurst0711 + (secuencia0711 - count0711); WATCH(dropBurst0711); count0711 = secuencia0711; pb0711 = (dropBurst0711/(arriveBurst0711 + dropBurst0711))*100; WATCH(pb0711);} }
             else if   (destAddress == 11 && sourceAddress == 8)  {secuencia0811 = recvBurst->getSecuencia(); count0811++; arriveBurst0811++; WATCH(arriveBurst0811);
                  if   (count0811 == secuencia0811){dropBurst0811 = dropBurst0811; pb0811 = (dropBurst0811/(arriveBurst0811 + dropBurst0811))*100; WATCH(pb0811);}
                  else {dropBurst0811 = dropBurst0811 + (secuencia0811 - count0811); WATCH(dropBurst0811); count0811 = secuencia0811; pb0811 = (dropBurst0811/(arriveBurst0811 + dropBurst0811))*100; WATCH(pb0811);} }
             else if   (destAddress == 11 && sourceAddress == 9)  {secuencia0911 = recvBurst->getSecuencia(); count0911++; arriveBurst0911++; WATCH(arriveBurst0911);
                  if   (count0911 == secuencia0911){dropBurst0911 = dropBurst0911; pb0911 = (dropBurst0911/(arriveBurst0911 + dropBurst0911))*100; WATCH(pb0911);}
                  else {dropBurst0911 = dropBurst0911 + (secuencia0911 - count0911); WATCH(dropBurst0911); count0911 = secuencia0911; pb0911 = (dropBurst0911/(arriveBurst0911 + dropBurst0911))*100; WATCH(pb0911);} }
             else if   (destAddress == 11 && sourceAddress == 10) {secuencia1011 = recvBurst->getSecuencia(); count1011++; arriveBurst1011++; WATCH(arriveBurst1011);
                  if   (count1011 == secuencia1011){dropBurst1011 = dropBurst1011; pb1011 = (dropBurst1011/(arriveBurst1011 + dropBurst1011))*100; WATCH(pb1011);}
                  else {dropBurst1011 = dropBurst1011 + (secuencia1011 - count1011); WATCH(dropBurst1011); count1011 = secuencia1011; pb1011 = (dropBurst1011/(arriveBurst1011 + dropBurst1011))*100; WATCH(pb1011);} }
             else if   (destAddress == 11 && sourceAddress == 12) {secuencia1211 = recvBurst->getSecuencia(); count1211++; arriveBurst1211++; WATCH(arriveBurst1211);
                  if   (count1211 == secuencia1211){dropBurst1211 = dropBurst1211; pb1211 = (dropBurst1211/(arriveBurst1211 + dropBurst1211))*100; WATCH(pb1211);}
                  else {dropBurst1211 = dropBurst1211 + (secuencia1211 - count1211); WATCH(dropBurst1211); count1211 = secuencia1211; pb1211 = (dropBurst1211/(arriveBurst1211 + dropBurst1211))*100; WATCH(pb1211);} }
             else if   (destAddress == 11 && sourceAddress == 13) {secuencia1311 = recvBurst->getSecuencia(); count1311++; arriveBurst1311++; WATCH(arriveBurst1311);
                  if   (count1311 == secuencia1311){dropBurst1311 = dropBurst1311; pb1311 = (dropBurst1311/(arriveBurst1311 + dropBurst1311))*100; WATCH(pb1311);}
                  else {dropBurst1311 = dropBurst1311 + (secuencia1311 - count1311); WATCH(dropBurst1311); count1311 = secuencia1311; pb1311 = (dropBurst1311/(arriveBurst1311 + dropBurst1311))*100; WATCH(pb1311);} }
             else if   (destAddress == 11 && sourceAddress == 14) {secuencia1411 = recvBurst->getSecuencia(); count1411++; arriveBurst1411++; WATCH(arriveBurst1411);
                  if   (count1411 == secuencia1411){dropBurst1411 = dropBurst1411; pb1411 = (dropBurst1411/(arriveBurst1411 + dropBurst1411))*100; WATCH(pb1411);}
                  else {dropBurst1411 = dropBurst1411 + (secuencia1411 - count1411); WATCH(dropBurst1411); count1411 = secuencia1411; pb1411 = (dropBurst1411/(arriveBurst1411 + dropBurst1411))*100; WATCH(pb1411);} }


             //   if   (destAddress == 12 && sourceAddress == 12) {secuencia1212 = recvBurst->getSecuencia(); count1212++; arriveBurst1212++; WATCH(arriveBurst1212);
             //   if   (count1212 == secuencia1212){dropBurst1212 = dropBurst1212; pb1212 = (dropBurst1212/(arriveBurst1212 + dropBurst1212))*100; WATCH(pb1212);}
             //   else {dropBurst1212 = dropBurst1212 + (secuencia1212 - count1212); WATCH(dropBurst1212); count1212 = secuencia1212; pb1212 = (dropBurst1212/(arriveBurst1212 + dropBurst1212))*100; WATCH(pb1212);} }
             if        (destAddress == 12 && sourceAddress == 1)  {secuencia0112 = recvBurst->getSecuencia(); count0112++; arriveBurst0112++; WATCH(arriveBurst0112);
                  if   (count0112 == secuencia0112){dropBurst0112 = dropBurst0112; pb0112 = (dropBurst0112/(arriveBurst0112 + dropBurst0112))*100; WATCH(pb0112);}
                  else {dropBurst0112 = dropBurst0112 + (secuencia0112 - count0112); WATCH(dropBurst0112); count0112 = secuencia0112; pb0112 = (dropBurst0112/(arriveBurst0112 + dropBurst0112))*100; WATCH(pb0112);} }
             else if   (destAddress == 12 && sourceAddress == 2)  {secuencia0212 = recvBurst->getSecuencia(); count0212++; arriveBurst0212++; WATCH(arriveBurst0212);
                  if   (count0212 == secuencia0212){dropBurst0212 = dropBurst0212; pb0212 = (dropBurst0212/(arriveBurst0212 + dropBurst0212))*100; WATCH(pb0212);}
                  else {dropBurst0212 = dropBurst0212 + (secuencia0212 - count0212); WATCH(dropBurst0212); count0212 = secuencia0212; pb0212 = (dropBurst0212/(arriveBurst0212 + dropBurst0212))*100; WATCH(pb0212);} }
             else if   (destAddress == 12 && sourceAddress == 3)  {secuencia0312 = recvBurst->getSecuencia(); count0312++; arriveBurst0312++; WATCH(arriveBurst0312);
                  if   (count0312 == secuencia0312){dropBurst0312 = dropBurst0312; pb0312 = (dropBurst0312/(arriveBurst0312 + dropBurst0312))*100; WATCH(pb0312);}
                  else {dropBurst0312 = dropBurst0312 + (secuencia0312 - count0312); WATCH(dropBurst0312); count0312 = secuencia0312; pb0312 = (dropBurst0312/(arriveBurst0312 + dropBurst0312))*100; WATCH(pb0312);} }
             else if   (destAddress == 12 && sourceAddress == 4)  {secuencia0412 = recvBurst->getSecuencia(); count0412++; arriveBurst0412++; WATCH(arriveBurst0412);
                  if   (count0412 == secuencia0412){dropBurst0412 = dropBurst0412; pb0412 = (dropBurst0412/(arriveBurst0412 + dropBurst0412))*100; WATCH(pb0412);}
                  else {dropBurst0412 = dropBurst0412 + (secuencia0412 - count0412); WATCH(dropBurst0412); count0412 = secuencia0412; pb0412 = (dropBurst0412/(arriveBurst0412 + dropBurst0412))*100; WATCH(pb0412);} }
             else if   (destAddress == 12 && sourceAddress == 5)  {secuencia0512 = recvBurst->getSecuencia(); count0512++; arriveBurst0512++; WATCH(arriveBurst0512);
                  if   (count0512 == secuencia0512){dropBurst0512 = dropBurst0512; pb0512 = (dropBurst0512/(arriveBurst0512 + dropBurst0512))*100; WATCH(pb0512);}
                  else {dropBurst0512 = dropBurst0512 + (secuencia0512 - count0512); WATCH(dropBurst0512); count0512 = secuencia0512; pb0512 = (dropBurst0512/(arriveBurst0512 + dropBurst0512))*100; WATCH(pb0512);} }
             else if   (destAddress == 12 && sourceAddress == 6)  {secuencia0612 = recvBurst->getSecuencia(); count0612++; arriveBurst0612++; WATCH(arriveBurst0612);
                  if   (count0612 == secuencia0612){dropBurst0612 = dropBurst0612; pb0612 = (dropBurst0612/(arriveBurst0612 + dropBurst0612))*100; WATCH(pb0612);}
                  else {dropBurst0612 = dropBurst0612 + (secuencia0612 - count0612); WATCH(dropBurst0612); count0612 = secuencia0612; pb0612 = (dropBurst0612/(arriveBurst0612 + dropBurst0612))*100; WATCH(pb0612);} }
             else if   (destAddress == 12 && sourceAddress == 7)  {secuencia0712 = recvBurst->getSecuencia(); count0712++; arriveBurst0712++; WATCH(arriveBurst0712);
                  if   (count0712 == secuencia0712){dropBurst0712 = dropBurst0712; pb0712 = (dropBurst0712/(arriveBurst0712 + dropBurst0712))*100; WATCH(pb0712);}
                  else {dropBurst0712 = dropBurst0712 + (secuencia0712 - count0712); WATCH(dropBurst0712); count0712 = secuencia0712; pb0712 = (dropBurst0712/(arriveBurst0712 + dropBurst0712))*100; WATCH(pb0712);} }
             else if   (destAddress == 12 && sourceAddress == 8)  {secuencia0812 = recvBurst->getSecuencia(); count0812++; arriveBurst0812++; WATCH(arriveBurst0812);
                  if   (count0812 == secuencia0812){dropBurst0812 = dropBurst0812; pb0812 = (dropBurst0812/(arriveBurst0812 + dropBurst0812))*100; WATCH(pb0812);}
                  else {dropBurst0812 = dropBurst0812 + (secuencia0812 - count0812); WATCH(dropBurst0812); count0812 = secuencia0812; pb0812 = (dropBurst0812/(arriveBurst0812 + dropBurst0812))*100; WATCH(pb0812);} }
             else if   (destAddress == 12 && sourceAddress == 9)  {secuencia0912 = recvBurst->getSecuencia(); count0912++; arriveBurst0912++; WATCH(arriveBurst0912);
                  if   (count0912 == secuencia0912){dropBurst0912 = dropBurst0912; pb0912 = (dropBurst0912/(arriveBurst0912 + dropBurst0912))*100; WATCH(pb0912);}
                  else {dropBurst0912 = dropBurst0912 + (secuencia0912 - count0912); WATCH(dropBurst0912); count0912 = secuencia0912; pb0912 = (dropBurst0912/(arriveBurst0912 + dropBurst0912))*100; WATCH(pb0912);} }
             else if   (destAddress == 12 && sourceAddress == 10) {secuencia1012 = recvBurst->getSecuencia(); count1012++; arriveBurst1012++; WATCH(arriveBurst1012);
                  if   (count1012 == secuencia1012){dropBurst1012 = dropBurst1012; pb1012 = (dropBurst1012/(arriveBurst1012 + dropBurst1012))*100; WATCH(pb1012);}
                  else {dropBurst1012 = dropBurst1012 + (secuencia1012 - count1012); WATCH(dropBurst1012); count1012 = secuencia1012; pb1012 = (dropBurst1012/(arriveBurst1012 + dropBurst1012))*100; WATCH(pb1012);} }
             else if   (destAddress == 12 && sourceAddress == 11) {secuencia1112 = recvBurst->getSecuencia(); count1112++; arriveBurst1112++; WATCH(arriveBurst1112);
                  if   (count1112 == secuencia1112){dropBurst1112 = dropBurst1112; pb1112 = (dropBurst1112/(arriveBurst1112 + dropBurst1112))*100; WATCH(pb1112);}
                  else {dropBurst1112 = dropBurst1112 + (secuencia1112 - count1112); WATCH(dropBurst1112); count1112 = secuencia1112; pb1112 = (dropBurst1112/(arriveBurst1112 + dropBurst1112))*100; WATCH(pb1112);} }
             else if   (destAddress == 12 && sourceAddress == 13) {secuencia1312 = recvBurst->getSecuencia(); count1312++; arriveBurst1312++; WATCH(arriveBurst1312);
                  if   (count1312 == secuencia1312){dropBurst1312 = dropBurst1312; pb1312 = (dropBurst1312/(arriveBurst1312 + dropBurst1312))*100; WATCH(pb1312);}
                  else {dropBurst1312 = dropBurst1312 + (secuencia1312 - count1312); WATCH(dropBurst1312); count1312 = secuencia1312; pb1312 = (dropBurst1312/(arriveBurst1312 + dropBurst1312))*100; WATCH(pb1312);} }
             else if   (destAddress == 12 && sourceAddress == 14) {secuencia1412 = recvBurst->getSecuencia(); count1412++; arriveBurst1412++; WATCH(arriveBurst1412);
                  if   (count1412 == secuencia1412){dropBurst1412 = dropBurst1412; pb1412 = (dropBurst1412/(arriveBurst1412 + dropBurst1412))*100; WATCH(pb1412);}
                  else {dropBurst1412 = dropBurst1412 + (secuencia1412 - count1412); WATCH(dropBurst1412); count1412 = secuencia1412; pb1412 = (dropBurst1412/(arriveBurst1412 + dropBurst1412))*100; WATCH(pb1412);} }


             //   if   (destAddress == 13 && sourceAddress == 13) {secuencia1313 = recvBurst->getSecuencia(); count1313++; arriveBurst1313++; WATCH(arriveBurst1313);
             //   if   (count1313 == secuencia1313) {dropBurst1313 = dropBurst1313; pb1313 = (dropBurst1313/(arriveBurst1313 + dropBurst1313))*100; WATCH(pb1313);}
             //   else {dropBurst1313 = dropBurst1313 + (secuencia1313 - count1313); WATCH(dropBurst1313); count1313 = secuencia1313; pb1313 = (dropBurst1313/(arriveBurst1313 + dropBurst1313))*100; WATCH(pb1313);} }
             if        (destAddress == 13 && sourceAddress == 1)  {secuencia0113 = recvBurst->getSecuencia(); count0113++; arriveBurst0113++; WATCH(arriveBurst0113);
                  if   (count0113 == secuencia0113) {dropBurst0113 = dropBurst0113; pb0113 = (dropBurst0113/(arriveBurst0113 + dropBurst0113))*100; WATCH(pb0113);}
                  else {dropBurst0113 = dropBurst0113 + (secuencia0113 - count0113); WATCH(dropBurst0113); count0113 = secuencia0113; pb0113 = (dropBurst0113/(arriveBurst0113 + dropBurst0113))*100; WATCH(pb0113);} }
             else if   (destAddress == 13 && sourceAddress == 2)  {secuencia0213 = recvBurst->getSecuencia(); count0213++; arriveBurst0213++; WATCH(arriveBurst0213);
                  if   (count0213 == secuencia0213) {dropBurst0213 = dropBurst0213; pb0213 = (dropBurst0213/(arriveBurst0213 + dropBurst0213))*100; WATCH(pb0213);}
                  else {dropBurst0213 = dropBurst0213 + (secuencia0213 - count0213); WATCH(dropBurst0213); count0213 = secuencia0213; pb0213 = (dropBurst0213/(arriveBurst0213 + dropBurst0213))*100; WATCH(pb0213);} }
             else if   (destAddress == 13 && sourceAddress == 3)  {secuencia0313 = recvBurst->getSecuencia(); count0313++; arriveBurst0313++; WATCH(arriveBurst0313);
                  if   (count0313 == secuencia0313) {dropBurst0313 = dropBurst0313; pb0313 = (dropBurst0313/(arriveBurst0313 + dropBurst0313))*100; WATCH(pb0313);}
                  else {dropBurst0313 = dropBurst0313 + (secuencia0313 - count0313); WATCH(dropBurst0313); count0313 = secuencia0313; pb0313 = (dropBurst0313/(arriveBurst0313 + dropBurst0313))*100; WATCH(pb0313);} }
             else if   (destAddress == 13 && sourceAddress == 4)  {secuencia0413 = recvBurst->getSecuencia(); count0413++; arriveBurst0413++; WATCH(arriveBurst0413);
                  if   (count0413 == secuencia0413) {dropBurst0413 = dropBurst0413; pb0413 = (dropBurst0413/(arriveBurst0413 + dropBurst0413))*100; WATCH(pb0413);}
                  else {dropBurst0413 = dropBurst0413 + (secuencia0413 - count0413); WATCH(dropBurst0413); count0413 = secuencia0413; pb0413 = (dropBurst0413/(arriveBurst0413 + dropBurst0413))*100; WATCH(pb0413);} }
             else if   (destAddress == 13 && sourceAddress == 5)  {secuencia0513 = recvBurst->getSecuencia(); count0513++; arriveBurst0513++; WATCH(arriveBurst0513);
                  if   (count0513 == secuencia0513) {dropBurst0513 = dropBurst0513; pb0513 = (dropBurst0513/(arriveBurst0513 + dropBurst0513))*100; WATCH(pb0513);}
                  else {dropBurst0513 = dropBurst0513 + (secuencia0513 - count0513); WATCH(dropBurst0513); count0513 = secuencia0513; pb0513 = (dropBurst0513/(arriveBurst0513 + dropBurst0513))*100; WATCH(pb0513);} }
             else if   (destAddress == 13 && sourceAddress == 6)  {secuencia0613 = recvBurst->getSecuencia(); count0613++; arriveBurst0613++; WATCH(arriveBurst0613);
                  if   (count0613 == secuencia0613) {dropBurst0613 = dropBurst0613; pb0613 = (dropBurst0613/(arriveBurst0613 + dropBurst0613))*100; WATCH(pb0613);}
                  else {dropBurst0613 = dropBurst0613 + (secuencia0613 - count0613); WATCH(dropBurst0613); count0613 = secuencia0613; pb0613 = (dropBurst0613/(arriveBurst0613 + dropBurst0613))*100; WATCH(pb0613);} }
             else if   (destAddress == 13 && sourceAddress == 7)  {secuencia0713 = recvBurst->getSecuencia(); count0713++; arriveBurst0713++; WATCH(arriveBurst0713);
                  if   (count0713 == secuencia0713) {dropBurst0713 = dropBurst0713; pb0713 = (dropBurst0713/(arriveBurst0713 + dropBurst0713))*100; WATCH(pb0713);}
                  else {dropBurst0713 = dropBurst0713 + (secuencia0713 - count0713); WATCH(dropBurst0713); count0713 = secuencia0713; pb0713 = (dropBurst0713/(arriveBurst0713 + dropBurst0713))*100; WATCH(pb0713);} }
             else if   (destAddress == 13 && sourceAddress == 8)  {secuencia0813 = recvBurst->getSecuencia(); count0813++; arriveBurst0813++; WATCH(arriveBurst0813);
                  if   (count0813 == secuencia0813) {dropBurst0813 = dropBurst0813; pb0813 = (dropBurst0813/(arriveBurst0813 + dropBurst0813))*100; WATCH(pb0813);}
                  else {dropBurst0813 = dropBurst0813 + (secuencia0813 - count0813); WATCH(dropBurst0813); count0813 = secuencia0813; pb0813 = (dropBurst0813/(arriveBurst0813 + dropBurst0813))*100; WATCH(pb0813);} }
             else if   (destAddress == 13 && sourceAddress == 9)  {secuencia0913 = recvBurst->getSecuencia(); count0913++; arriveBurst0913++; WATCH(arriveBurst0913);
                  if   (count0913 == secuencia0913) {dropBurst0913 = dropBurst0913; pb0913 = (dropBurst0913/(arriveBurst0913 + dropBurst0913))*100; WATCH(pb0913);}
                  else {dropBurst0913 = dropBurst0913 + (secuencia0913 - count0913); WATCH(dropBurst0913); count0913 = secuencia0913; pb0913 = (dropBurst0913/(arriveBurst0913 + dropBurst0913))*100; WATCH(pb0913);} }
             else if   (destAddress == 13 && sourceAddress == 10) {secuencia1013 = recvBurst->getSecuencia(); count1013++; arriveBurst1013++; WATCH(arriveBurst1013);
                  if   (count1013 == secuencia1013) {dropBurst1013 = dropBurst1013; pb1013 = (dropBurst1013/(arriveBurst1013 + dropBurst1013))*100; WATCH(pb1013);}
                  else {dropBurst1013 = dropBurst1013 + (secuencia1013 - count1013); WATCH(dropBurst1013); count1013 = secuencia1013; pb1013 = (dropBurst1013/(arriveBurst1013 + dropBurst1013))*100; WATCH(pb1013);} }
             else if   (destAddress == 13 && sourceAddress == 11) {secuencia1113 = recvBurst->getSecuencia(); count1113++; arriveBurst1113++; WATCH(arriveBurst1113);
                  if   (count1113 == secuencia1113) {dropBurst1113 = dropBurst1113; pb1113 = (dropBurst1113/(arriveBurst1113 + dropBurst1113))*100; WATCH(pb1113);}
                  else {dropBurst1113 = dropBurst1113 + (secuencia1113 - count1113); WATCH(dropBurst1113); count1113 = secuencia1113; pb1113 = (dropBurst1113/(arriveBurst1113 + dropBurst1113))*100; WATCH(pb1113);} }
             else if   (destAddress == 13 && sourceAddress == 12) {secuencia1213 = recvBurst->getSecuencia(); count1213++; arriveBurst1213++; WATCH(arriveBurst1213);
                  if   (count1213 == secuencia1213) {dropBurst1213 = dropBurst1213; pb1213 = (dropBurst1213/(arriveBurst1213 + dropBurst1213))*100; WATCH(pb1213);}
                  else {dropBurst1213 = dropBurst1213 + (secuencia1213 - count1213); WATCH(dropBurst1213); count1213 = secuencia1213; pb1213 = (dropBurst1213/(arriveBurst1213 + dropBurst1213))*100; WATCH(pb1213);} }
             else if   (destAddress == 13 && sourceAddress == 14) {secuencia1413 = recvBurst->getSecuencia(); count1413++; arriveBurst1413++; WATCH(arriveBurst1413);
                  if   (count1413 == secuencia1413) {dropBurst1413 = dropBurst1413; pb1413 = (dropBurst1413/(arriveBurst1413 + dropBurst1413))*100; WATCH(pb1413);}
                  else {dropBurst1413 = dropBurst1413 + (secuencia1413 - count1413); WATCH(dropBurst1413); count1413 = secuencia1413; pb1413 = (dropBurst1413/(arriveBurst1413 + dropBurst1413))*100; WATCH(pb1413);} }


             //   if   (destAddress == 14  && sourceAddress == 14){secuencia1414 = recvBurst->getSecuencia(); count1414++; arriveBurst1414++; WATCH(arriveBurst1414);
             //   if   (count1414 == secuencia1414) {dropBurst1414 = dropBurst1414; pb1414 = (dropBurst1414/(arriveBurst1414 + dropBurst1414))*100; WATCH(pb1414);}
             //   else {dropBurst1414 = dropBurst1414 + (secuencia1414 - count1414); WATCH(dropBurst1414); count1414 = secuencia1414; pb1414 = (dropBurst1414/(arriveBurst1414 + dropBurst1414))*100; WATCH(pb1414);} }
             if        (destAddress == 14 && sourceAddress == 1)  {secuencia0114 = recvBurst->getSecuencia(); count0114++; arriveBurst0114++; WATCH(arriveBurst0114);
                  if   (count0114 == secuencia0114) {dropBurst0114 = dropBurst0114; pb0114 = (dropBurst0114/(arriveBurst0114 + dropBurst0114))*100; WATCH(pb0114);}
                  else {dropBurst0114 = dropBurst0114 + (secuencia0114 - count0114); WATCH(dropBurst0114); count0114 = secuencia0114; pb0114 = (dropBurst0114/(arriveBurst0114 + dropBurst0114))*100; WATCH(pb0114);} }
             else if   (destAddress == 14 && sourceAddress == 2)  {secuencia0214 = recvBurst->getSecuencia(); count0214++; arriveBurst0214++; WATCH(arriveBurst0214);
                  if   (count0214 == secuencia0214) {dropBurst0214 = dropBurst0214; pb0214 = (dropBurst0214/(arriveBurst0214 + dropBurst0214))*100; WATCH(pb0214);}
                  else {dropBurst0214 = dropBurst0214 + (secuencia0214 - count0214); WATCH(dropBurst0214); count0214 = secuencia0214; pb0214 = (dropBurst0214/(arriveBurst0214 + dropBurst0214))*100; WATCH(pb0214);} }
             else if   (destAddress == 14 && sourceAddress == 3)  {secuencia0314 = recvBurst->getSecuencia(); count0314++; arriveBurst0314++; WATCH(arriveBurst0314);
                  if   (count0314 == secuencia0314) {dropBurst0314 = dropBurst0314; pb0314 = (dropBurst0314/(arriveBurst0314 + dropBurst0314))*100; WATCH(pb0314);}
                  else {dropBurst0314 = dropBurst0314 + (secuencia0314 - count0314); WATCH(dropBurst0314); count0314 = secuencia0314; pb0314 = (dropBurst0314/(arriveBurst0314 + dropBurst0314))*100; WATCH(pb0314);} }
             else if   (destAddress == 14 && sourceAddress == 4)  {secuencia0414 = recvBurst->getSecuencia(); count0414++; arriveBurst0414++; WATCH(arriveBurst0414);
                  if   (count0414 == secuencia0414) {dropBurst0414 = dropBurst0414; pb0414 = (dropBurst0414/(arriveBurst0414 + dropBurst0414))*100; WATCH(pb0414);}
                  else {dropBurst0414 = dropBurst0414 + (secuencia0414 - count0414); WATCH(dropBurst0414); count0414 = secuencia0414; pb0414 = (dropBurst0414/(arriveBurst0414 + dropBurst0414))*100; WATCH(pb0414);} }
             else if   (destAddress == 14 && sourceAddress == 5)  {secuencia0514 = recvBurst->getSecuencia(); count0514++; arriveBurst0514++; WATCH(arriveBurst0514);
                  if   (count0514 == secuencia0514) {dropBurst0514 = dropBurst0514; pb0514 = (dropBurst0514/(arriveBurst0514 + dropBurst0514))*100; WATCH(pb0514);}
                  else {dropBurst0514 = dropBurst0514 + (secuencia0514 - count0514); WATCH(dropBurst0514); count0514 = secuencia0514; pb0514 = (dropBurst0514/(arriveBurst0514 + dropBurst0514))*100; WATCH(pb0514);} }
             else if   (destAddress == 14 && sourceAddress == 6)  {secuencia0614 = recvBurst->getSecuencia(); count0614++; arriveBurst0614++; WATCH(arriveBurst0614);
                  if   (count0614 == secuencia0614) {dropBurst0614 = dropBurst0614; pb0614 = (dropBurst0614/(arriveBurst0614 + dropBurst0614))*100; WATCH(pb0614);}
                  else {dropBurst0614 = dropBurst0614 + (secuencia0614 - count0614); WATCH(dropBurst0614); count0614 = secuencia0614; pb0614 = (dropBurst0614/(arriveBurst0614 + dropBurst0614))*100; WATCH(pb0614);} }
             else if   (destAddress == 14 && sourceAddress == 7)  {secuencia0714 = recvBurst->getSecuencia(); count0714++; arriveBurst0714++; WATCH(arriveBurst0714);
                  if   (count0714 == secuencia0714) {dropBurst0714 = dropBurst0714; pb0714 = (dropBurst0714/(arriveBurst0714 + dropBurst0714))*100; WATCH(pb0714);}
                  else {dropBurst0714 = dropBurst0714 + (secuencia0714 - count0714); WATCH(dropBurst0714); count0714 = secuencia0714; pb0714 = (dropBurst0714/(arriveBurst0714 + dropBurst0714))*100; WATCH(pb0714);} }
             else if   (destAddress == 14 && sourceAddress == 8)  {secuencia0814 = recvBurst->getSecuencia(); count0814++; arriveBurst0814++; WATCH(arriveBurst0814);
                  if   (count0814 == secuencia0814) {dropBurst0814 = dropBurst0814; pb0814 = (dropBurst0814/(arriveBurst0814 + dropBurst0814))*100; WATCH(pb0814);}
                  else {dropBurst0814 = dropBurst0814 + (secuencia0814 - count0814); WATCH(dropBurst0814); count0814 = secuencia0814; pb0814 = (dropBurst0814/(arriveBurst0814 + dropBurst0814))*100; WATCH(pb0814);} }
             else if   (destAddress == 14 && sourceAddress == 9)  {secuencia0914 = recvBurst->getSecuencia(); count0914++; arriveBurst0914++; WATCH(arriveBurst0914);
                  if   (count0914 == secuencia0914) {dropBurst0914 = dropBurst0914; pb0914 = (dropBurst0914/(arriveBurst0914 + dropBurst0914))*100; WATCH(pb0914);}
                  else {dropBurst0914 = dropBurst0914 + (secuencia0914 - count0914); WATCH(dropBurst0914); count0914 = secuencia0914; pb0914 = (dropBurst0914/(arriveBurst0914 + dropBurst0914))*100; WATCH(pb0914);} }
             else if   (destAddress == 14 && sourceAddress == 10) {secuencia1014 = recvBurst->getSecuencia(); count1014++; arriveBurst1014++; WATCH(arriveBurst1014);
                  if   (count1014 == secuencia1014) {dropBurst1014 = dropBurst1014; pb1014 = (dropBurst1014/(arriveBurst1014 + dropBurst1014))*100; WATCH(pb1014);}
                  else {dropBurst1014 = dropBurst1014 + (secuencia1014 - count1014); WATCH(dropBurst1014); count1014 = secuencia1014; pb1014 = (dropBurst1014/(arriveBurst1014 + dropBurst1014))*100; WATCH(pb1014);} }
             else if   (destAddress == 14 && sourceAddress == 11) {secuencia1114 = recvBurst->getSecuencia(); count1114++; arriveBurst1114++; WATCH(arriveBurst1114);
                  if   (count1114 == secuencia1114) {dropBurst1114 = dropBurst1114; pb1114 = (dropBurst1114/(arriveBurst1114 + dropBurst1114))*100; WATCH(pb1114);}
                  else {dropBurst1114 = dropBurst1114 + (secuencia1114 - count1114); WATCH(dropBurst1114); count1114 = secuencia1114; pb1114 = (dropBurst1114/(arriveBurst1114 + dropBurst1114))*100; WATCH(pb1114);} }
             else if   (destAddress == 14 && sourceAddress == 12) {secuencia1214 = recvBurst->getSecuencia(); count1214++; arriveBurst1214++; WATCH(arriveBurst1214);
                  if   (count1214 == secuencia1214) {dropBurst1214 = dropBurst1214; pb1214 = (dropBurst1214/(arriveBurst1214 + dropBurst1214))*100; WATCH(pb1214);}
                  else {dropBurst1214 = dropBurst1214 + (secuencia1214 - count1214); WATCH(dropBurst1214); count1214 = secuencia1214; pb1214 = (dropBurst1214/(arriveBurst1214 + dropBurst1214))*100; WATCH(pb1214);} }
             else if   (destAddress == 14 && sourceAddress == 13) {secuencia1314 = recvBurst->getSecuencia(); count1314++; arriveBurst1314++; WATCH(arriveBurst1314);
                  if   (count1314 == secuencia1314) {dropBurst1314 = dropBurst1314; pb1314 = (dropBurst1314/(arriveBurst1314 + dropBurst1314))*100; WATCH(pb1314);}
                  else {dropBurst1314 = dropBurst1314 + (secuencia1314 - count1314); WATCH(dropBurst1314); count1314 = secuencia1314; pb1314 = (dropBurst1314/(arriveBurst1314 + dropBurst1314))*100; WATCH(pb1314);} }


          //############################################################################################################################################################
          //############################################################################################################################################################

  }


   else if(msg->getKind() == 2){ //Final de la ráfaga. Se busca el inicio del mensaje y se desemnsambla.
      Burst *recvBurst = check_and_cast < Burst*> (msg);
      int bId,nSeq; // valores de ID de la ráfaga

      bId = recvBurst->getIdBurstifier();
      nSeq = recvBurst->getSecNum();

      list<Burst*>::iterator i;
      Burst* actElem;
      //Busca desde el comienzo porque la ráfaga que se está buscando es probablemente una de la últimas
      for(i = receivedBursts.begin(); i != receivedBursts.end(); i++){
         actElem = *i;
         if((actElem->getIdBurstifier() == bId) && (actElem->getSecNum() == nSeq)) break; //Se encuentra la rafaga
      }


      if(i != receivedBursts.end()){ //Si el iterador superior no llega hasta el final...significa que la ráfaga fue encontrada.
         Burst *burstIni= check_and_cast< Burst* > (*i);

         cMessage *tempPack;
         while(burstIni->hasMessages()){ //Libera los paquetes hasta que la cola de burstIni esté vacia
            tempPack = burstIni->retrieveMessage();
            //TODO: Envía el paquete a un buffer intermedio por lo tanto, todos los paquetes no serían liberados a la red eléctrica al mismo tiempo.
            send(tempPack,"out");
         }
         //Limpieza
         delete msg;
         delete burstIni;
         i = receivedBursts.erase(i);

         listSize--;
         VlistSize.record(listSize);
      }


      else{
         printf("<OBS_BurstDissasembler><t=%s> Error, la rafaga id=(%d,%d) no encontrada\n",simTime().str().c_str(),bId,nSeq);
         delete msg;
      }
   }
}

void EdgeNodeDisassembler::updateDisplay()
{
    char buf[40];
    sprintf(buf, "Rafagas recibidas: %ld ", recvBursts);
    getDisplayString().setTagArg("t",0,buf);
}


void EdgeNodeDisassembler::finish()
{
    recordScalar("Simulation duration", simTime());
    eedStats.record();
    recordScalar("numero de Rafagas Recibidas",recvBursts);


    miDireccion = destAddress;//getParentModule()->getParentModule()->getSubmodule("edgeHost")->getSubmodule("Host")->getSubmodule("source")->par("address");


    if      (miDireccion == 1) {
            eed1 = (eed0201/arriveBurst0201 + eed0301/arriveBurst0301 + eed0401/arriveBurst0401 + eed0501/arriveBurst0501 + eed0601/arriveBurst0601 + eed0701/arriveBurst0701 + eed0801/arriveBurst0801 + eed0901/arriveBurst0901 + eed1001/arriveBurst1001 + eed1101/arriveBurst1101 + eed1201/arriveBurst1201 + eed1301/arriveBurst1301 + eed1401/arriveBurst1401)/13;
            pb1 = (pb0201 + pb0301 + pb0401 + pb0501 + pb0601 + pb0701 + pb0801 + pb0901 + pb1001 + pb1101 + pb1201 + pb1301 + pb1401)/(100*13); WATCH(pb1);
            //dropBurst1 = dropBurst0201 + dropBurst0301 + dropBurst0401 + dropBurst0501 + dropBurst0601 + dropBurst0701 + dropBurst0801 + dropBurst0901 + dropBurst1001 + dropBurst1101 + dropBurst1201 + dropBurst1301 + dropBurst1401;
            //arriveBurst1 = (arriveBurst0201 + arriveBurst0301 + arriveBurst0401 + arriveBurst0501 + arriveBurst0601 + arriveBurst0701 + arriveBurst0801 + arriveBurst0901 + arriveBurst1001 + arriveBurst1101 + arriveBurst1201 + arriveBurst1301 + arriveBurst1401);
            //BurstTotal1 = dropBurst1 + arriveBurst1;
            //BurstTotal1 = (BurstTotal0201 + BurstTotal0301 + BurstTotal0401 + BurstTotal0501 + BurstTotal0601 + BurstTotal0701 + BurstTotal0801 + BurstTotal0901 + BurstTotal1001 + BurstTotal1101 + BurstTotal1201 + BurstTotal1301 + BurstTotal1401);
            //BurstGeneratedXX01 = secuencia0201 + secuencia0301 + secuencia0401 + secuencia0501 + secuencia0601 + secuencia0701 + secuencia0801 + secuencia0901 + secuencia1001 + secuencia1101 + secuencia1201 + secuencia1301 + secuencia1401;
            BurstReceivedXX01 = arriveBurst0201 + arriveBurst0301 + arriveBurst0401 + arriveBurst0501 + arriveBurst0601 + arriveBurst0701 + arriveBurst0801 + arriveBurst0901 + arriveBurst1001 + arriveBurst1101 + arriveBurst1201 + arriveBurst1301 + arriveBurst1401;
            BurstDropXX01 = dropBurst0201 + dropBurst0301 + dropBurst0401 + dropBurst0501 + dropBurst0601 + dropBurst0701 + dropBurst0801 + dropBurst0901 + dropBurst1001 + dropBurst1101 + dropBurst1201 + dropBurst1301 + dropBurst1401;
            BurstGeneratedXX01 = BurstReceivedXX01 + BurstDropXX01;
            PBXX01 = (BurstDropXX01)/(BurstGeneratedXX01);

            recordScalar("End to End Delay promedio nodo 1",eed1); recordScalar("Probabilidad de bloqueo nodo 1",PBXX01);
            recordScalar("Porcentaje de rafagas perdidas nodo 1",PBXX01*100);
            recordScalar("Rafagas Generadas Nodo XX01",BurstGeneratedXX01); recordScalar("Rafagas Recibidas Nodo XX01",BurstReceivedXX01); recordScalar("Rafagas Perdidas Nodo XX01",BurstDropXX01);
            //recordScalar("Rafagas perdidas nodo 1",dropBurst1);
            //recordScalar("Rafagas Generadas Nodo 1",BurstGeneratedXX01);  recordScalar("Rafagas Recibidas Nodo 01",BurstReceivedXX01); recordScalar("Rafagas Perdidas Nodo 01",BurstDropXX01);
            }
    else if (miDireccion == 2) {
            eed2 = (eed0102/arriveBurst0102 + eed0302/arriveBurst0302 + eed0402/arriveBurst0402 + eed0502/arriveBurst0502 + eed0602/arriveBurst0602 + eed0702/arriveBurst0702 + eed0802/arriveBurst0802 + eed0902/arriveBurst0902 + eed1002/arriveBurst1002 + eed1102/arriveBurst1102 + eed1202/arriveBurst1202 + eed1302/arriveBurst1302 + eed1402/arriveBurst1402)/13;
            pb2 = (pb0102 + pb0302 + pb0402 + pb0502 + pb0602 + pb0702 + pb0802 + pb0902 + pb1002 + pb1102 + pb1202 + pb1302 + pb1402)/(100*13); WATCH(pb2);
            //dropBurst2 = dropBurst0102 + dropBurst0302 + dropBurst0402 + dropBurst0502 + dropBurst0602 + dropBurst0702 + dropBurst0802 + dropBurst0902 + dropBurst1002 + dropBurst1102 + dropBurst1202 + dropBurst1302 + dropBurst1402;
            //arriveBurst2 = (arriveBurst0102 + arriveBurst0302 + arriveBurst0402 + arriveBurst0502 + arriveBurst0602 + arriveBurst0702 + arriveBurst0802 + arriveBurst0902 + arriveBurst1002 + arriveBurst1102 + arriveBurst1202 + arriveBurst1302 + arriveBurst1402);
            //BurstTotal2 = dropBurst2 + arriveBurst2;
            //BurstTotal2 = (BurstTotal0102 + BurstTotal0302 + BurstTotal0402 + BurstTotal0502 + BurstTotal0602 + BurstTotal0702 + BurstTotal0802 + BurstTotal0902 + BurstTotal1002 + BurstTotal1102 + BurstTotal1202 + BurstTotal1302 + BurstTotal1402);
            //BurstGeneratedXX02 = secuencia0102 + secuencia0302 + secuencia0402 + secuencia0502 + secuencia0602 + secuencia0702 + secuencia0802 + secuencia0902 + secuencia1002 + secuencia1102 + secuencia1202 + secuencia1302 + secuencia1402;
            BurstReceivedXX02 = arriveBurst0102 + arriveBurst0302 + arriveBurst0402 + arriveBurst0502 + arriveBurst0602 + arriveBurst0702 + arriveBurst0802 + arriveBurst0902 + arriveBurst1002 + arriveBurst1102 + arriveBurst1202 + arriveBurst1302 + arriveBurst1402;
            BurstDropXX02 = dropBurst0102 + dropBurst0302 + dropBurst0402 + dropBurst0502 + dropBurst0602 + dropBurst0702 + dropBurst0802 + dropBurst0902 + dropBurst1002 + dropBurst1102 + dropBurst1202 + dropBurst1302 + dropBurst1402;
            BurstGeneratedXX02 = BurstReceivedXX02 + BurstDropXX02;
            PBXX02 = (BurstDropXX02)/(BurstGeneratedXX02);

            recordScalar("End to End Delay promedio nodo 2",eed2); recordScalar("Probabilidad de bloqueo nodo 2",PBXX02);
            recordScalar("Porcentaje de rafagas perdidas nodo 2",PBXX02*100);
            recordScalar("Rafagas Generadas Nodo XX02",BurstGeneratedXX02); recordScalar("Rafagas Recibidas Nodo XX02",BurstReceivedXX02); recordScalar("Rafagas Perdidas Nodo XX02",BurstDropXX02);
            //recordScalar("Rafagas perdidas nodo 2",dropBurst2);
            //recordScalar("Rafagas Generadas Nodo 2",BurstGeneratedXX02);  recordScalar("Rafagas Recibidas Nodo 02",BurstReceivedXX02); recordScalar("Rafagas Perdidas Nodo 02",BurstDropXX02);
            }
    else if (miDireccion == 3) {
            eed3 = (eed0103/arriveBurst0103 + eed0203/arriveBurst0203 + eed0403/arriveBurst0403 + eed0503/arriveBurst0503 + eed0603/arriveBurst0603 + eed0703/arriveBurst0703 + eed0803/arriveBurst0803 + eed0903/arriveBurst0903 + eed1003/arriveBurst1003 + eed1103/arriveBurst1103 + eed1203/arriveBurst1203 + eed1303/arriveBurst1303 + eed1403/arriveBurst1403)/13;
            pb3 = (pb0103 + pb0203 + pb0403 + pb0503 + pb0603 + pb0703 + pb0803 + pb0903 + pb1003 + pb1103 + pb1203 + pb1303 + pb1403)/(100*13); WATCH(pb3);
            //dropBurst3 = dropBurst0103 + dropBurst0203 + dropBurst0403 + dropBurst0503 + dropBurst0603 + dropBurst0703 + dropBurst0803 + dropBurst0903 + dropBurst1003 + dropBurst1103 + dropBurst1203 + dropBurst1303 + dropBurst1403;
            //arriveBurst3 = (arriveBurst0103 + arriveBurst0203 + arriveBurst0403 + arriveBurst0503 + arriveBurst0603 + arriveBurst0703 + arriveBurst0803 + arriveBurst0903 + arriveBurst1003 + arriveBurst1103 + arriveBurst1203 + arriveBurst1303 + arriveBurst1403);
            //BurstTotal3 = dropBurst3 + arriveBurst3;
            //BurstTotal3 = (BurstTotal0103 + BurstTotal0203 + BurstTotal0403 + BurstTotal0503 + BurstTotal0603 + BurstTotal0703 + BurstTotal0803 + BurstTotal0903 + BurstTotal1003 + BurstTotal1103 + BurstTotal1203 + BurstTotal1303 + BurstTotal1403);
            //BurstGeneratedXX03 = secuencia0103 + secuencia0203 + secuencia0403 + secuencia0503 + secuencia0603 + secuencia0703 + secuencia0803 + secuencia0903 + secuencia1003 + secuencia1103 + secuencia1203 + secuencia1303 + secuencia1403;
            BurstReceivedXX03 = arriveBurst0103 + arriveBurst0203 + arriveBurst0403 + arriveBurst0503 + arriveBurst0603 + arriveBurst0703 + arriveBurst0803 + arriveBurst0903 + arriveBurst1003 + arriveBurst1103 + arriveBurst1203 + arriveBurst1303 + arriveBurst1403;
            BurstDropXX03 = dropBurst0103 + dropBurst0203 + dropBurst0403 + dropBurst0503 + dropBurst0603 + dropBurst0703 + dropBurst0803 + dropBurst0903 + dropBurst1003 + dropBurst1103 + dropBurst1203 + dropBurst1303 + dropBurst1403;
            BurstGeneratedXX03 = BurstReceivedXX03 + BurstDropXX03;
            PBXX03 = (BurstDropXX03)/(BurstGeneratedXX03);

            recordScalar("End to End Delay promedio nodo 3",eed3); recordScalar("Probabilidad de bloqueo nodo 3",PBXX03);
            recordScalar("Porcentaje de rafagas perdidas nodo 3",PBXX03*100);                                                               //recordScalar("Rafagas perdidas nodo 3",dropBurst3);
            recordScalar("Rafagas Generadas Nodo XX03",BurstGeneratedXX03); recordScalar("Rafagas Recibidas Nodo XX03",BurstReceivedXX03); recordScalar("Rafagas Perdidas Nodo XX03",BurstDropXX03);

            //recordScalar("Rafagas Generadas Nodo 3",BurstGeneratedXX03);  recordScalar("Rafagas Recibidas Nodo 03",BurstReceivedXX03); recordScalar("Rafagas Perdidas Nodo 03",BurstDropXX03);
            }
    else if (miDireccion == 4) {
            eed4 = (eed0104/arriveBurst0104 + eed0204/arriveBurst0204 + eed0304/arriveBurst0304 + eed0504/arriveBurst0504 + eed0604/arriveBurst0604 + eed0704/arriveBurst0704 + eed0804/arriveBurst0804 + eed0904/arriveBurst0904 + eed1004/arriveBurst1004 + eed1104/arriveBurst1104 + eed1204/arriveBurst1204 + eed1304/arriveBurst1304 + eed1404/arriveBurst1404)/13;
            pb4 = (pb0104 + pb0204 + pb0304 + pb0504 + pb0604 + pb0704 + pb0804 + pb0904 + pb1004 + pb1104 + pb1204 + pb1304 + pb1404)/(100*13); WATCH(pb4);
            //dropBurst4 = dropBurst0104 + dropBurst0204 + dropBurst0304 + dropBurst0504 + dropBurst0604 + dropBurst0704 + dropBurst0804 + dropBurst0904 + dropBurst1004 + dropBurst1104 + dropBurst1204 + dropBurst1304 + dropBurst1404;
            //arriveBurst4 = (arriveBurst0104 + arriveBurst0204 + arriveBurst0304 + arriveBurst0504 + arriveBurst0604 + arriveBurst0704 + arriveBurst0804 + arriveBurst0904 + arriveBurst1004 + arriveBurst1104 + arriveBurst1204 + arriveBurst1304 + arriveBurst1404);
            //BurstTotal4 = dropBurst4 + arriveBurst4;
            //BurstTotal4 = (BurstTotal0104 + BurstTotal0204 + BurstTotal0304 + BurstTotal0504 + BurstTotal0604 + BurstTotal0704 + BurstTotal0804 + BurstTotal0904 + BurstTotal1004 + BurstTotal1104 + BurstTotal1204 + BurstTotal1304 + BurstTotal1404);
            //BurstGeneratedXX04 = secuencia0104 + secuencia0204 + secuencia0304 + secuencia0504 + secuencia0604 + secuencia0704 + secuencia0804 + secuencia0904 + secuencia1004 + secuencia1104 + secuencia1204 + secuencia1304 + secuencia1404;
            BurstReceivedXX04 = arriveBurst0104 + arriveBurst0204 + arriveBurst0304 + arriveBurst0504 + arriveBurst0604 + arriveBurst0704 + arriveBurst0804 + arriveBurst0904 + arriveBurst1004 + arriveBurst1104 + arriveBurst1204 + arriveBurst1304 + arriveBurst1404;
            BurstDropXX04 = dropBurst0104 + dropBurst0204 + dropBurst0304 + dropBurst0504 + dropBurst0604 + dropBurst0704 + dropBurst0804 + dropBurst0904 + dropBurst1004 + dropBurst1104 + dropBurst1204 + dropBurst1304 + dropBurst1404;
            BurstGeneratedXX04 = BurstReceivedXX04 + BurstDropXX04;
            PBXX04 = (BurstDropXX04)/(BurstGeneratedXX04);

            recordScalar("End to End Delay promedio nodo 4",eed4); recordScalar("Probabilidad de bloqueo nodo 4",PBXX04);
            recordScalar("Porcentaje de rafagas perdidas nodo 4",PBXX04*100);                                                               //recordScalar("Rafagas perdidas nodo 4",dropBurst4);
            recordScalar("Rafagas Generadas Nodo XX04",BurstGeneratedXX04); recordScalar("Rafagas Recibidas Nodo XX04",BurstReceivedXX04); recordScalar("Rafagas Perdidas Nodo XX04",BurstDropXX04);

            //recordScalar("Rafagas Generadas Nodo 4",BurstGeneratedXX04);  recordScalar("Rafagas Recibidas Nodo 04",BurstReceivedXX04); recordScalar("Rafagas Perdidas Nodo 04",BurstDropXX04);
            }
    else if (miDireccion == 5) {
            eed5 = (eed0105/arriveBurst0105 + eed0205/arriveBurst0205 + eed0305/arriveBurst0305 + eed0405/arriveBurst0405 + eed0605/arriveBurst0605 + eed0705/arriveBurst0705 + eed0805/arriveBurst0805 + eed0905/arriveBurst0905 + eed1005/arriveBurst1005 + eed1105/arriveBurst1105 + eed1205/arriveBurst1205 + eed1305/arriveBurst1305 + eed1405/arriveBurst1405)/13;
            pb5 = (pb0105 + pb0205 + pb0305 + pb0405 + pb0605 + pb0705 + pb0805 + pb0905 + pb1005 + pb1105 + pb1205 + pb1305 + pb1405)/(100*13); WATCH(pb5);
            //dropBurst5 = dropBurst0105 + dropBurst0205 + dropBurst0305 + dropBurst0405 + dropBurst0605 + dropBurst0705 + dropBurst0805 + dropBurst0905 + dropBurst1005 + dropBurst1105 + dropBurst1205 + dropBurst1305 + dropBurst1405;
            //arriveBurst5 = (arriveBurst0105 + arriveBurst0205 + arriveBurst0305 + arriveBurst0405 + arriveBurst0605 + arriveBurst0705 + arriveBurst0805 + arriveBurst0905 + arriveBurst1005 + arriveBurst1105 + arriveBurst1205 + arriveBurst1305 + arriveBurst1405);
            //BurstTotal5 = dropBurst5 + arriveBurst5;
            //BurstTotal5 = (BurstTotal0105 + BurstTotal0205 + BurstTotal0305 + BurstTotal0405 + BurstTotal0605 + BurstTotal0705 + BurstTotal0805 + BurstTotal0905 + BurstTotal1005 + BurstTotal1105 + BurstTotal1205 + BurstTotal1305 + BurstTotal1405);
            //BurstGeneratedXX05 = secuencia0105 + secuencia0205 + secuencia0305 + secuencia0405 + secuencia0605 + secuencia0705 + secuencia0805 + secuencia0905 + secuencia1005 + secuencia1105 + secuencia1205 + secuencia1305 + secuencia1405;
            BurstReceivedXX05 = arriveBurst0105 + arriveBurst0205 + arriveBurst0305 + arriveBurst0405 + arriveBurst0605 + arriveBurst0705 + arriveBurst0805 + arriveBurst0905 + arriveBurst1005 + arriveBurst1105 + arriveBurst1205 + arriveBurst1305 + arriveBurst1405;
            BurstDropXX05 = dropBurst0105 + dropBurst0205 + dropBurst0305 + dropBurst0405 + dropBurst0605 + dropBurst0705 + dropBurst0805 + dropBurst0905 + dropBurst1005 + dropBurst1105 + dropBurst1205 + dropBurst1305 + dropBurst1405;
            BurstGeneratedXX05 = BurstReceivedXX05 + BurstDropXX05;
            PBXX05 = (BurstDropXX05)/(BurstGeneratedXX05);

            recordScalar("End to End Delay promedio nodo 5",eed5); recordScalar("Probabilidad de bloqueo nodo 5",PBXX05);
            recordScalar("Porcentaje de rafagas perdidas nodo 5",PBXX05*100);                                                               //recordScalar("Rafagas perdidas nodo 5",dropBurst5);
            recordScalar("Rafagas Generadas Nodo XX05",BurstGeneratedXX05); recordScalar("Rafagas Recibidas Nodo XX05",BurstReceivedXX05); recordScalar("Rafagas Perdidas Nodo XX05",BurstDropXX05);

            //recordScalar("Rafagas Generadas Nodo 5",BurstGeneratedXX05);  recordScalar("Rafagas Recibidas Nodo 05",BurstReceivedXX05); recordScalar("Rafagas Perdidas Nodo 05",BurstDropXX05);
            }
    else if (miDireccion == 6) {
            eed6 = (eed0106/arriveBurst0106 + eed0206/arriveBurst0206 + eed0306/arriveBurst0306 + eed0406/arriveBurst0406 + eed0506/arriveBurst0506 + eed0706/arriveBurst0706 + eed0806/arriveBurst0806 + eed0906/arriveBurst0906 + eed1006/arriveBurst1006 + eed1106/arriveBurst1106 + eed1206/arriveBurst1206 + eed1306/arriveBurst1306 + eed1406/arriveBurst1406)/13;
            pb6 = (pb0106 + pb0206 + pb0306 + pb0406 + pb0506 + pb0706 + pb0806 + pb0906 + pb1006 + pb1106 + pb1206 + pb1306 + pb1406)/(100*13); WATCH(pb6);
            //dropBurst6 = dropBurst0106 + dropBurst0206 + dropBurst0306 + dropBurst0406 + dropBurst0506 + dropBurst0706 + dropBurst0806 + dropBurst0906 + dropBurst1006 + dropBurst1106 + dropBurst1206 + dropBurst1306 + dropBurst1406;
            //arriveBurst6 = (arriveBurst0106 + arriveBurst0206 + arriveBurst0306 + arriveBurst0406 + arriveBurst0506 + arriveBurst0706 + arriveBurst0806 + arriveBurst0906 + arriveBurst1006 + arriveBurst1106 + arriveBurst1206 + arriveBurst1306 + arriveBurst1406);
            //BurstTotal6 = dropBurst6 + arriveBurst6;
            //BurstTotal6 = (BurstTotal0106 + BurstTotal0206 + BurstTotal0306 + BurstTotal0406 + BurstTotal0506 + BurstTotal0706 + BurstTotal0806 + BurstTotal0906 + BurstTotal1006 + BurstTotal1106 + BurstTotal1206 + BurstTotal1306 + BurstTotal1406);
            //BurstGeneratedXX06 = secuencia0106 + secuencia0206 + secuencia0306 + secuencia0406 + secuencia0506 + secuencia0706 + secuencia0806 + secuencia0906 + secuencia1006 + secuencia1106 + secuencia1206 + secuencia1306 + secuencia1406;
            BurstReceivedXX06 = arriveBurst0106 + arriveBurst0206 + arriveBurst0306 + arriveBurst0406 + arriveBurst0506 + arriveBurst0706 + arriveBurst0806 + arriveBurst0906 + arriveBurst1006 + arriveBurst1106 + arriveBurst1206 + arriveBurst1306 + arriveBurst1406;
            BurstDropXX06 = dropBurst0106 + dropBurst0206 + dropBurst0306 + dropBurst0406 + dropBurst0506 + dropBurst0706 + dropBurst0806 + dropBurst0906 + dropBurst1006 + dropBurst1106 + dropBurst1206 + dropBurst1306 + dropBurst1406;
            BurstGeneratedXX06 = BurstReceivedXX06 + BurstDropXX06;
            PBXX06 = (BurstDropXX06)/(BurstGeneratedXX06);

            recordScalar("End to End Delay promedio nodo 6",eed6); recordScalar("Probabilidad de bloqueo nodo 6",PBXX06);
            recordScalar("Porcentaje de rafagas perdidas nodo 6",PBXX06*100);                                                               //recordScalar("Rafagas perdidas nodo 6",dropBurst6);
            recordScalar("Rafagas Generadas Nodo XX06",BurstGeneratedXX06); recordScalar("Rafagas Recibidas Nodo XX06",BurstReceivedXX06); recordScalar("Rafagas Perdidas Nodo XX06",BurstDropXX06);

            //recordScalar("Rafagas Generadas Nodo 6",BurstGeneratedXX06);  recordScalar("Rafagas Recibidas Nodo 06",BurstReceivedXX06); recordScalar("Rafagas Perdidas Nodo 06",BurstDropXX06);
            }
    else if (miDireccion == 7) {
            eed7 = (eed0107/arriveBurst0107 + eed0207/arriveBurst0207 + eed0307/arriveBurst0307 + eed0407/arriveBurst0407 + eed0507/arriveBurst0507 + eed0607/arriveBurst0607 + eed0807/arriveBurst0807 + eed0907/arriveBurst0907 + eed1007/arriveBurst1007 + eed1107/arriveBurst1107 + eed1207/arriveBurst1207 + eed1307/arriveBurst1307 + eed1407/arriveBurst1407)/13;
            pb7 = (pb0107 + pb0207 + pb0307 + pb0407 + pb0507 + pb0607 + pb0807 + pb0907 + pb1007 + pb1107 + pb1207 + pb1307 + pb1407)/(100*13); WATCH(pb7);
            //dropBurst7 = dropBurst0107 + dropBurst0207 + dropBurst0307 + dropBurst0407 + dropBurst0507 + dropBurst0607 + dropBurst0807 + dropBurst0907 + dropBurst1007 + dropBurst1107 + dropBurst1207 + dropBurst1307 + dropBurst1407;
            //arriveBurst7 = (arriveBurst0107 + arriveBurst0207 + arriveBurst0307 + arriveBurst0407 + arriveBurst0507 + arriveBurst0607 + arriveBurst0807 + arriveBurst0907 + arriveBurst1007 + arriveBurst1107 + arriveBurst1207 + arriveBurst1307 + arriveBurst1407);
            //BurstTotal7 = dropBurst7 + arriveBurst7;
            //BurstTotal7 = (BurstTotal0107 + BurstTotal0207 + BurstTotal0307 + BurstTotal0407 + BurstTotal0507 + BurstTotal0607 + BurstTotal0807 + BurstTotal0907 + BurstTotal1007 + BurstTotal1107 + BurstTotal1207 + BurstTotal1307 + BurstTotal1407);
            //BurstGeneratedXX07 = secuencia0107 + secuencia0207 + secuencia0307 + secuencia0407 + secuencia0507 + secuencia0607 + secuencia0807 + secuencia0907 + secuencia1007 + secuencia1107 + secuencia1207 + secuencia1307 + secuencia1407;
            BurstReceivedXX07 = arriveBurst0107 + arriveBurst0207 + arriveBurst0307 + arriveBurst0407 + arriveBurst0507 + arriveBurst0607 + arriveBurst0807 + arriveBurst0907 + arriveBurst1007 + arriveBurst1107 + arriveBurst1207 + arriveBurst1307 + arriveBurst1407;
            BurstDropXX07 = dropBurst0107 + dropBurst0207 + dropBurst0307 + dropBurst0407 + dropBurst0507 + dropBurst0607 + dropBurst0807 + dropBurst0907 + dropBurst1007 + dropBurst1107 + dropBurst1207 + dropBurst1307 + dropBurst1407;
            BurstGeneratedXX07 = BurstReceivedXX07 + BurstDropXX07;
            PBXX07 = (BurstDropXX07)/(BurstGeneratedXX07);

            recordScalar("End to End Delay promedio nodo 7",eed7); recordScalar("Probabilidad de bloqueo nodo 7",PBXX07);
            recordScalar("Porcentaje de rafagas perdidas nodo 7",PBXX07*100);                                                               //recordScalar("Rafagas perdidas nodo 7",dropBurst7);
            recordScalar("Rafagas Generadas Nodo XX07",BurstGeneratedXX07); recordScalar("Rafagas Recibidas Nodo XX07",BurstReceivedXX07); recordScalar("Rafagas Perdidas Nodo XX07",BurstDropXX07);

            //recordScalar("Rafagas Generadas Nodo 7",BurstGeneratedXX07);  recordScalar("Rafagas Recibidas Nodo 07",BurstReceivedXX07); recordScalar("Rafagas Perdidas Nodo 07",BurstDropXX07);
            }
    else if (miDireccion == 8) {
            eed8 = (eed0108/arriveBurst0108 + eed0208/arriveBurst0208 + eed0308/arriveBurst0308 + eed0408/arriveBurst0408 + eed0508/arriveBurst0508 + eed0608/arriveBurst0608 + eed0708/arriveBurst0708 + eed0908/arriveBurst0908 + eed1008/arriveBurst1008 + eed1108/arriveBurst1108 + eed1208/arriveBurst1208 + eed1308/arriveBurst1308 + eed1408/arriveBurst1408)/13;
            pb8 = (pb0108 + pb0208 + pb0308 + pb0408 + pb0508 + pb0608 + pb0708 + pb0908 + pb1008 + pb1108 + pb1208 + pb1308 + pb1408)/(100*13); WATCH(pb8);
            //dropBurst8 = dropBurst0108 + dropBurst0208 + dropBurst0308 + dropBurst0408 + dropBurst0508 + dropBurst0608 + dropBurst0708 + dropBurst0908 + dropBurst1008 + dropBurst1108 + dropBurst1208 + dropBurst1308 + dropBurst1408;
            //arriveBurst8 = (arriveBurst0108 + arriveBurst0208 + arriveBurst0308 + arriveBurst0408 + arriveBurst0508 + arriveBurst0608 + arriveBurst0708 + arriveBurst0908 + arriveBurst1008 + arriveBurst1108 + arriveBurst1208 + arriveBurst1308 + arriveBurst1408);
            //BurstTotal8 = dropBurst8 + arriveBurst8;
            //BurstTotal8 = (BurstTotal0108 + BurstTotal0208 + BurstTotal0308 + BurstTotal0408 + BurstTotal0508 + BurstTotal0608 + BurstTotal0708 + BurstTotal0908 + BurstTotal1008 + BurstTotal1108 + BurstTotal1208 + BurstTotal1308 + BurstTotal1408);
            //BurstGeneratedXX08 = secuencia0108 + secuencia0208 + secuencia0308 + secuencia0408 + secuencia0508 + secuencia0608 + secuencia0708 + secuencia0908 + secuencia1008 + secuencia1108 + secuencia1208 + secuencia1308 + secuencia1408;
            BurstReceivedXX08 = arriveBurst0108 + arriveBurst0208 + arriveBurst0308 + arriveBurst0408 + arriveBurst0508 + arriveBurst0608 + arriveBurst0708 + arriveBurst0908 + arriveBurst1008 + arriveBurst1108 + arriveBurst1208 + arriveBurst1308 + arriveBurst1408;
            BurstDropXX08 = dropBurst0108 + dropBurst0208 + dropBurst0308 + dropBurst0408 + dropBurst0508 + dropBurst0608 + dropBurst0708 + dropBurst0908 + dropBurst1008 + dropBurst1108 + dropBurst1208 + dropBurst1308 + dropBurst1408;
            BurstGeneratedXX08 = BurstReceivedXX08 + BurstDropXX08;


            PBXX08 = (BurstDropXX08)/(BurstGeneratedXX08);
            recordScalar("End to End Delay promedio nodo 8",PBXX08); recordScalar("Probabilidad de bloqueo nodo 8",pb8);
            recordScalar("Porcentaje de rafagas perdidas nodo 8",PBXX08*100);                                                               //recordScalar("Rafagas perdidas nodo 8",dropBurst8);
            recordScalar("Rafagas Generadas Nodo XX08",BurstGeneratedXX08); recordScalar("Rafagas Recibidas Nodo XX08",BurstReceivedXX08); recordScalar("Rafagas Perdidas Nodo XX08",BurstDropXX08);

            //recordScalar("Rafagas Generadas Nodo 8",BurstGeneratedXX08);  recordScalar("Rafagas Recibidas Nodo 08",BurstReceivedXX08); recordScalar("Rafagas Perdidas Nodo 08",BurstDropXX08);
            }
    else if (miDireccion == 9) {
            eed9 = (eed0109/arriveBurst0109 + eed0209/arriveBurst0209 + eed0309/arriveBurst0309 + eed0409/arriveBurst0409 + eed0509/arriveBurst0509 + eed0609/arriveBurst0609 + eed0709/arriveBurst0709 + eed0809/arriveBurst0809 + eed1009/arriveBurst1009 + eed1109/arriveBurst1109 + eed1209/arriveBurst1209 + eed1309/arriveBurst1309 + eed1409/arriveBurst1409)/13;
            pb9 = (pb0109 + pb0209 + pb0309 + pb0409 + pb0509 + pb0609 + pb0709 + pb0809 + pb1009 + pb1109 + pb1209 + pb1309 + pb1409)/(100*13); WATCH(pb9);
            //dropBurst9 = dropBurst0109 + dropBurst0209 + dropBurst0309 + dropBurst0409 + dropBurst0509 + dropBurst0609 + dropBurst0709 + dropBurst0809 + dropBurst1009 + dropBurst1109 + dropBurst1209 + dropBurst1309 + dropBurst1409;
            //arriveBurst9 = (arriveBurst0109 + arriveBurst0209 + arriveBurst0309 + arriveBurst0409 + arriveBurst0509 + arriveBurst0609 + arriveBurst0709 + arriveBurst0809 + arriveBurst1009 + arriveBurst1109 + arriveBurst1209 + arriveBurst1309 + arriveBurst1409);
            //BurstTotal9 = dropBurst9 + arriveBurst9;
            //BurstTotal9 = (BurstTotal0109 + BurstTotal0209 + BurstTotal0309 + BurstTotal0409 + BurstTotal0509 + BurstTotal0609 + BurstTotal0709 + BurstTotal0809 + BurstTotal1009 + BurstTotal1109 + BurstTotal1209 + BurstTotal1309 + BurstTotal1409);
            //BurstGeneratedXX09 = secuencia0109 + secuencia0209 + secuencia0309 + secuencia0409 + secuencia0509 + secuencia0609 + secuencia0709 + secuencia0809 + secuencia1009 + secuencia1109 + secuencia1209 + secuencia1309 + secuencia1409;
            BurstReceivedXX09 = arriveBurst0109 + arriveBurst0209 + arriveBurst0309 + arriveBurst0409 + arriveBurst0509 + arriveBurst0609 + arriveBurst0709 + arriveBurst0809 + arriveBurst1009 + arriveBurst1109 + arriveBurst1209 + arriveBurst1309 + arriveBurst1409;
            BurstDropXX09 = dropBurst0109 + dropBurst0209 + dropBurst0309 + dropBurst0409 + dropBurst0509 + dropBurst0609 + dropBurst0709 + dropBurst0809 + dropBurst1009 + dropBurst1109 + dropBurst1209 + dropBurst1309 + dropBurst1409;
            BurstGeneratedXX09 = BurstReceivedXX09 + BurstDropXX09;

            PBXX09 = (BurstDropXX09)/(BurstGeneratedXX09);
            recordScalar("End to End Delay promedio nodo 9",eed9); recordScalar("Probabilidad de bloqueo nodo 9",PBXX09);
            recordScalar("Porcentaje de rafagas perdidas nodo 9",PBXX09*100);                                                               //recordScalar("Rafagas perdidas nodo 9",dropBurst9);
            recordScalar("Rafagas Generadas Nodo XX09",BurstGeneratedXX09); recordScalar("Rafagas Recibidas Nodo XX09",BurstReceivedXX09); recordScalar("Rafagas Perdidas Nodo XX09",BurstDropXX09);

            //recordScalar("Rafagas Generadas Nodo 9",BurstGeneratedXX09);  recordScalar("Rafagas Recibidas Nodo 09",BurstReceivedXX09); recordScalar("Rafagas Perdidas Nodo 09",BurstDropXX09);
            }
    else if (miDireccion == 10) {
            eed10 = (eed0110/arriveBurst0110 + eed0210/arriveBurst0210 + eed0310/arriveBurst0310 + eed0410/arriveBurst0410 + eed0510/arriveBurst0510 + eed0610/arriveBurst0610 + eed0710/arriveBurst0710 + eed0810/arriveBurst0810 + eed0910/arriveBurst0910 + eed1110/arriveBurst1110 + eed1210/arriveBurst1210 + eed1310/arriveBurst1310 + eed1410/arriveBurst1410)/13;
            pb10 = (pb0110 + pb0210 + pb0310 + pb0410 + pb0510 + pb0610 + pb0710 + pb0810 + pb0910 + pb1110 + pb1210 + pb1310 + pb1410)/(100*13); WATCH(pb10);
            //dropBurst10 = dropBurst0110 + dropBurst0210 + dropBurst0310 + dropBurst0410 + dropBurst0510 + dropBurst0610 + dropBurst0710 + dropBurst0810 + dropBurst0910 + dropBurst1110 + dropBurst1210 + dropBurst1310 + dropBurst1410;
            //arriveBurst10 = (arriveBurst0110 + arriveBurst0210 + arriveBurst0310 + arriveBurst0410 + arriveBurst0510 + arriveBurst0610 + arriveBurst0710 + arriveBurst0810 + arriveBurst0910 + arriveBurst1110 + arriveBurst1210 + arriveBurst1310 + arriveBurst1410);
            //BurstTotal10 = dropBurst10 + arriveBurst10;
            //BurstTotal10 = (BurstTotal0110 + BurstTotal0210 + BurstTotal0310 + BurstTotal0410 + BurstTotal0510 + BurstTotal0610 + BurstTotal0710 + BurstTotal0810 + BurstTotal0910 + BurstTotal1110 + BurstTotal1210 + BurstTotal1310 + BurstTotal1410);
            //BurstGeneratedXX10 = secuencia0110 + secuencia0210 + secuencia0310 + secuencia0410 + secuencia0510 + secuencia0610 + secuencia0710 + secuencia0810 + secuencia0910 + secuencia1110 + secuencia1210 + secuencia1310 + secuencia1410;
            BurstReceivedXX10 = arriveBurst0110 + arriveBurst0210 + arriveBurst0310 + arriveBurst0410 + arriveBurst0510 + arriveBurst0610 + arriveBurst0710 + arriveBurst0810 + arriveBurst0910 + arriveBurst1110 + arriveBurst1210 + arriveBurst1310 + arriveBurst1410;
            BurstDropXX10 = dropBurst0110 + dropBurst0210 + dropBurst0310 + dropBurst0410 + dropBurst0510 + dropBurst0610 + dropBurst0710 + dropBurst0810 + dropBurst0910 + dropBurst1110 + dropBurst1210 + dropBurst1310 + dropBurst1410;
            BurstGeneratedXX10 = BurstReceivedXX10 + BurstDropXX10;
            PBXX10 = (BurstDropXX10)/(BurstGeneratedXX10);
            recordScalar("End to End Delay promedio nodo 10",eed10); recordScalar("Probabilidad de bloqueo nodo 10",PBXX10);
            recordScalar("Porcentaje de rafagas perdidas nodo 10",PBXX10*100);                                                              //recordScalar("Rafagas perdidas nodo 10",dropBurst10);
            recordScalar("Rafagas Generadas Nodo XX10",BurstGeneratedXX10); recordScalar("Rafagas Recibidas Nodo XX10",BurstReceivedXX10); recordScalar("Rafagas Perdidas Nodo XX10",BurstDropXX10);

            //recordScalar("Rafagas Generadas Nodo 10",BurstGeneratedXX10);  recordScalar("Rafagas Recibidas Nodo 10",BurstReceivedXX10); recordScalar("Rafagas Perdidas Nodo 10",BurstDropXX10);
            }
    else if (miDireccion == 11) {
            eed11 = (eed0111/arriveBurst0111 + eed0211/arriveBurst0211 + eed0311/arriveBurst0311 + eed0411/arriveBurst0411 + eed0511/arriveBurst0511 + eed0611/arriveBurst0611 + eed0711/arriveBurst0711 + eed0811/arriveBurst0811 + eed0911/arriveBurst0911 + eed1011/arriveBurst1011 + eed1211/arriveBurst1211 + eed1311/arriveBurst1311 + eed1411/arriveBurst1411)/13;
            pb11 = (pb0111 + pb0211 + pb0311 + pb0411 + pb0511 + pb0611 + pb0711 + pb0811 + pb0911 + pb1011 + pb1211 + pb1311 + pb1411)/(100*13); WATCH(pb11);
            //dropBurst11 = dropBurst0111 + dropBurst0211 + dropBurst0311 + dropBurst0411 + dropBurst0511 + dropBurst0611 + dropBurst0711 + dropBurst0811 + dropBurst0911 + dropBurst1011 + dropBurst1211 + dropBurst1311 + dropBurst1411;
            //arriveBurst11 = (arriveBurst0111 + arriveBurst0211 + arriveBurst0311 + arriveBurst0411 + arriveBurst0511 + arriveBurst0611 + arriveBurst0711 + arriveBurst0811 + arriveBurst0911 + arriveBurst1011 + arriveBurst1211 + arriveBurst1311 + arriveBurst1411);
            //BurstTotal11 = dropBurst11 + arriveBurst11;
            //BurstTotal11 = (BurstTotal0111 + BurstTotal0211 + BurstTotal0311 + BurstTotal0411 + BurstTotal0511 + BurstTotal0611 + BurstTotal0711 + BurstTotal0811 + BurstTotal0911 + BurstTotal1011 + BurstTotal1211 + BurstTotal1311 + BurstTotal1411);
            //BurstGeneratedXX11 = secuencia0111 + secuencia0211 + secuencia0311 + secuencia0411 + secuencia0511 + secuencia0611 + secuencia0711 + secuencia0811 + secuencia0911 + secuencia1011 + secuencia1211 + secuencia1311 + secuencia1411;
            BurstReceivedXX11 = arriveBurst0111 + arriveBurst0211 + arriveBurst0311 + arriveBurst0411 + arriveBurst0511 + arriveBurst0611 + arriveBurst0711 + arriveBurst0811 + arriveBurst0911 + arriveBurst1011 + arriveBurst1211 + arriveBurst1311 + arriveBurst1411;
            BurstDropXX11 = dropBurst0111 + dropBurst0211 + dropBurst0311 + dropBurst0411 + dropBurst0511 + dropBurst0611 + dropBurst0711 + dropBurst0811 + dropBurst0911 + dropBurst1011 + dropBurst1211 + dropBurst1311 + dropBurst1411;
            BurstGeneratedXX11 = BurstReceivedXX11 + BurstDropXX11;
            PBXX11 = (BurstDropXX11)/(BurstGeneratedXX11);
            recordScalar("End to End Delay promedio nodo 11",eed11); recordScalar("Probabilidad de bloqueo nodo 11",PBXX11);
            recordScalar("Porcentaje de rafagas perdidas nodo 11",PBXX11*100);                                                              //recordScalar("Rafagas perdidas nodo 11",dropBurst11);
            recordScalar("Rafagas Generadas Nodo XX11",BurstGeneratedXX11); recordScalar("Rafagas Recibidas Nodo XX11",BurstReceivedXX11); recordScalar("Rafagas Perdidas Nodo XX11",BurstDropXX11);

            //recordScalar("Rafagas Generadas Nodo 11",BurstGeneratedXX11);  recordScalar("Rafagas Recibidas Nodo 11",BurstReceivedXX11); recordScalar("Rafagas Perdidas Nodo 11",BurstDropXX11);
            }
    else if (miDireccion == 12) {
            eed12 = (eed0112/arriveBurst0112 + eed0212/arriveBurst0212 + eed0312/arriveBurst0312 + eed0412/arriveBurst0412 + eed0512/arriveBurst0512 + eed0612/arriveBurst0612 + eed0712/arriveBurst0712 + eed0812/arriveBurst0812 + eed0912/arriveBurst0912 + eed1012/arriveBurst1012 + eed1112/arriveBurst1112 + eed1312/arriveBurst1312 + eed1412/arriveBurst1412)/13;
            pb12 = (pb0112 + pb0212 + pb0312 + pb0412 + pb0512 + pb0612 + pb0712 + pb0812 + pb0912 + pb1012 + pb1112 + pb1312 + pb1412)/(100*13); WATCH(pb12);
            //dropBurst12 = dropBurst0112 + dropBurst0212 + dropBurst0312 + dropBurst0412 + dropBurst0512 + dropBurst0612 + dropBurst0712 + dropBurst0812 + dropBurst0912 + dropBurst1012 + dropBurst1112 + dropBurst1312 + dropBurst1412;
            //arriveBurst12 = (arriveBurst0112 + arriveBurst0212 + arriveBurst0312 + arriveBurst0412 + arriveBurst0512 + arriveBurst0612 + arriveBurst0712 + arriveBurst0812 + arriveBurst0912 + arriveBurst1012 + arriveBurst1112 + arriveBurst1312 + arriveBurst1412);
            //BurstTotal12 = dropBurst12 + arriveBurst12;
            //BurstTotal12 = (BurstTotal0112 + BurstTotal0212 + BurstTotal0312 + BurstTotal0412 + BurstTotal0512 + BurstTotal0612 + BurstTotal0712 + BurstTotal0812 + BurstTotal0912 + BurstTotal1012 + BurstTotal1112 + BurstTotal1312 + BurstTotal1412);
            //BurstGeneratedXX12 = secuencia0112 + secuencia0212 + secuencia0312 + secuencia0412 + secuencia0512 + secuencia0612 + secuencia0712 + secuencia0812 + secuencia0912 + secuencia1012 + secuencia1112 + secuencia1312 + secuencia1412;
            BurstReceivedXX12 = arriveBurst0112 + arriveBurst0212 + arriveBurst0312 + arriveBurst0412 + arriveBurst0512 + arriveBurst0612 + arriveBurst0712 + arriveBurst0812 + arriveBurst0912 + arriveBurst1012 + arriveBurst1112 + arriveBurst1312 + arriveBurst1412;
            BurstDropXX12 = dropBurst0112 + dropBurst0212 + dropBurst0312 + dropBurst0412 + dropBurst0512 + dropBurst0612 + dropBurst0712 + dropBurst0812 + dropBurst0912 + dropBurst1012 + dropBurst1112 + dropBurst1312 + dropBurst1412;
            BurstGeneratedXX12 = BurstReceivedXX12 + BurstDropXX12;
            PBXX12 = (BurstDropXX12)/(BurstGeneratedXX12);
            recordScalar("End to End Delay promedio nodo 12",eed12); recordScalar("Probabilidad de bloqueo nodo 12",PBXX12);
            recordScalar("Porcentaje de rafagas perdidas nodo 12",PBXX12*100);                                                             //recordScalar("Rafagas perdidas nodo 12",dropBurst12);
            recordScalar("Rafagas Generadas Nodo XX12",BurstGeneratedXX12); recordScalar("Rafagas Recibidas Nodo XX12",BurstReceivedXX12); recordScalar("Rafagas Perdidas Nodo XX12",BurstDropXX12);

            //recordScalar("Rafagas Generadas Nodo 12",BurstGeneratedXX12); recordScalar("Rafagas Recibidas Nodo 12",BurstReceivedXX12); recordScalar("Rafagas Perdidas Nodo 12",BurstDropXX12);
            }
    else if (miDireccion == 13) {
            eed13 = (eed0113/arriveBurst0113 + eed0213/arriveBurst0213 + eed0313/arriveBurst0313 + eed0413/arriveBurst0413 + eed0513/arriveBurst0513 + eed0613/arriveBurst0613 + eed0713/arriveBurst0713 + eed0813/arriveBurst0813 + eed0913/arriveBurst0913 + eed1013/arriveBurst1013 + eed1113/arriveBurst1113 + eed1213/arriveBurst1213 + eed1413/arriveBurst1413)/13;
            pb13 = (pb0113 + pb0213 + pb0313 + pb0413 + pb0513 + pb0613 + pb0713 + pb0813 + pb0913 + pb1013 + pb1113 + pb1213 + pb1413)/(100*13); WATCH(pb13);
            //dropBurst13 = dropBurst0113 + dropBurst0213 + dropBurst0313 + dropBurst0413 + dropBurst0513 + dropBurst0613 + dropBurst0713 + dropBurst0813 + dropBurst0913 + dropBurst1013 + dropBurst1113 + dropBurst1213 + dropBurst1413;
            //arriveBurst13 = (arriveBurst0113 + arriveBurst0213 + arriveBurst0313 + arriveBurst0413 + arriveBurst0513 + arriveBurst0613 + arriveBurst0713 + arriveBurst0813 + arriveBurst0913 + arriveBurst1013 + arriveBurst1113 + arriveBurst1213 + arriveBurst1413);
            //BurstTotal13 = dropBurst13 + arriveBurst13;
            //BurstTotal13 = (BurstTotal0113 + BurstTotal0213 + BurstTotal0313 + BurstTotal0413 + BurstTotal0513 + BurstTotal0613 + BurstTotal0713 + BurstTotal0813 + BurstTotal0913 + BurstTotal1013 + BurstTotal1113 + BurstTotal1213 + BurstTotal1413);
            //BurstGeneratedXX13 = secuencia0113 + secuencia0213 + secuencia0313 + secuencia0413 + secuencia0513 + secuencia0613 + secuencia0713 + secuencia0813 + secuencia0913 + secuencia1013 + secuencia1113 + secuencia1213 + secuencia1413;
            BurstReceivedXX13 = arriveBurst0113 + arriveBurst0213 + arriveBurst0313 + arriveBurst0413 + arriveBurst0513 + arriveBurst0613 + arriveBurst0713 + arriveBurst0813 + arriveBurst0913 + arriveBurst1013 + arriveBurst1113 + arriveBurst1213 + arriveBurst1413;
            BurstDropXX13 = dropBurst0113 + dropBurst0213 + dropBurst0313 + dropBurst0413 + dropBurst0513 + dropBurst0613 + dropBurst0713 + dropBurst0813 + dropBurst0913 + dropBurst1013 + dropBurst1113 + dropBurst1213 + dropBurst1413;
            BurstGeneratedXX13 = BurstReceivedXX13 + BurstDropXX13;
            PBXX13 = (BurstDropXX13)/(BurstGeneratedXX13);
            recordScalar("End to End Delay promedio nodo 13",eed13); recordScalar("Probabilidad de bloqueo nodo 13",PBXX13);
            recordScalar("Porcentaje de rafagas perdidas nodo 13",PBXX13*100);                                                             //recordScalar("Rafagas perdidas nodo 13",dropBurst13);
            recordScalar("Rafagas Generadas Nodo XX13",BurstGeneratedXX13); recordScalar("Rafagas Recibidas Nodo XX13",BurstReceivedXX13); recordScalar("Rafagas Perdidas Nodo XX13",BurstDropXX13);

            //recordScalar("Rafagas Generadas Nodo 13",BurstGeneratedXX13); recordScalar("Rafagas Recibidas Nodo 13",BurstReceivedXX13); recordScalar("Rafagas Perdidas Nodo 13",BurstDropXX13);
            }
    else if (miDireccion == 14) {
            eed14 = (eed0114/arriveBurst0114 + eed0214/arriveBurst0214 + eed0314/arriveBurst0314 + eed0414/arriveBurst0414 + eed0514/arriveBurst0514 + eed0614/arriveBurst0614 + eed0714/arriveBurst0714 + eed0814/arriveBurst0814 + eed0914/arriveBurst0914 + eed1014/arriveBurst1014 + eed1114/arriveBurst1114 + eed1214/arriveBurst1214 + eed1314/arriveBurst1314)/13;
            pb14 = (pb0114 + pb0214 + pb0314 + pb0414 + pb0514 + pb0614 + pb0714 + pb0814 + pb0914 + pb1014 + pb1114 + pb1214 + pb1314)/(100*13); WATCH(pb14);
            //dropBurst14 = dropBurst0114 + dropBurst0214 + dropBurst0314 + dropBurst0414 + dropBurst0514 + dropBurst0614 + dropBurst0714 + dropBurst0814 + dropBurst0914 + dropBurst1014 + dropBurst1114 + dropBurst1214 + dropBurst1314;
            //arriveBurst14 = (arriveBurst0114 + arriveBurst0214 + arriveBurst0314 + arriveBurst0414 + arriveBurst0514 + arriveBurst0614 + arriveBurst0714 + arriveBurst0814 + arriveBurst0914 + arriveBurst1014 + arriveBurst1114 + arriveBurst1214 + arriveBurst1314);
            //BurstTotal14 = dropBurst14 + arriveBurst14;
            //BurstTotal14 = (BurstTotal0114 + BurstTotal0214 + BurstTotal0314 + BurstTotal0414 + BurstTotal0514 + BurstTotal0614 + BurstTotal0714 + BurstTotal0814 + BurstTotal0914 + BurstTotal1014 + BurstTotal1114 + BurstTotal1214 + BurstTotal1314);
            //BurstGeneratedXX14 = secuencia0114 + secuencia0214 + secuencia0314 + secuencia0414 + secuencia0514 + secuencia0614 + secuencia0714 + secuencia0814 + secuencia0914 + secuencia1014 + secuencia1114 + secuencia1214 + secuencia1314;
            BurstReceivedXX14 = arriveBurst0114 + arriveBurst0214 + arriveBurst0314 + arriveBurst0414 + arriveBurst0514 + arriveBurst0614 + arriveBurst0714 + arriveBurst0814 + arriveBurst0914 + arriveBurst1014 + arriveBurst1114 + arriveBurst1214 + arriveBurst1314;
            BurstDropXX14 = dropBurst0114 + dropBurst0214 + dropBurst0314 + dropBurst0414 + dropBurst0514 + dropBurst0614 + dropBurst0714 + dropBurst0814 + dropBurst0914 + dropBurst1014 + dropBurst1114 + dropBurst1214 + dropBurst1314;
            BurstGeneratedXX14 = BurstReceivedXX14 + BurstDropXX14;
            PBXX14 = (BurstDropXX14)/(BurstGeneratedXX14);
            recordScalar("End to End Delay promedio nodo 14",eed14); recordScalar("Probabilidad de bloqueo nodo 14",PBXX14);
            recordScalar("Porcentaje de rafagas perdidas nodo 14",PBXX14*100);                                                             //recordScalar("Rafagas perdidas nodo 14",dropBurst14);
            recordScalar("Rafagas Generadas Nodo XX14",BurstGeneratedXX14); recordScalar("Rafagas Recibidas Nodo XX14",BurstReceivedXX14); recordScalar("Rafagas Perdidas Nodo XX14",BurstDropXX14);
            //recordScalar("Rafagas Generadas Nodo 14",BurstGeneratedXX14); recordScalar("Rafagas Recibidas Nodo 14",BurstReceivedXX14); recordScalar("Rafagas Perdidas Nodo 14",BurstDropXX14);
            }



            ganancia0 = (ganancia0/count0); recordScalar("Ganancia espectral clase 0 en %",ganancia0);
            ganancia1 = (ganancia1/count1); recordScalar("Ganancia espectral clase 1 en %",ganancia1);
            ganancia2 = (ganancia2/count2); recordScalar("Ganancia espectral clase 2 en %",ganancia2);

            ganancia = (count0*ganancia0 + count1*ganancia1 + count2*ganancia2)/((count0 + count1 + count2)*100); recordScalar("Ganancia espectral Total%",ganancia);

}

