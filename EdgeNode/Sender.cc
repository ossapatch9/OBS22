/*
 * Sender.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */
#include "Sender.h"

Define_Module(Sender);

Sender::~Sender()
{
 free(horizon);
 //Se libera memoria para el vector horizonte
 int i;
 for(i=0;i<numLambdas;i++)
   {
    delete horizonVec[i];
   }
}



void Sender::initialize()
{
    numSaltos = 0;

    int i;

    //Se establecen los parámetros del .ned
    numLambdas = par("numLambdas");
    dataRate = par("dataRate");
    BCPSize = par("BCPSize");
    guardTime = par("guardTime");
    maxSchedBurstSize = par("maxSchedBurstSize");
    int maxSchedBurstSizeInBits = maxSchedBurstSize*8;
    scheduleBursts.setMaxSize(maxSchedBurstSizeInBits);
    scheduleBursts.setMaxElems((int)par("maxSchedBurstElems"));
    testing = par("testing");
    control_is_busy = false;

    //Se establece el mapa de colores
    const char* colourString = par("colours");

    colour = (int*)calloc(numLambdas,sizeof(int));
    int j;

    if(strcmp(colourString,"") != 0)
     {
      cStringTokenizer tokenizer(colourString);

      for(j=0;j<numLambdas;j++)
         colour[j] = atoi(tokenizer.nextToken());
     } else{
            for(j=0;j<numLambdas;j++)
            colour[j] = j;
           }

    //Se establece el vector horizonte con ceros
    horizon = (simtime_t*)calloc(numLambdas,sizeof(simtime_t));
    horizonVec.reserve(numLambdas);

    for(i=0;i<numLambdas;i++)
       {
        horizon[i] = 0;
        char buf[32];
        sprintf(buf, "horizonVector{%d}", i);
        horizonVec.push_back(new cOutVector(buf));
        WATCH(horizon[i]);
       }


         waitingBCP.setName("waitingBCPs");

         burstRecv = 0;             burstSend = 0;              burstSendCore = 0;

         burstDroppedByOffset = 0;  burstDroppedByQueue = 0;

         //variable para Proba.Bloqueo
         secuencia0101 = 0; secuencia0201 = 0; secuencia0301 = 0; secuencia0401 = 0; secuencia0501 = 0; secuencia0601 = 0; secuencia0701 = 0; //Destino 01 //Origen XX
         secuencia0801 = 0; secuencia0901 = 0; secuencia1001 = 0; secuencia1101 = 0; secuencia1201 = 0; secuencia1301 = 0; secuencia1401 = 0;
         secuencia0102 = 0; secuencia0202 = 0; secuencia0302 = 0; secuencia0402 = 0; secuencia0502 = 0; secuencia0602 = 0; secuencia0702 = 0; //Destino 02 //Origen XX
         secuencia0802 = 0; secuencia0902 = 0; secuencia1002 = 0; secuencia1102 = 0; secuencia1202 = 0; secuencia1302 = 0; secuencia1402 = 0;
         secuencia0103 = 0; secuencia0203 = 0; secuencia0303 = 0; secuencia0403 = 0; secuencia0503 = 0; secuencia0603 = 0; secuencia0703 = 0; //Destino 03 //Origen XX
         secuencia0803 = 0; secuencia0903 = 0; secuencia1003 = 0; secuencia1103 = 0; secuencia1203 = 0; secuencia1303 = 0; secuencia1403 = 0;
         secuencia0104 = 0; secuencia0204 = 0; secuencia0304 = 0; secuencia0404 = 0; secuencia0504 = 0; secuencia0604 = 0; secuencia0704 = 0; //Destino 04 //Origen XX
         secuencia0804 = 0; secuencia0904 = 0; secuencia1004 = 0; secuencia1104 = 0; secuencia1204 = 0; secuencia1304 = 0; secuencia1404 = 0;
         secuencia0105 = 0; secuencia0205 = 0; secuencia0305 = 0; secuencia0405 = 0; secuencia0505 = 0; secuencia0605 = 0; secuencia0705 = 0; //Destino 05 //Origen XX
         secuencia0805 = 0; secuencia0905 = 0; secuencia1005 = 0; secuencia1105 = 0; secuencia1205 = 0; secuencia1305 = 0; secuencia1405 = 0;
         secuencia0106 = 0; secuencia0206 = 0; secuencia0306 = 0; secuencia0406 = 0; secuencia0506 = 0; secuencia0606 = 0; secuencia0706 = 0; //Destino 06 //Origen XX
         secuencia0806 = 0; secuencia0906 = 0; secuencia1006 = 0; secuencia1106 = 0; secuencia1206 = 0; secuencia1306 = 0; secuencia1406 = 0;
         secuencia0107 = 0; secuencia0207 = 0; secuencia0307 = 0; secuencia0407 = 0; secuencia0507 = 0; secuencia0607 = 0; secuencia0707 = 0; //Destino 07 //Origen XX
         secuencia0807 = 0; secuencia0907 = 0; secuencia1007 = 0; secuencia1107 = 0; secuencia1207 = 0; secuencia1307 = 0; secuencia1407 = 0;
         secuencia0108 = 0; secuencia0208 = 0; secuencia0308 = 0; secuencia0408 = 0; secuencia0508 = 0; secuencia0608 = 0; secuencia0708 = 0; //Destino 08 //Origen XX
         secuencia0808 = 0; secuencia0908 = 0; secuencia1008 = 0; secuencia1108 = 0; secuencia1208 = 0; secuencia1308 = 0; secuencia1408 = 0;
         secuencia0109 = 0; secuencia0209 = 0; secuencia0309 = 0; secuencia0409 = 0; secuencia0509 = 0; secuencia0609 = 0; secuencia0709 = 0; //Destino 09 //Origen XX
         secuencia0809 = 0; secuencia0909 = 0; secuencia1009 = 0; secuencia1109 = 0; secuencia1209 = 0; secuencia1309 = 0; secuencia1409 = 0;
         secuencia0110 = 0; secuencia0210 = 0; secuencia0310 = 0; secuencia0410 = 0; secuencia0510 = 0; secuencia0610 = 0; secuencia0710 = 0; //Destino 10 //Origen XX
         secuencia0810 = 0; secuencia0910 = 0; secuencia1010 = 0; secuencia1110 = 0; secuencia1210 = 0; secuencia1310 = 0; secuencia1410 = 0;
         secuencia0111 = 0; secuencia0211 = 0; secuencia0311 = 0; secuencia0411 = 0; secuencia0511 = 0; secuencia0611 = 0; secuencia0711 = 0; //Destino 11 //Origen XX
         secuencia0811 = 0; secuencia0911 = 0; secuencia1011 = 0; secuencia1111 = 0; secuencia1211 = 0; secuencia1311 = 0; secuencia1411 = 0;
         secuencia0112 = 0; secuencia0212 = 0; secuencia0312 = 0; secuencia0412 = 0; secuencia0512 = 0; secuencia0612 = 0; secuencia0712 = 0; //Destino 12 //Origen XX
         secuencia0812 = 0; secuencia0912 = 0; secuencia1012 = 0; secuencia1112 = 0; secuencia1212 = 0; secuencia1312 = 0; secuencia1412 = 0;
         secuencia0113 = 0; secuencia0213 = 0; secuencia0313 = 0; secuencia0413 = 0; secuencia0513 = 0; secuencia0613 = 0; secuencia0713 = 0; //Destino 13 //Origen XX
         secuencia0813 = 0; secuencia0913 = 0; secuencia1013 = 0; secuencia1113 = 0; secuencia1213 = 0; secuencia1313 = 0; secuencia1413 = 0;
         secuencia0114 = 0; secuencia0214 = 0; secuencia0314 = 0; secuencia0414 = 0; secuencia0514 = 0; secuencia0614 = 0; secuencia0714 = 0; //Destino 14 //Origen XX
         secuencia0814 = 0; secuencia0914 = 0; secuencia1014 = 0; secuencia1114 = 0; secuencia1214 = 0; secuencia1314 = 0; secuencia1414 = 0;



         WATCH(burstDroppedByOffset);  WATCH(burstDroppedByQueue);

         WATCH(burstSender_Core01XX); WATCH(burstSender_Core02XX); WATCH(burstSender_Core03XX); WATCH(burstSender_Core04XX);  WATCH(burstSender_Core05XX); WATCH(burstSender_Core06XX); WATCH(burstSender_Core07XX);
         WATCH(burstSender_Core08XX); WATCH(burstSender_Core09XX); WATCH(burstSender_Core10XX);  WATCH(burstSender_Core11XX); WATCH(burstSender_Core12XX); WATCH(burstSender_Core13XX); WATCH(burstSender_Core14XX);

         WATCH(burstGeneratedXX01); WATCH(burstGeneratedXX02);  WATCH(burstGeneratedXX03); WATCH(burstGeneratedXX04); WATCH(burstGeneratedXX05); WATCH(burstGeneratedXX05);
         WATCH(burstGeneratedXX06); WATCH(burstGeneratedXX07);  WATCH(burstGeneratedXX08); WATCH(burstGeneratedXX09); WATCH(burstGeneratedXX10); WATCH(burstGeneratedXX11);
         WATCH(burstGeneratedXX12); WATCH(burstGeneratedXX13);  WATCH(burstGeneratedXX14);

         WATCH(burstGenerated0101); WATCH(burstGenerated0202);  WATCH(burstGenerated0303); WATCH(burstGenerated0404); WATCH(burstGenerated0505); WATCH(burstGenerated0606); WATCH(burstGenerated0707);
         WATCH(burstGenerated0808); WATCH(burstGenerated0909);  WATCH(burstGenerated1010); WATCH(burstGenerated1111); WATCH(burstGenerated1212); WATCH(burstGenerated1313); WATCH(burstGenerated1414);

         WATCH(secuencia0101); WATCH(secuencia0201); WATCH(secuencia0301); WATCH(secuencia0401); WATCH(secuencia0501); WATCH(secuencia0601); WATCH(secuencia0701); //Destino 01) //Origen XX
         WATCH(secuencia0801); WATCH(secuencia0901); WATCH(secuencia1001); WATCH(secuencia1101); WATCH(secuencia1201); WATCH(secuencia1301); WATCH(secuencia1401);
         WATCH(secuencia0102); WATCH(secuencia0202); WATCH(secuencia0302); WATCH(secuencia0402); WATCH(secuencia0502); WATCH(secuencia0602); WATCH(secuencia0702); //Destino 02) //Origen XX
         WATCH(secuencia0802); WATCH(secuencia0902); WATCH(secuencia1002); WATCH(secuencia1102); WATCH(secuencia1202); WATCH(secuencia1302); WATCH(secuencia1402);
         WATCH(secuencia0103); WATCH(secuencia0203); WATCH(secuencia0303); WATCH(secuencia0403); WATCH(secuencia0503); WATCH(secuencia0603); WATCH(secuencia0703); //Destino 03) //Origen XX
         WATCH(secuencia0803); WATCH(secuencia0903); WATCH(secuencia1003); WATCH(secuencia1103); WATCH(secuencia1203); WATCH(secuencia1303); WATCH(secuencia1403);
         WATCH(secuencia0104); WATCH(secuencia0204); WATCH(secuencia0304); WATCH(secuencia0404); WATCH(secuencia0504); WATCH(secuencia0604); WATCH(secuencia0704); //Destino 04) //Origen XX
         WATCH(secuencia0804); WATCH(secuencia0904); WATCH(secuencia1004); WATCH(secuencia1104); WATCH(secuencia1204); WATCH(secuencia1304); WATCH(secuencia1404);
         WATCH(secuencia0105); WATCH(secuencia0205); WATCH(secuencia0305); WATCH(secuencia0405); WATCH(secuencia0505); WATCH(secuencia0605); WATCH(secuencia0705); //Destino 05) //Origen XX
         WATCH(secuencia0805); WATCH(secuencia0905); WATCH(secuencia1005); WATCH(secuencia1105); WATCH(secuencia1205); WATCH(secuencia1305); WATCH(secuencia1405);
         WATCH(secuencia0106); WATCH(secuencia0206); WATCH(secuencia0306); WATCH(secuencia0406); WATCH(secuencia0506); WATCH(secuencia0606); WATCH(secuencia0706); //Destino 06) //Origen XX
         WATCH(secuencia0806); WATCH(secuencia0906); WATCH(secuencia1006); WATCH(secuencia1106); WATCH(secuencia1206); WATCH(secuencia1306); WATCH(secuencia1406);
         WATCH(secuencia0107); WATCH(secuencia0207); WATCH(secuencia0307); WATCH(secuencia0407); WATCH(secuencia0507); WATCH(secuencia0607); WATCH(secuencia0707); //Destino 07) //Origen XX
         WATCH(secuencia0807); WATCH(secuencia0907); WATCH(secuencia1007); WATCH(secuencia1107); WATCH(secuencia1207); WATCH(secuencia1307); WATCH(secuencia1407);
         WATCH(secuencia0108); WATCH(secuencia0208); WATCH(secuencia0308); WATCH(secuencia0408); WATCH(secuencia0508); WATCH(secuencia0608); WATCH(secuencia0708); //Destino 08) //Origen XX
         WATCH(secuencia0808); WATCH(secuencia0908); WATCH(secuencia1008); WATCH(secuencia1108); WATCH(secuencia1208); WATCH(secuencia1308); WATCH(secuencia1408);
         WATCH(secuencia0109); WATCH(secuencia0209); WATCH(secuencia0309); WATCH(secuencia0409); WATCH(secuencia0509); WATCH(secuencia0609); WATCH(secuencia0709); //Destino 09) //Origen XX
         WATCH(secuencia0809); WATCH(secuencia0909); WATCH(secuencia1009); WATCH(secuencia1109); WATCH(secuencia1209); WATCH(secuencia1309); WATCH(secuencia1409);
         WATCH(secuencia0110); WATCH(secuencia0210); WATCH(secuencia0310); WATCH(secuencia0410); WATCH(secuencia0510); WATCH(secuencia0610); WATCH(secuencia0710); //Destino 10) //Origen XX
         WATCH(secuencia0810); WATCH(secuencia0910); WATCH(secuencia1010); WATCH(secuencia1110); WATCH(secuencia1210); WATCH(secuencia1310); WATCH(secuencia1410);
         WATCH(secuencia0111); WATCH(secuencia0211); WATCH(secuencia0311); WATCH(secuencia0411); WATCH(secuencia0511); WATCH(secuencia0611); WATCH(secuencia0711); //Destino 11) //Origen XX
         WATCH(secuencia0811); WATCH(secuencia0911); WATCH(secuencia1011); WATCH(secuencia1111); WATCH(secuencia1211); WATCH(secuencia1311); WATCH(secuencia1411);
         WATCH(secuencia0112); WATCH(secuencia0212); WATCH(secuencia0312); WATCH(secuencia0412); WATCH(secuencia0512); WATCH(secuencia0612); WATCH(secuencia0712); //Destino 12) //Origen XX
         WATCH(secuencia0812); WATCH(secuencia0912); WATCH(secuencia1012); WATCH(secuencia1112); WATCH(secuencia1212); WATCH(secuencia1312); WATCH(secuencia1412);
         WATCH(secuencia0113); WATCH(secuencia0213); WATCH(secuencia0313); WATCH(secuencia0413); WATCH(secuencia0513); WATCH(secuencia0613); WATCH(secuencia0713); //Destino 13) //Origen XX
         WATCH(secuencia0813); WATCH(secuencia0913); WATCH(secuencia1013); WATCH(secuencia1113); WATCH(secuencia1213); WATCH(secuencia1313); WATCH(secuencia1413);
         WATCH(secuencia0114); WATCH(secuencia0214); WATCH(secuencia0314); WATCH(secuencia0414); WATCH(secuencia0514); WATCH(secuencia0614); WATCH(secuencia0714); //Destino 14) //Origen XX
         WATCH(secuencia0814); WATCH(secuencia0914); WATCH(secuencia1014); WATCH(secuencia1114); WATCH(secuencia1214); WATCH(secuencia1314); WATCH(secuencia1414);


         WATCH(burstRecv);     WATCH(burstSendCore);

}

