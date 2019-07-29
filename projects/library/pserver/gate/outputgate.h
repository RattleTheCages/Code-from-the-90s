/**  outputgate.h  *************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Output Gate Object.



log_o::debug levels
311 - Output Watch.
312 - Output Messages.
319 - Preformace time points.


changes log
when      who       what
4.3.99    Dan       Creation.


*******************************************************************************/


#ifndef OUTPUTGATEOBJECT_API
#define OUTPUTGATEOBJECT_API

#include "../../lib/thread/thread.h"
#include "../../lib/thread/queue.h"
#include "../../sserver/telenet/sendrecv.h"
#include "../../sserver/dataobjects/output.h"


class outputgate_o: public thread_o  {
  private:
    queue_o<output_o>*  OutputQueue;
    unsigned long       NumberAdvanced;
    
  public:
    outputgate_o();                                     // Default constructor.
    outputgate_o(const outputgate_o&);                  // Copy contructor.
    outputgate_o(const thread_o&,queue_o<output_o>&);
   ~outputgate_o();                                     // Default destructor.
    outputgate_o& operator = (const outputgate_o&);     // Assignment operator.

    void            tendgate();
    unsigned long   numberAdvanced() const;

};


/******************************************************************************/

inline unsigned long outputgate_o::numberAdvanced() const  {
    return NumberAdvanced;
}


#endif

/******************************************************************************/
