/**  inputGate_o.h  ************************************************************

    12.31.1999  Performance Server Library v2.000



    Input Gate Object.



log_o::debug levels
301 - Input watch loop.
302 - Input messages.
309 - Preformance time points.


changes log
when      who       what
4.28.99   Dan       Creation 
5.2.99    Dan       Changed   Constructor arguments.
5.4.99    Dan       Added     Method string operator.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef InputGateOBJECT_API
#define InputGateOBJECT_API

#include "thread_o.h"
#include "queue_o.h"
#include "server_o.h"
#include "input_o.h"


class inputGate_o: public thread_o  {
  private:
    server_o*           Server;
    queue_o<input_o>*   InputQueue;
    unsigned long       NumberAdvanced;
    
  public:
    inputGate_o();                                      // Default constructor.
    inputGate_o(const inputGate_o&);                    // Copy contructor.
    inputGate_o(const thread_o&,server_o&,queue_o<input_o>&);
    virtual     ~inputGate_o();                         // Default destructor.
    inputGate_o& operator = (const inputGate_o&);       // Assignment operator.

    void            tendgate();
    unsigned long   numberAdvanced() const;

};


/******************************************************************************/

inline unsigned long inputGate_o::numberAdvanced() const  {
    return NumberAdvanced;
}


#endif

/******************************************************************************/