void Sender::handleMessage(cMessage *msg)
{
 BurstSenderInfo *info;


 if(!(msg->isSelfMessage())) // Recibe una ráfaga desde BurstAssembler (Burstifier)
   {
    //Emite el mensaje a ráfaga
    Burst *rfg = check_and_cast<Burst*>(msg);

    burstTam.record(rfg->getBitLength());
    burstRecv++;



//#============================== #============================== #==============================
  //codigo para calculo de probabilidad de bloqueo    //***codigo nuevo***
//#============================== #============================== #==============================
   sourceAddress = rfg->getSourceAddress();   destAddress   = rfg->getDestAddress();

   if      (sourceAddress == 1  && destAddress == 1) {}
   else if (sourceAddress == 2  && destAddress == 1) {secuencia0201++;  rfg->setSecuencia(secuencia0201);}
   else if (sourceAddress == 3  && destAddress == 1) {secuencia0301++;  rfg->setSecuencia(secuencia0301);}
   else if (sourceAddress == 4  && destAddress == 1) {secuencia0401++;  rfg->setSecuencia(secuencia0401);}
   else if (sourceAddress == 5  && destAddress == 1) {secuencia0501++;  rfg->setSecuencia(secuencia0501);}
   else if (sourceAddress == 6  && destAddress == 1) {secuencia0601++;  rfg->setSecuencia(secuencia0601);}
   else if (sourceAddress == 7  && destAddress == 1) {secuencia0701++;  rfg->setSecuencia(secuencia0701);}
   else if (sourceAddress == 8  && destAddress == 1) {secuencia0801++;  rfg->setSecuencia(secuencia0801);}
   else if (sourceAddress == 9  && destAddress == 1) {secuencia0901++;  rfg->setSecuencia(secuencia0901);}
   else if (sourceAddress == 10 && destAddress == 1) {secuencia1001++;  rfg->setSecuencia(secuencia1001);}
   else if (sourceAddress == 11 && destAddress == 1) {secuencia1101++;  rfg->setSecuencia(secuencia1101);}
   else if (sourceAddress == 12 && destAddress == 1) {secuencia1201++;  rfg->setSecuencia(secuencia1201);}
   else if (sourceAddress == 13 && destAddress == 1) {secuencia1301++;  rfg->setSecuencia(secuencia1301);}
   else if (sourceAddress == 14 && destAddress == 1) {secuencia1401++;  rfg->setSecuencia(secuencia1401);}

   if      (sourceAddress == 1  && destAddress == 2) {secuencia0102++;  rfg->setSecuencia(secuencia0102);}
   else if (sourceAddress == 2  && destAddress == 2) {}
   else if (sourceAddress == 3  && destAddress == 2) {secuencia0302++;  rfg->setSecuencia(secuencia0302);}
   else if (sourceAddress == 4  && destAddress == 2) {secuencia0402++;  rfg->setSecuencia(secuencia0402);}
   else if (sourceAddress == 5  && destAddress == 2) {secuencia0502++;  rfg->setSecuencia(secuencia0502);}
   else if (sourceAddress == 6  && destAddress == 2) {secuencia0602++;  rfg->setSecuencia(secuencia0602);}
   else if (sourceAddress == 7  && destAddress == 2) {secuencia0702++;  rfg->setSecuencia(secuencia0702);}
   else if (sourceAddress == 8  && destAddress == 2) {secuencia0802++;  rfg->setSecuencia(secuencia0802);}
   else if (sourceAddress == 9  && destAddress == 2) {secuencia0902++;  rfg->setSecuencia(secuencia0902);}
   else if (sourceAddress == 10 && destAddress == 2) {secuencia1002++;  rfg->setSecuencia(secuencia1002);}
   else if (sourceAddress == 11 && destAddress == 2) {secuencia1102++;  rfg->setSecuencia(secuencia1102);}
   else if (sourceAddress == 12 && destAddress == 2) {secuencia1202++;  rfg->setSecuencia(secuencia1202);}
   else if (sourceAddress == 13 && destAddress == 2) {secuencia1302++;  rfg->setSecuencia(secuencia1302);}
   else if (sourceAddress == 14 && destAddress == 2) {secuencia1402++;  rfg->setSecuencia(secuencia1402);}

   if      (sourceAddress == 1  && destAddress == 3) {secuencia0103++;  rfg->setSecuencia(secuencia0103);}
   else if (sourceAddress == 2  && destAddress == 3) {secuencia0203++;  rfg->setSecuencia(secuencia0203);}
   else if (sourceAddress == 3  && destAddress == 3) {}
   else if (sourceAddress == 4  && destAddress == 3) {secuencia0403++;  rfg->setSecuencia(secuencia0403);}
   else if (sourceAddress == 5  && destAddress == 3) {secuencia0503++;  rfg->setSecuencia(secuencia0503);}
   else if (sourceAddress == 6  && destAddress == 3) {secuencia0603++;  rfg->setSecuencia(secuencia0603);}
   else if (sourceAddress == 7  && destAddress == 3) {secuencia0703++;  rfg->setSecuencia(secuencia0703);}
   else if (sourceAddress == 8  && destAddress == 3) {secuencia0803++;  rfg->setSecuencia(secuencia0803);}
   else if (sourceAddress == 9  && destAddress == 3) {secuencia0903++;  rfg->setSecuencia(secuencia0903);}
   else if (sourceAddress == 10 && destAddress == 3) {secuencia1003++;  rfg->setSecuencia(secuencia1003);}
   else if (sourceAddress == 11 && destAddress == 3) {secuencia1103++;  rfg->setSecuencia(secuencia1103);}
   else if (sourceAddress == 12 && destAddress == 3) {secuencia1203++;  rfg->setSecuencia(secuencia1203);}
   else if (sourceAddress == 13 && destAddress == 3) {secuencia1303++;  rfg->setSecuencia(secuencia1303);}
   else if (sourceAddress == 14 && destAddress == 3) {secuencia1403++;  rfg->setSecuencia(secuencia1403);}

   if      (sourceAddress == 1  && destAddress == 4) {secuencia0104++;  rfg->setSecuencia(secuencia0104);}
   else if (sourceAddress == 2  && destAddress == 4) {secuencia0204++;  rfg->setSecuencia(secuencia0204);}
   else if (sourceAddress == 3  && destAddress == 4) {secuencia0304++;  rfg->setSecuencia(secuencia0304);}
   else if (sourceAddress == 4  && destAddress == 4) {}
   else if (sourceAddress == 5  && destAddress == 4) {secuencia0504++;  rfg->setSecuencia(secuencia0504);}
   else if (sourceAddress == 6  && destAddress == 4) {secuencia0604++;  rfg->setSecuencia(secuencia0604);}
   else if (sourceAddress == 7  && destAddress == 4) {secuencia0704++;  rfg->setSecuencia(secuencia0704);}
   else if (sourceAddress == 8  && destAddress == 4) {secuencia0804++;  rfg->setSecuencia(secuencia0804);}
   else if (sourceAddress == 9  && destAddress == 4) {secuencia0904++;  rfg->setSecuencia(secuencia0904);}
   else if (sourceAddress == 10 && destAddress == 4) {secuencia1004++;  rfg->setSecuencia(secuencia1004);}
   else if (sourceAddress == 11 && destAddress == 4) {secuencia1104++;  rfg->setSecuencia(secuencia1104);}
   else if (sourceAddress == 12 && destAddress == 4) {secuencia1204++;  rfg->setSecuencia(secuencia1204);}
   else if (sourceAddress == 13 && destAddress == 4) {secuencia1304++;  rfg->setSecuencia(secuencia1304);}
   else if (sourceAddress == 14 && destAddress == 4) {secuencia1404++;  rfg->setSecuencia(secuencia1404);}

   if      (sourceAddress == 1  && destAddress == 5) {secuencia0105++;  rfg->setSecuencia(secuencia0105);}
   else if (sourceAddress == 2  && destAddress == 5) {secuencia0205++;  rfg->setSecuencia(secuencia0205);}
   else if (sourceAddress == 3  && destAddress == 5) {secuencia0305++;  rfg->setSecuencia(secuencia0305);}
   else if (sourceAddress == 4  && destAddress == 5) {secuencia0405++;  rfg->setSecuencia(secuencia0405);}
   else if (sourceAddress == 5  && destAddress == 5) {}
   else if (sourceAddress == 6  && destAddress == 5) {secuencia0605++;  rfg->setSecuencia(secuencia0605);}
   else if (sourceAddress == 7  && destAddress == 5) {secuencia0705++;  rfg->setSecuencia(secuencia0705);}
   else if (sourceAddress == 8  && destAddress == 5) {secuencia0805++;  rfg->setSecuencia(secuencia0805);}
   else if (sourceAddress == 9  && destAddress == 5) {secuencia0905++;  rfg->setSecuencia(secuencia0905);}
   else if (sourceAddress == 10 && destAddress == 5) {secuencia1005++;  rfg->setSecuencia(secuencia1005);}
   else if (sourceAddress == 11 && destAddress == 5) {secuencia1105++;  rfg->setSecuencia(secuencia1105);}
   else if (sourceAddress == 12 && destAddress == 5) {secuencia1205++;  rfg->setSecuencia(secuencia1205);}
   else if (sourceAddress == 13 && destAddress == 5) {secuencia1305++;  rfg->setSecuencia(secuencia1305);}
   else if (sourceAddress == 14 && destAddress == 5) {secuencia1405++;  rfg->setSecuencia(secuencia1405);}

   if      (sourceAddress == 1  && destAddress == 6) {secuencia0106++;  rfg->setSecuencia(secuencia0106);}
   else if (sourceAddress == 2  && destAddress == 6) {secuencia0206++;  rfg->setSecuencia(secuencia0206);}
   else if (sourceAddress == 3  && destAddress == 6) {secuencia0306++;  rfg->setSecuencia(secuencia0306);}
   else if (sourceAddress == 4  && destAddress == 6) {secuencia0406++;  rfg->setSecuencia(secuencia0406);}
   else if (sourceAddress == 5  && destAddress == 6) {secuencia0506++;  rfg->setSecuencia(secuencia0506);}
   else if (sourceAddress == 6  && destAddress == 6) {}
   else if (sourceAddress == 7  && destAddress == 6) {secuencia0706++;  rfg->setSecuencia(secuencia0706);}
   else if (sourceAddress == 8  && destAddress == 6) {secuencia0806++;  rfg->setSecuencia(secuencia0806);}
   else if (sourceAddress == 9  && destAddress == 6) {secuencia0906++;  rfg->setSecuencia(secuencia0906);}
   else if (sourceAddress == 10 && destAddress == 6) {secuencia1006++;  rfg->setSecuencia(secuencia1006);}
   else if (sourceAddress == 11 && destAddress == 6) {secuencia1106++;  rfg->setSecuencia(secuencia1106);}
   else if (sourceAddress == 12 && destAddress == 6) {secuencia1206++;  rfg->setSecuencia(secuencia1206);}
   else if (sourceAddress == 13 && destAddress == 6) {secuencia1306++;  rfg->setSecuencia(secuencia1306);}
   else if (sourceAddress == 14 && destAddress == 6) {secuencia1406++;  rfg->setSecuencia(secuencia1406);}

   if      (sourceAddress == 1  && destAddress == 7) {secuencia0107++;  rfg->setSecuencia(secuencia0107);}
   else if (sourceAddress == 2  && destAddress == 7) {secuencia0207++;  rfg->setSecuencia(secuencia0207);}
   else if (sourceAddress == 3  && destAddress == 7) {secuencia0307++;  rfg->setSecuencia(secuencia0307);}
   else if (sourceAddress == 4  && destAddress == 7) {secuencia0407++;  rfg->setSecuencia(secuencia0407);}
   else if (sourceAddress == 5  && destAddress == 7) {secuencia0507++;  rfg->setSecuencia(secuencia0507);}
   else if (sourceAddress == 6  && destAddress == 7) {secuencia0607++;  rfg->setSecuencia(secuencia0607);}
   else if (sourceAddress == 7  && destAddress == 7) {}
   else if (sourceAddress == 8  && destAddress == 7) {secuencia0807++;  rfg->setSecuencia(secuencia0807);}
   else if (sourceAddress == 9  && destAddress == 7) {secuencia0907++;  rfg->setSecuencia(secuencia0907);}
   else if (sourceAddress == 10 && destAddress == 7) {secuencia1007++;  rfg->setSecuencia(secuencia1007);}
   else if (sourceAddress == 11 && destAddress == 7) {secuencia1107++;  rfg->setSecuencia(secuencia1107);}
   else if (sourceAddress == 12 && destAddress == 7) {secuencia1207++;  rfg->setSecuencia(secuencia1207);}
   else if (sourceAddress == 13 && destAddress == 7) {secuencia1307++;  rfg->setSecuencia(secuencia1307);}
   else if (sourceAddress == 14 && destAddress == 7) {secuencia1407++;  rfg->setSecuencia(secuencia1407);}

   if      (sourceAddress == 1  && destAddress == 8) {secuencia0108++;  rfg->setSecuencia(secuencia0108);}
   else if (sourceAddress == 2  && destAddress == 8) {secuencia0208++;  rfg->setSecuencia(secuencia0208);}
   else if (sourceAddress == 3  && destAddress == 8) {secuencia0308++;  rfg->setSecuencia(secuencia0308);}
   else if (sourceAddress == 4  && destAddress == 8) {secuencia0408++;  rfg->setSecuencia(secuencia0408);}
   else if (sourceAddress == 5  && destAddress == 8) {secuencia0508++;  rfg->setSecuencia(secuencia0508);}
   else if (sourceAddress == 6  && destAddress == 8) {secuencia0608++;  rfg->setSecuencia(secuencia0608);}
   else if (sourceAddress == 7  && destAddress == 8) {secuencia0708++;  rfg->setSecuencia(secuencia0708);}
   else if (sourceAddress == 8  && destAddress == 8) {}
   else if (sourceAddress == 9  && destAddress == 8) {secuencia0908++;  rfg->setSecuencia(secuencia0908);}
   else if (sourceAddress == 10 && destAddress == 8) {secuencia1008++;  rfg->setSecuencia(secuencia1008);}
   else if (sourceAddress == 11 && destAddress == 8) {secuencia1108++;  rfg->setSecuencia(secuencia1108);}
   else if (sourceAddress == 12 && destAddress == 8) {secuencia1208++;  rfg->setSecuencia(secuencia1208);}
   else if (sourceAddress == 13 && destAddress == 8) {secuencia1308++;  rfg->setSecuencia(secuencia1308);}
   else if (sourceAddress == 14 && destAddress == 8) {secuencia1408++;  rfg->setSecuencia(secuencia1408);}

   if      (sourceAddress == 1  && destAddress == 9) {secuencia0109++;  rfg->setSecuencia(secuencia0109);}
   else if (sourceAddress == 2  && destAddress == 9) {secuencia0209++;  rfg->setSecuencia(secuencia0209);}
   else if (sourceAddress == 3  && destAddress == 9) {secuencia0309++;  rfg->setSecuencia(secuencia0309);}
   else if (sourceAddress == 4  && destAddress == 9) {secuencia0409++;  rfg->setSecuencia(secuencia0409);}
   else if (sourceAddress == 5  && destAddress == 9) {secuencia0509++;  rfg->setSecuencia(secuencia0509);}
   else if (sourceAddress == 6  && destAddress == 9) {secuencia0609++;  rfg->setSecuencia(secuencia0609);}
   else if (sourceAddress == 7  && destAddress == 9) {secuencia0709++;  rfg->setSecuencia(secuencia0709);}
   else if (sourceAddress == 8  && destAddress == 9) {secuencia0809++;  rfg->setSecuencia(secuencia0809);}
   else if (sourceAddress == 9  && destAddress == 9) {}
   else if (sourceAddress == 10 && destAddress == 9) {secuencia1009++;  rfg->setSecuencia(secuencia1009);}
   else if (sourceAddress == 11 && destAddress == 9) {secuencia1109++;  rfg->setSecuencia(secuencia1109);}
   else if (sourceAddress == 12 && destAddress == 9) {secuencia1209++;  rfg->setSecuencia(secuencia1209);}
   else if (sourceAddress == 13 && destAddress == 9) {secuencia1309++;  rfg->setSecuencia(secuencia1309);}
   else if (sourceAddress == 14 && destAddress == 9) {secuencia1409++;  rfg->setSecuencia(secuencia1409);}

   if      (sourceAddress == 1  && destAddress == 10) {secuencia0110++;  rfg->setSecuencia(secuencia0110);}
   else if (sourceAddress == 2  && destAddress == 10) {secuencia0210++;  rfg->setSecuencia(secuencia0210);}
   else if (sourceAddress == 3  && destAddress == 10) {secuencia0310++;  rfg->setSecuencia(secuencia0310);}
   else if (sourceAddress == 4  && destAddress == 10) {secuencia0410++;  rfg->setSecuencia(secuencia0410);}
   else if (sourceAddress == 5  && destAddress == 10) {secuencia0510++;  rfg->setSecuencia(secuencia0510);}
   else if (sourceAddress == 6  && destAddress == 10) {secuencia0610++;  rfg->setSecuencia(secuencia0610);}
   else if (sourceAddress == 7  && destAddress == 10) {secuencia0710++;  rfg->setSecuencia(secuencia0710);}
   else if (sourceAddress == 8  && destAddress == 10) {secuencia0810++;  rfg->setSecuencia(secuencia0810);}
   else if (sourceAddress == 9  && destAddress == 10) {secuencia0910++;  rfg->setSecuencia(secuencia0910);}
   else if (sourceAddress == 10 && destAddress == 10) {}
   else if (sourceAddress == 11 && destAddress == 10) {secuencia1110++;  rfg->setSecuencia(secuencia1110);}
   else if (sourceAddress == 12 && destAddress == 10) {secuencia1210++;  rfg->setSecuencia(secuencia1210);}
   else if (sourceAddress == 13 && destAddress == 10) {secuencia1310++;  rfg->setSecuencia(secuencia1310);}
   else if (sourceAddress == 14 && destAddress == 10) {secuencia1410++;  rfg->setSecuencia(secuencia1410);}

   if      (sourceAddress == 1  && destAddress == 11) {secuencia0111++;  rfg->setSecuencia(secuencia0111);}
   else if (sourceAddress == 2  && destAddress == 11) {secuencia0211++;  rfg->setSecuencia(secuencia0211);}
   else if (sourceAddress == 3  && destAddress == 11) {secuencia0311++;  rfg->setSecuencia(secuencia0311);}
   else if (sourceAddress == 4  && destAddress == 11) {secuencia0411++;  rfg->setSecuencia(secuencia0411);}
   else if (sourceAddress == 5  && destAddress == 11) {secuencia0511++;  rfg->setSecuencia(secuencia0511);}
   else if (sourceAddress == 6  && destAddress == 11) {secuencia0611++;  rfg->setSecuencia(secuencia0611);}
   else if (sourceAddress == 7  && destAddress == 11) {secuencia0711++;  rfg->setSecuencia(secuencia0711);}
   else if (sourceAddress == 8  && destAddress == 11) {secuencia0811++;  rfg->setSecuencia(secuencia0811);}
   else if (sourceAddress == 9  && destAddress == 11) {secuencia0911++;  rfg->setSecuencia(secuencia0911);}
   else if (sourceAddress == 10 && destAddress == 11) {secuencia1011++;  rfg->setSecuencia(secuencia1011);}
   else if (sourceAddress == 11 && destAddress == 11) {}
   else if (sourceAddress == 12 && destAddress == 11) {secuencia1211++;  rfg->setSecuencia(secuencia1211);}
   else if (sourceAddress == 13 && destAddress == 11) {secuencia1311++;  rfg->setSecuencia(secuencia1311);}
   else if (sourceAddress == 14 && destAddress == 11) {secuencia1411++;  rfg->setSecuencia(secuencia1411);}

   if      (sourceAddress == 1  && destAddress == 12) {secuencia0112++;  rfg->setSecuencia(secuencia0112);}
   else if (sourceAddress == 2  && destAddress == 12) {secuencia0212++;  rfg->setSecuencia(secuencia0212);}
   else if (sourceAddress == 3  && destAddress == 12) {secuencia0312++;  rfg->setSecuencia(secuencia0312);}
   else if (sourceAddress == 4  && destAddress == 12) {secuencia0412++;  rfg->setSecuencia(secuencia0412);}
   else if (sourceAddress == 5  && destAddress == 12) {secuencia0512++;  rfg->setSecuencia(secuencia0512);}
   else if (sourceAddress == 6  && destAddress == 12) {secuencia0612++;  rfg->setSecuencia(secuencia0612);}
   else if (sourceAddress == 7  && destAddress == 12) {secuencia0712++;  rfg->setSecuencia(secuencia0712);}
   else if (sourceAddress == 8  && destAddress == 12) {secuencia0812++;  rfg->setSecuencia(secuencia0812);}
   else if (sourceAddress == 9  && destAddress == 12) {secuencia0912++;  rfg->setSecuencia(secuencia0912);}
   else if (sourceAddress == 10 && destAddress == 12) {secuencia1012++;  rfg->setSecuencia(secuencia1012);}
   else if (sourceAddress == 11 && destAddress == 12) {secuencia1112++;  rfg->setSecuencia(secuencia1112);}
   else if (sourceAddress == 12 && destAddress == 12) {}
   else if (sourceAddress == 13 && destAddress == 12) {secuencia1312++;  rfg->setSecuencia(secuencia1312);}
   else if (sourceAddress == 14 && destAddress == 12) {secuencia1412++;  rfg->setSecuencia(secuencia1412);}

   if      (sourceAddress == 1  && destAddress == 13) {secuencia0113++;  rfg->setSecuencia(secuencia0113);}
   else if (sourceAddress == 2  && destAddress == 13) {secuencia0213++;  rfg->setSecuencia(secuencia0213);}
   else if (sourceAddress == 3  && destAddress == 13) {secuencia0313++;  rfg->setSecuencia(secuencia0313);}
   else if (sourceAddress == 4  && destAddress == 13) {secuencia0413++;  rfg->setSecuencia(secuencia0413);}
   else if (sourceAddress == 5  && destAddress == 13) {secuencia0513++;  rfg->setSecuencia(secuencia0513);}
   else if (sourceAddress == 6  && destAddress == 13) {secuencia0613++;  rfg->setSecuencia(secuencia0613);}
   else if (sourceAddress == 7  && destAddress == 13) {secuencia0713++;  rfg->setSecuencia(secuencia0713);}
   else if (sourceAddress == 8  && destAddress == 13) {secuencia0813++;  rfg->setSecuencia(secuencia0813);}
   else if (sourceAddress == 9  && destAddress == 13) {secuencia0913++;  rfg->setSecuencia(secuencia0913);}
   else if (sourceAddress == 10 && destAddress == 13) {secuencia1013++;  rfg->setSecuencia(secuencia1013);}
   else if (sourceAddress == 11 && destAddress == 13) {secuencia1113++;  rfg->setSecuencia(secuencia1113);}
   else if (sourceAddress == 12 && destAddress == 13) {secuencia1213++;  rfg->setSecuencia(secuencia1213);}
   else if (sourceAddress == 13 && destAddress == 13) {}
   else if (sourceAddress == 14 && destAddress == 13) {secuencia1413++;  rfg->setSecuencia(secuencia1413);}

   if      (sourceAddress == 1  && destAddress == 14) {secuencia0114++;  rfg->setSecuencia(secuencia0114);}
   else if (sourceAddress == 2  && destAddress == 14) {secuencia0214++;  rfg->setSecuencia(secuencia0214);}
   else if (sourceAddress == 3  && destAddress == 14) {secuencia0314++;  rfg->setSecuencia(secuencia0314);}
   else if (sourceAddress == 4  && destAddress == 14) {secuencia0414++;  rfg->setSecuencia(secuencia0414);}
   else if (sourceAddress == 5  && destAddress == 14) {secuencia0514++;  rfg->setSecuencia(secuencia0514);}
   else if (sourceAddress == 6  && destAddress == 14) {secuencia0614++;  rfg->setSecuencia(secuencia0614);}
   else if (sourceAddress == 7  && destAddress == 14) {secuencia0714++;  rfg->setSecuencia(secuencia0714);}
   else if (sourceAddress == 8  && destAddress == 14) {secuencia0814++;  rfg->setSecuencia(secuencia0814);}
   else if (sourceAddress == 9  && destAddress == 14) {secuencia0914++;  rfg->setSecuencia(secuencia0914);}
   else if (sourceAddress == 10 && destAddress == 14) {secuencia1014++;  rfg->setSecuencia(secuencia1014);}
   else if (sourceAddress == 11 && destAddress == 14) {secuencia1114++;  rfg->setSecuencia(secuencia1114);}
   else if (sourceAddress == 12 && destAddress == 14) {secuencia1214++;  rfg->setSecuencia(secuencia1214);}
   else if (sourceAddress == 13 && destAddress == 14) {secuencia1314++;  rfg->setSecuencia(secuencia1314);}
   else if (sourceAddress == 14 && destAddress == 14) {}

    //**********************************************

   if      (sourceAddress == 1  && destAddress == 1)  {secuencia0101++; rfg->setSecuencia(secuencia0101);}
   else if (sourceAddress == 2  && destAddress == 2)  {secuencia0202++; rfg->setSecuencia(secuencia0202);}
   else if (sourceAddress == 3  && destAddress == 3)  {secuencia0303++; rfg->setSecuencia(secuencia0303);}
   else if (sourceAddress == 4  && destAddress == 4)  {secuencia0404++; rfg->setSecuencia(secuencia0404);}
   else if (sourceAddress == 5  && destAddress == 5)  {secuencia0505++; rfg->setSecuencia(secuencia0505);}
   else if (sourceAddress == 6  && destAddress == 6)  {secuencia0606++; rfg->setSecuencia(secuencia0606);}
   else if (sourceAddress == 7  && destAddress == 7)  {secuencia0707++; rfg->setSecuencia(secuencia0707);}
   else if (sourceAddress == 8  && destAddress == 8)  {secuencia0808++; rfg->setSecuencia(secuencia0808);}
   else if (sourceAddress == 9  && destAddress == 9)  {secuencia0909++; rfg->setSecuencia(secuencia0909);}
   else if (sourceAddress == 10 && destAddress == 10) {secuencia1010++; rfg->setSecuencia(secuencia1010);}
   else if (sourceAddress == 11 && destAddress == 11) {secuencia1111++; rfg->setSecuencia(secuencia1111);}
   else if (sourceAddress == 12 && destAddress == 12) {secuencia1212++; rfg->setSecuencia(secuencia1212);}
   else if (sourceAddress == 13 && destAddress == 13) {secuencia1313++; rfg->setSecuencia(secuencia1313);}
   else if (sourceAddress == 14 && destAddress == 14) {secuencia1414++; rfg->setSecuencia(secuencia1414);}

    //**********************************************


    burstSender_Core01XX = secuencia0101 +secuencia0102 +secuencia0103 +secuencia0104 +secuencia0105 +secuencia0106 +secuencia0107 +secuencia0108 +secuencia0109 +secuencia0110 +secuencia0111 +secuencia0112 +secuencia0113 +secuencia0114;
    burstSender_Core02XX = secuencia0201 +secuencia0202 +secuencia0203 +secuencia0204 +secuencia0205 +secuencia0206 +secuencia0207 +secuencia0208 +secuencia0209 +secuencia0210 +secuencia0211 +secuencia0212 +secuencia0213 +secuencia0214;
    burstSender_Core03XX = secuencia0301 +secuencia0302 +secuencia0303 +secuencia0304 +secuencia0305 +secuencia0306 +secuencia0307 +secuencia0308 +secuencia0309 +secuencia0310 +secuencia0311 +secuencia0312 +secuencia0313 +secuencia0314;
    burstSender_Core04XX = secuencia0401 +secuencia0402 +secuencia0403 +secuencia0404 +secuencia0405 +secuencia0406 +secuencia0407 +secuencia0408 +secuencia0409 +secuencia0410 +secuencia0411 +secuencia0412 +secuencia0413 +secuencia0414;
    burstSender_Core05XX = secuencia0501 +secuencia0502 +secuencia0503 +secuencia0504 +secuencia0505 +secuencia0506 +secuencia0507 +secuencia0508 +secuencia0509 +secuencia0510 +secuencia0511 +secuencia0512 +secuencia0513 +secuencia0514;
    burstSender_Core06XX = secuencia0601 +secuencia0602 +secuencia0603 +secuencia0604 +secuencia0605 +secuencia0606 +secuencia0607 +secuencia0608 +secuencia0609 +secuencia0610 +secuencia0611 +secuencia0612 +secuencia0613 +secuencia0614;
    burstSender_Core07XX = secuencia0701 +secuencia0702 +secuencia0703 +secuencia0704 +secuencia0705 +secuencia0706 +secuencia0707 +secuencia0708 +secuencia0709 +secuencia0710 +secuencia0711 +secuencia0712 +secuencia0713 +secuencia0714;
    burstSender_Core08XX = secuencia0801 +secuencia0802 +secuencia0803 +secuencia0804 +secuencia0805 +secuencia0806 +secuencia0807 +secuencia0808 +secuencia0809 +secuencia0810 +secuencia0811 +secuencia0812 +secuencia0813 +secuencia0814;
    burstSender_Core09XX = secuencia0901 +secuencia0902 +secuencia0903 +secuencia0904 +secuencia0905 +secuencia0906 +secuencia0907 +secuencia0908 +secuencia0909 +secuencia0910 +secuencia0911 +secuencia0912 +secuencia0913 +secuencia0914;
    burstSender_Core10XX = secuencia1001 +secuencia1002 +secuencia1003 +secuencia1004 +secuencia1005 +secuencia1006 +secuencia1007 +secuencia1008 +secuencia1009 +secuencia1010 +secuencia1011 +secuencia1012 +secuencia1013 +secuencia1014;
    burstSender_Core11XX = secuencia1101 +secuencia1102 +secuencia1103 +secuencia1104 +secuencia1105 +secuencia1106 +secuencia1107 +secuencia1108 +secuencia1109 +secuencia1110 +secuencia1111 +secuencia1112 +secuencia1113 +secuencia1114;
    burstSender_Core12XX = secuencia1201 +secuencia1202 +secuencia1203 +secuencia1204 +secuencia1205 +secuencia1206 +secuencia1207 +secuencia1208 +secuencia1209 +secuencia1210 +secuencia1211 +secuencia1212 +secuencia1213 +secuencia1214;
    burstSender_Core13XX = secuencia1301 +secuencia1302 +secuencia1303 +secuencia1304 +secuencia1305 +secuencia1306 +secuencia1307 +secuencia1308 +secuencia1309 +secuencia1310 +secuencia1311 +secuencia1312 +secuencia1313 +secuencia1314;
    burstSender_Core14XX = secuencia1401 +secuencia1402 +secuencia1403 +secuencia1404 +secuencia1405 +secuencia1406 +secuencia1407 +secuencia1408 +secuencia1409 +secuencia1410 +secuencia1411 +secuencia1412 +secuencia1413 +secuencia1414;


    burstGeneratedXX01 = secuencia0201 + secuencia0301 + secuencia0401 + secuencia0501 + secuencia0601 + secuencia0701 + secuencia0801 + secuencia0901 + secuencia1001 + secuencia1101 + secuencia1201 + secuencia1301 + secuencia1401;
    burstGeneratedXX02 = secuencia0102 + secuencia0302 + secuencia0402 + secuencia0502 + secuencia0602 + secuencia0702 + secuencia0802 + secuencia0902 + secuencia1002 + secuencia1102 + secuencia1202 + secuencia1302 + secuencia1402;
    burstGeneratedXX03 = secuencia0103 + secuencia0203 + secuencia0403 + secuencia0503 + secuencia0603 + secuencia0703 + secuencia0803 + secuencia0903 + secuencia1003 + secuencia1103 + secuencia1203 + secuencia1303 + secuencia1403;
    burstGeneratedXX04 = secuencia0104 + secuencia0204 + secuencia0304 + secuencia0504 + secuencia0604 + secuencia0704 + secuencia0804 + secuencia0904 + secuencia1004 + secuencia1104 + secuencia1204 + secuencia1304 + secuencia1404;
    burstGeneratedXX05 = secuencia0105 + secuencia0205 + secuencia0305 + secuencia0405 + secuencia0605 + secuencia0705 + secuencia0805 + secuencia0905 + secuencia1005 + secuencia1105 + secuencia1205 + secuencia1305 + secuencia1405;
    burstGeneratedXX06 = secuencia0106 + secuencia0206 + secuencia0306 + secuencia0406 + secuencia0506 + secuencia0706 + secuencia0806 + secuencia0906 + secuencia1006 + secuencia1106 + secuencia1206 + secuencia1306 + secuencia1406;
    burstGeneratedXX07 = secuencia0107 + secuencia0207 + secuencia0307 + secuencia0407 + secuencia0507 + secuencia0607 + secuencia0807 + secuencia0907 + secuencia1007 + secuencia1107 + secuencia1207 + secuencia1307 + secuencia1407;
    burstGeneratedXX08 = secuencia0108 + secuencia0208 + secuencia0308 + secuencia0408 + secuencia0508 + secuencia0608 + secuencia0708 + secuencia0908 + secuencia1008 + secuencia1108 + secuencia1208 + secuencia1308 + secuencia1408;
    burstGeneratedXX09 = secuencia0109 + secuencia0209 + secuencia0309 + secuencia0409 + secuencia0509 + secuencia0609 + secuencia0709 + secuencia0809 + secuencia1009 + secuencia1109 + secuencia1209 + secuencia1309 + secuencia1409;
    burstGeneratedXX10 = secuencia0110 + secuencia0210 + secuencia0310 + secuencia0410 + secuencia0510 + secuencia0610 + secuencia0710 + secuencia0810 + secuencia0910 + secuencia1110 + secuencia1210 + secuencia1310 + secuencia1410;
    burstGeneratedXX11 = secuencia0111 + secuencia0211 + secuencia0311 + secuencia0411 + secuencia0511 + secuencia0611 + secuencia0711 + secuencia0811 + secuencia0911 + secuencia1011 + secuencia1211 + secuencia1311 + secuencia1411;
    burstGeneratedXX12 = secuencia0112 + secuencia0212 + secuencia0312 + secuencia0412 + secuencia0512 + secuencia0612 + secuencia0712 + secuencia0812 + secuencia0912 + secuencia1012 + secuencia1112 + secuencia1312 + secuencia1412;
    burstGeneratedXX13 = secuencia0113 + secuencia0213 + secuencia0313 + secuencia0413 + secuencia0513 + secuencia0613 + secuencia0713 + secuencia0813 + secuencia0913 + secuencia1013 + secuencia1113 + secuencia1213 + secuencia1413;
    burstGeneratedXX14 = secuencia0114 + secuencia0214 + secuencia0314 + secuencia0414 + secuencia0514 + secuencia0614 + secuencia0714 + secuencia0814 + secuencia0914 + secuencia1014 + secuencia1114 + secuencia1214 + secuencia1314;

    burstGenerated0101 = secuencia0101; burstGenerated0202 = secuencia0202; burstGenerated0303 = secuencia0303; burstGenerated0404 = secuencia0404;
    burstGenerated0505 = secuencia0505; burstGenerated0606 = secuencia0606; burstGenerated0707 = secuencia0707; burstGenerated0808 = secuencia0808; burstGenerated0909 = secuencia0909;
    burstGenerated1010 = secuencia1010; burstGenerated1111 = secuencia1111; burstGenerated1212 = secuencia1212; burstGenerated1313 = secuencia1313; burstGenerated1414 = secuencia1414;

    //*****-----------------------------------------------



    int wl = 0;
    int pos=0;

    wl=findNearestHorizon(); //retorna la posición del horizonte más apto para enviar la ráfaga actual

    char pkname[40];
    sprintf(pkname,"----Wavelengt--%d",wl);
    EV << "info" << pkname << endl;

    //Inserta el id de la ráfaga
    rfg->setSendId(getId()); //retorna el identificador del módulo

    BurstSenderInfo *myInfo = new BurstSenderInfo();

    myInfo->setIdBurstifier(rfg->getIdBurstifier()); //retorna el índice del vector correspondiente al módulo
    myInfo->setNumSeq(rfg->getSecNum());             //Contador de ráfagas...burstCounter este sec num sirve cuando los paquetes o ráfagas llegan desordenados, con este indicador, se puede ordenar cuando lleguen al receptor
    myInfo->setAssignedLambda(wl);

    BurstifierInfo *lInfo = (BurstifierInfo*) rfg->removeControlInfo();
    myInfo->setLabel(lInfo->getLabel()); //se define en el .ini una etiqueta de destino para cada burstifier
    delete lInfo;

    //Crea el automensaje "schedule the bcp_ini send"
    cMessage *ctrMsg= new cMessage("Sched");


    //Entra aquí si la ráfaga puede ser enviada solo cuando el canal wl se establezca como libre. (habrá mucho tiempo para enviar el bcp y esperar el tiempo de offset máximo)
    if(horizon[wl] - rfg->getMaxOffset() >= simTime()) //el = Significa que se puede programar una ráfaga al mismo tiempo que el valor del horizonte
      {
       //Se almacena en ScheduledBurst
       pos = scheduleBursts.insertBurst(rfg, horizon[wl]);

       if(pos == -1)
       { //scheduledBurst está lleno. Se decarta esta ráfaga
         delete msg;
         delete ctrMsg;
         burstDroppedByQueue++;
         return;
       }

     //Inserta la posición de la ráfaga en la cola de scheduledBurst
     myInfo->setBurstId(pos);

     //Se llenan los campos de control(este mensaje viajará a través de todos los estados del sender)
     ctrMsg->setControlInfo(myInfo);
     ctrMsg->setKind(OBS_PROGRAMAR_BCP); //Se Establece en el paso 1: Schedule BCP

     //Programar envío de BCP
     scheduleAt(horizon[wl] - rfg->getMaxOffset(), ctrMsg);

     //Actualizar el valor del horizonte
     horizon[wl] = horizon[wl] + (rfg->getBitLength()/dataRate) + guardTime;

     //Se Registra el valor del horizonte
     horizonVec[wl]->record(horizon[wl]);
     }


    else //Se puede mandar el BCP inmediatamente de esta forma la ráfaga será enviada dentro del offset máximo
     {
      //Se almacena en ScheduledBurst
      pos = scheduleBursts.insertBurst(rfg, simTime() + rfg->getMaxOffset());
      char name[40];
      sprintf(name, "--pos %d", pos);
      EV<< "info"<<name<< endl;

      if(pos == -1)
        { // la cola de ScheduleBursts queue está llena. Descartar
         delete msg;
         delete ctrMsg;
         burstDroppedByQueue++;
         return;
        }

      //Insertar la posición de la ráfaga en la cola scheduledBurst
      myInfo->setBurstId(pos);

      // LLenar los campos del mensaje de control(Este mensaje pasará a traves de todos los estados del sender)
      ctrMsg->setControlInfo(myInfo);
      ctrMsg->setKind(OBS_PROGRAMAR_BCP);

      //Programar envío de BCP en este momento
      scheduleAt(simTime(), ctrMsg);

      //Actualizar el valor del horizonte
      horizon[wl] = simTime() + rfg->getMaxOffset() + (rfg->getBitLength()/dataRate) + guardTime;

      //Registrar el valor del horizonte
      horizonVec[wl]->record(horizon[wl]);
      }
     }


    else
    {
     /*  Sección de automensajes. la clase de mensajes determinará en cuál sesión entrar  */

     if(msg->getKind() == OBS_PROGRAMAR_BCP)//Primer paso: Enviar el mensaje de inicio del BCP y programar el mensaje final del BCP.  ***-->BCP
       {
       //Se extrae la información de control del mensaje de control recibido
       info = check_and_cast<BurstSenderInfo *>(msg->getControlInfo());

       //Si la ráfaga no se puede enviar sobre el mínimo offset, descartarla
       if((simTime() + scheduleBursts.retrieveMinOffset(info->getBurstId())) >= scheduleBursts.retrieveSendTime(info->getBurstId()))
        {
        scheduleBursts.removeBurst(info->getBurstId());
        delete msg;

        //Actualizar el contador de ráfagas descartadas
        burstDroppedByOffset++;

        // Ahora se puede escoger un BCP de la cola (si hay alguno disponible) para manarlo
        if(!waitingBCP.empty())
         {//se escoge un BCP y se manda en este instante
          cMessage *bcp_ini = (cMessage*)waitingBCP.pop();
          scheduleAt(simTime(),bcp_ini);
         }

        return;
        }


    // El canal de control se encuentra ocupado transmitiendo otro BCP?  ***-->BCP
    if(control_is_busy)
      {
      //Si es así, colocar el BCP actual en la cola (waitingBCP)
      waitingBCP.insert(msg);
      }


    //============================== #============================== #==============================
    // Primer paso: Enviar el ini del mensaje del BCP  ***-->BCP
    //============================== #============================== #==============================
    else
     {//Si no lo es, tomar el canal de control
      control_is_busy = true;

      //Crear el mensaje BCP
      BurstControlPacket *bcp = new BurstControlPacket("iniBCP");


      //Inicializar todos los campos del BCP
      bcp->setKind(1); //kind 1 = initial BCP
      bcp->setColorBurst(colour[info->getAssignedLambda()]); //wl

      //Incluye tiempo de llegada de la ráfaga relativo: la diferencia entre la llegada de iniBCP e iniBurst
      //Como iniBCP será enviado en ste instate, este tiempo es: sendTime(burst) - current simTime
      bcp->setDeltaArriveBurst(scheduleBursts.retrieveSendTime(info->getBurstId()) - simTime());

      //Llenar todos los campos del BCP
      bcp->setIdBurstifier(info->getIdBurstifier()); //índice o identificador del módulo burstifier al que corresponden
      bcp->setNumSeq(info->getNumSeq()); //Contador de ráfagas
      bcp->setIdSend(getId()); //índice o identificador del módulo, en este caso sender
      bcp->setLabel(info->getLabel()); //se establece en el .ini y es una etiqueta para cada burstifier
      bcp->setBurstSize(scheduleBursts.retrieveBurstSize(info->getBurstId()));
      bcp->setByteLength(BCPSize);
      bcp->setNumSaltos(numSaltos); //se fija el valor de numero de saltos con el contenido de la variable numSaltos


    //============================== #==============================
    // Envio del ini BCP
    //============================== #==============================
    //Enviar el BCP al canal de control(el último)
      send(bcp,"out",numLambdas);


      //Retransmitir el mensaje recibido(ctlMsg = *msg here)
      msg->setKind(OBS_PROGRAMAR_FIN_BCP);

      //Programar el envío de Schedule endBCP
      int BCPSizeInBits = BCPSize*8;
      scheduleAt(simTime()+(BCPSizeInBits/dataRate),msg);
      }
     }



   //============================== #============================== #==============================
   // Segundo paso: Enviar el fin del mensaje del BCP y programar el envío de la ráfaga.  ***-->BCP
   //============================== #============================== #==============================
    else if(msg->getKind() == OBS_PROGRAMAR_FIN_BCP)
     {
      info = check_and_cast<BurstSenderInfo *>(msg->getControlInfo());
      BurstControlPacket *bcp = new BurstControlPacket("endBCP"); //mensaje creado del BCP

      //llenar el mensaje BCP con info
      bcp->setKind(2); //kind 2 = end BCP
      bcp->setIdBurstifier(info->getIdBurstifier());  //índice o identificador del módulo burstifier al que corresponden
      bcp->setNumSeq(info->getNumSeq());              //contador de ráfagas


      //============================== #==============================
      // Envio del end BCP
      //============================== #==============================
      //Envia endBCP al canal de control
      send(bcp,"out",numLambdas);


      //Retransmitir el mensaje recibido (ctlMsg = *msg here)
      msg->setKind(OBS_PROGRAMAR_RAFAGA);

      //Programar envío de BurstIni
      scheduleAt(scheduleBursts.retrieveSendTime(info->getBurstId()),msg);

      control_is_busy = false; //El canal de control está libre ahora...


      //Escoger un BCP si hay alguno disponible
      if(!waitingBCP.empty())
        {
         //Colocar el BCP fuera de la cola y programarlo
         cMessage *bcp_ini = (cMessage*)waitingBCP.pop();
         scheduleAt(simTime(),bcp_ini);
        }
      }



     //============================== #============================== #==============================
     // Tercer paso: Enviar el inicio de la ráfaga óptica  ***-->BURST
     //============================== #============================== #==============================
    else if(msg->getKind() == OBS_PROGRAMAR_RAFAGA)
     {
      info = check_and_cast<BurstSenderInfo *>(msg->getControlInfo());
      Burst *burst= scheduleBursts.retrieveBurst(info->getBurstId());

      //Llenar los campos de la ráfaga
      burst->setName("iniBurst");
      burst->setKind(1);                //kind 1= send burst


    //============================== #==============================
    // Envio del ini Burst
    //============================== #==============================
      send(burst,"out",info->getAssignedLambda());


    //============================== #==============================
    // Actualiza el contador de envíos
    //============================== #==============================
      burstSend++;  burstSendCore++;


    //Retransmitir el mensaje recibido(ctlMsg = *msg here)

      msg->setKind(OBS_PROGRAMAR_FIN_RAFAGA);
    //Se programa el final de la ráfaga
      scheduleAt(simTime()+(burst->getBitLength()/dataRate),msg);
    }



    //============================== #============================== #==============================
    // Cuarto y último paso: Enviar el final de la ráfaga    ***-->BURST
    //============================== #============================== #==============================
    else if(msg->getKind() == OBS_PROGRAMAR_FIN_RAFAGA)
     {
      info = check_and_cast<BurstSenderInfo *>(msg->removeControlInfo());
      Burst *burst = new Burst("endBurst");

      //Se llenan los campos de la ráfaga
      burst->setKind(2);                               //kind 2= end burst
      burst->setIdBurstifier(info->getIdBurstifier()); //índice o identificador del módulo burstifier al que corresponden
      burst->setSecNum(info->getNumSeq());             //contador de ráfagas


      //============================== #==============================
      // Envio del end Burst
      //============================== #==============================
      send(burst,"out",info->getAssignedLambda());


      //Borrar ráfaga de las lista programada
      scheduleBursts.removeBurst(info->getBurstId());

      //Remover la información de control y los mensajes contenedores
      delete msg;
      delete info;
    } }
}



