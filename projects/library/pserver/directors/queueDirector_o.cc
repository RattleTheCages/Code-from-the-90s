/**  queueDirector_o.cc  *******************************************************

    12.31.1999  Performance Server Library v2.000




changes log
when      who     what
5.1.99    Dan     Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "queueDirector_o.h"


queueDirector_o::queueDirector_o()  {}

queueDirector_o::~queueDirector_o()  {}

queue_o<input_o>* queueDirector_o::inputQueue(int priority)  {
    if(priority < 0 || priority > NumberOfInputQueues)
        return &InputQueue[1];
    return &InputQueue[priority];
}

int queueDirector_o::releaseInputQueues()  {
    int n = 0;
    for(int x=0;x<NumberOfInputQueues;x++)  n += InputQueue[x].release();
    return n;
}

void queueDirector_o::retainInputQueues()  {
    for(int x=0;x<NumberOfInputQueues;x++)  InputQueue[x].retain();
}



/******************************************************************************/
