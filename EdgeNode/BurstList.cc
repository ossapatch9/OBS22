/*
 * BurstList.cc
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana y Adriana
 */


#include "BurstList.h"

BurstList::BurstList()
{
   counter = 0;
   listSize = 0;
   numElems = 0;
   maxSize = 0; //
   maxElems = 0; // Por defecto: deshabilidado
   numElemsVector.setName("burstListSize");
   burstList.setName("scheduledBursts");
}

BurstList::~BurstList()
{
   burstList.clear();
}

//Inserta la ráfaga al final del vector. Retorna la posicion donde la ráfaga se encuentra almacenada.
int BurstList::insertBurst(Burst *burst,simtime_t sendTime){
   if(maxElems != 0){
      if(numElems  == maxElems)
         return -1;
   }
   if(maxSize != 0){
       if(listSize + burst->getBitLength() > maxSize)
          return -1;
   }

      ScheduleBurst *item = new ScheduleBurst();
      item->setIdBurst(counter);
      counter++;
      listSize += burst->getBitLength();
      numElems++;
      numElemsVector.record(numElems);

      item->setMinOffset(burst->getMinOffset());
      item->setMaxOffset(burst->getMaxOffset());
      item->setSendTime(sendTime);
      item->encapsulate(burst);
      item->setListIndex(counter-1);

      burstList.insert(item);
      return counter-1;
      }

void BurstList::removeBurst(int bId)
{

   cQueue::Iterator iter_list(burstList,0);//De adelante hacia atrás
   ScheduleBurst *item;
   Burst *burst;
   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getIdBurst() == bId){
         burst = check_and_cast <Burst *> (item->decapsulate());
         listSize -= burst->getBitLength();
         delete burstList.remove(item);
         delete burst;
         numElems--;
         numElemsVector.record(numElems);
         return;
      }
   }
}

Burst* BurstList::retrieveBurst(int index)
{

   cQueue::Iterator iter_list(burstList,0);//De adelante hacia atrás
   ScheduleBurst *item;

   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getListIndex() == index) break;
   }

   //Crea un mensaje "clon" reemplazando el original por éste.

   Burst *element = check_and_cast<Burst *>(item->decapsulate());
   Burst *clone = element->dup();
   clone->setKind(99);
   item->encapsulate(clone);
   //return clone;
   return element;
}


int BurstList::retrieveBurstSize(int index)
{
   cQueue::Iterator iter_list(burstList,0);//De adelante hacia atrás
   ScheduleBurst *item;

   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getListIndex() == index) break;
   }

   Burst *element = check_and_cast<Burst *>(item->getEncapsulatedPacket());
   return element->getByteLength();

}

simtime_t BurstList::retrieveSendTime(int index)
{
   cQueue::Iterator iter_list(burstList,0);//De adelante hacia atrás
   ScheduleBurst *item;
   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getListIndex() == index) break;
   }

   return item->getSendTime();
}

simtime_t BurstList::retrieveMinOffset(int index)
{
   cQueue::Iterator iter_list(burstList,0);//De adelante hacia atrás
   ScheduleBurst *item;

   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getListIndex() == index) break;
}

   return item->getMinOffset();
}

simtime_t BurstList::retrieveMaxOffset(int index)
{
   cQueue::Iterator iter_list(burstList,0);
   ScheduleBurst *item;

   while(!iter_list.end()){
      item = (ScheduleBurst*)iter_list++;
      if(item->getListIndex() == index) break;
   }

   return item->getMaxOffset();
}

void BurstList::setMaxSize(int size)
{
   maxSize = size;
}

void BurstList::setMaxElems(int numElems)
{
  maxElems = numElems;
}


