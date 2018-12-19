/*
 * Burst.h
 *
 *  Created on: 2/04/2013
 *      Author: Tatiana
 */

#ifndef BURST_H_
#define BURST_H_

#include<list>
#include"Burst_m.h"

using namespace std;

 class Burst : public Burst_Base
  {

    public:
      Burst(const char *name=NULL, int kind=0) : Burst_Base(name,kind) {}
      Burst(const Burst& other) : Burst_Base(other) {operator=(other);}
      Burst& operator=(const Burst& other) {Burst_Base::operator=(other); return *this;}
      ~Burst();
     virtual Burst *dup() const {return new Burst(*this);}
      // ADD CODE HERE to redefine and implement pure virtual functions from Burst_Base

     virtual void insertMessage(cMessage *msg); //!< Inserts a message in the queue.
     virtual cMessage* retrieveMessage(); //!< Retrieves and deletes the first message of the queue. NULL if queue is empty.
     virtual bool hasMessages(); //!< Returns true if queue is not empty. Otherwise, returns false.
  };


#endif /* BURST_H_ */
