/**  queueDirector_o.h  ********************************************************

    12.31.1999  Performance Server Library v2.000


    Queue Director Object.



changes log
when      who     what
4.28.99   Dan     Creation.
5.4.99    Dan     Added:    Method string operator.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef QueueDirectorOBJECT_API
#define QueueDirectorOBJECT_API

#define QueueDirector_MAX_INPUT_QUEUES   256

#include "error_o.h"
#include "queue_o.h"
#include "input_o.h"
#include "output_o.h"


class queueDirector_o: public error_o  {
  private:
    int                 NumberOfInputQueues;
    queue_o<input_o>    InputQueue[QueueDirector_MAX_INPUT_QUEUES];
    queue_o<output_o>   OutputQueue;

  public:
    queueDirector_o();                              // Default constructor.
    queueDirector_o(const queueDirector_o&);        // Copy constuctor.
    virtual  ~queueDirector_o();                    // Default desructor.
    queueDirector_o& operator = (const queueDirector_o&);
                                                    // Assignment operator.


    queue_o<input_o>*   inputQueue(int);        // Return input queue asked
                                                // for by index.
    queue_o<output_o>*  outputQueue();          // Return the output queue.

    int                 releaseInputQueues();   // Release all waiting threads
                                                // on all Request Queues,
                                                // return total number of
                                                // threads released.
    void                retainInputQueues();    // Retain threads on all
                                                // Request Queues.

    int                 numberOfInputQueues() const;
};
string_o& operator << (string_o&, const queueDirector_o&);


/******************************************************************************/

inline int queueDirector_o::numberOfInputQueues() const  {
    return  NumberOfInputQueues;
}

inline queue_o<output_o>* queueDirector_o::outputQueue()  {
    return  &OutputQueue;
}

inline string_o& operator << (string_o& s,const queueDirector_o& qd)  {
    s << "queueDirector_o: ";
    return  s;
}


#endif

/******************************************************************************/
