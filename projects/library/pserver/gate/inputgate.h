/**  inputgate.h  **************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



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


*******************************************************************************/


#ifndef INPUTGATEOBJECT_API
#define INPUTGATEOBJECT_API

#include "../../lib/thread/thread.h"
#include "../../lib/thread/queue.h"
#include "../../sserver/telenet/server.h"
#include "../../sserver/dataobjects/input.h"


class inputgate_o: public thread_o  {
  private:
    server_o*           Server;
    queue_o<input_o>*   InputQueue;
    unsigned long       NumberAdvanced;
    
  public:
    inputgate_o();                                      // Default constructor.
    inputgate_o(const inputgate_o&);                    // Copy contructor.
    inputgate_o(const thread_o&,server_o&,queue_o<input_o>&);
   ~inputgate_o();                                      // Default destructor.
    inputgate_o& operator = (const inputgate_o&);       // Assignment operator.

    void            tendgate();
    unsigned long   numberAdvanced() const;

};


/******************************************************************************/

inline unsigned long inputgate_o::numberAdvanced() const  {
    return NumberAdvanced;
}


#endif

/******************************************************************************/
