/**  rand_o.cc  ****************************************************************

    12.31.1999  Performance Server Library v2.000




changes log
when      who       what
8.24.96   Dan       Creation.
5.2.99    Dan       Changed:  Seeds off of the processes's pid now.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include <stdlib.h>
#include "rand_o"
#include "sysinfo_o"

extern sysinfo_o sysinfo;


void* rand_oThreadLoop(void* rand_oThread)  {
    (void)((rand_o*)rand_oThread)->threadLoop();
    (void)((thread_o*)rand_oThread)->exit();
    return  rand_oThread;
}


rand_o::rand_o()  {
    (void)::srand(::sysinfo.pid());
    srandSet = 0;
    recycleNumbers.release();
}

rand_o::~rand_o()  {}


int rand_o::i(int limit)  {

//  return (int)((double)limit*((double)rand()/RAND_MAX));

    if(!srandSet)  {
        srandSet = 1;
        (void)::srand(::sysinfo.pid());
        start(rand_oThreadLoop, this);
    }

    int* rq = randomNumbers.get();
    int r = (int)((double)limit*((double)*rq/RAND_MAX));
    recycleNumbers.put(rq);
    condition.broadcast("rand_o::i()");
    return  r;
}

void rand_o::threadLoop()  {
    while(1)  {
        while(randomNumbers.cardinality() < 8096)  {
            int* rq = recycleNumbers.get();
            if(!rq)  rq = new int();
            *rq = rand();
            randomNumbers.put(rq);
        }
        condition.wait("rand_o");
    }
}



/******************************************************************************/
