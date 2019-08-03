/**  outputGate_o.h  ***********************************************************

    12.31.1999  Performance Server Library v2.000



    Output Gate Object.



log_o::debug levels
311 - Output Watch.
312 - Output Messages.
319 - Preformace time points.


changes log
when      who       what
4.3.99    Dan       Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef OutputGateOBJECT_API
#define OutputGateOBJECT_API

#include "thread_o.h"
#include "queue_o.h"
#include "sendrecv_o.h"
#include "output_o.h"


class outputGate_o: public thread_o  {
  private:
    queue_o<output_o>*  OutputQueue;
    unsigned long       NumberAdvanced;
    
  public:
    outputGate_o();                                     // Default constructor.
    outputGate_o(const outputGate_o&);                  // Copy contructor.
    outputGate_o(const thread_o&,queue_o<output_o>&);
    virtual      ~outputGate_o();                       // Default destructor.
    outputGate_o& operator = (const outputGate_o&);     // Assignment operator.

    void            tendgate();
    unsigned long   numberAdvanced() const;

};


/******************************************************************************/

inline unsigned long outputGate_o::numberAdvanced() const  {
    return  NumberAdvanced;
}


#endif

/******************************************************************************/