void Sender::finish(){

   recordScalar("Raf.GeneradasSender_alCore", burstSendCore);          recordScalar("Raf.GeneradasEnsamble_alSender", burstRecv);

   recordScalar("Raf.Ensambladas_Core Nodo01XX",burstSender_Core01XX); recordScalar("Raf.Ensambladas_Core Nodo02XX",burstSender_Core02XX); recordScalar("Raf.Ensambladas_Core Nodo03XX",burstSender_Core03XX);
   recordScalar("Raf.Ensambladas_Core Nodo04XX",burstSender_Core04XX); recordScalar("Raf.Ensambladas_Core Nodo05XX",burstSender_Core05XX); recordScalar("Raf.Ensambladas_Core Nodo06XX",burstSender_Core06XX);
   recordScalar("Raf.Ensambladas_Core Nodo07XX",burstSender_Core07XX); recordScalar("Raf.Ensambladas_Core Nodo08XX",burstSender_Core08XX); recordScalar("Raf.Ensambladas_Core Nodo09XX",burstSender_Core09XX);
   recordScalar("Raf.Ensambladas_Core Nodo10XX",burstSender_Core10XX); recordScalar("Raf.Ensambladas_Core Nodo11XX",burstSender_Core11XX); recordScalar("Raf.Ensambladas_Core Nodo12XX",burstSender_Core12XX);
   recordScalar("Raf.Ensambladas_Core Nodo13XX",burstSender_Core13XX); recordScalar("Raf.Ensambladas_Core Nodo14XX",burstSender_Core14XX);

   recordScalar("Raf.Totales Generadas NodoXX01",burstGeneratedXX01); recordScalar("Raf.Totales Generadas NodoXX02",burstGeneratedXX02); recordScalar("Raf.Totales Generadas NodoXX03",burstGeneratedXX03);
   recordScalar("Raf.Totales Generadas NodoXX04",burstGeneratedXX04); recordScalar("Raf.Totales Generadas NodoXX05",burstGeneratedXX05); recordScalar("Raf.Totales Generadas NodoXX06",burstGeneratedXX06);
   recordScalar("Raf.Totales Generadas NodoXX07",burstGeneratedXX07); recordScalar("Raf.Totales Generadas NodoXX08",burstGeneratedXX08); recordScalar("Raf.Totales Generadas NodoXX09",burstGeneratedXX09);
   recordScalar("Raf.Totales Generadas NodoXX10",burstGeneratedXX10); recordScalar("Raf.Totales Generadas NodoXX11",burstGeneratedXX11); recordScalar("Raf.Totales Generadas NodoXX12",burstGeneratedXX12);
   recordScalar("Raf.Totales Generadas NodoXX13",burstGeneratedXX13); recordScalar("Raf.Totales Generadas NodoXX14",burstGeneratedXX14);

   recordScalar("Raf.Totales Generadas Nodo0101",burstGenerated0101); recordScalar("Raf.Totales Generadas Nodo0202",burstGenerated0202); recordScalar("Raf.Totales Generadas Nodo0303",burstGenerated0303);
   recordScalar("Raf.Totales Generadas Nodo0404",burstGenerated0404); recordScalar("Raf.Totales Generadas Nodo0505",burstGenerated0505); recordScalar("Raf.Totales Generadas Nodo0606",burstGenerated0606);
   recordScalar("Raf.Totales Generadas Nodo0707",burstGenerated0707); recordScalar("Raf.Totales Generadas Nodo0808",burstGenerated0808); recordScalar("Raf.Totales Generadas Nodo0909",burstGenerated0909);
   recordScalar("Raf.Totales Generadas Nodo0909",burstGenerated1010); recordScalar("Raf.Totales Generadas Nodo1111",burstGenerated1111); recordScalar("Raf.Totales Generadas Nodo1212",burstGenerated1212);
   recordScalar("Raf.Totales Generadas Nodo1313",burstGenerated1313); recordScalar("Raf.Totales Generadas Nodo1414",burstGenerated1414);

   recordScalar("burst dropped by reaching Minimum Offset",burstDroppedByOffset);
   recordScalar("burst dropped by queue",burstDroppedByQueue);
   recordScalar("BCPs pending to be sent (because the control channel is busy)", waitingBCP.length());

}



int Sender::findNearestHorizon()
{
    int min = 0;
       int i;
       for(i=0;i<numLambdas;i++)
       {
          if(horizon[min] > horizon[i]) //devuelve el menor tiempo que encuentra
             min = i;
       }
       return min;
}



