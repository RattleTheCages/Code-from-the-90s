/**   workthread.h  ************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Work Thread Object.


debug_o levels
111 - Loop start and stop.
112 - Loop messages.
113 - Carapace messages.
119 - Preformace time points.


changes log
when      who       what
4.28.99   Dan       Creation
5.2.99    Dan       Changed   Constructor arguments.

*******************************************************************************/


#ifndef WORKTHREADOBJECT_API
#define WORKTHREADOBJECT_API


#include "thread.h"
#include "queue.h"
#include "../../sserver/dataobjects/input.h"
#include "../../sserver/dataobjects/output.h"


class workthread_o: public thread_o  {
  private:
    unsigned long       NumberAdvanced;
    queue_o<input_o>*   InputQueue;
    queue_o<output_o>*  OutputQueue;

  protected:
    int             workLoop();

  public:
    workthread_o();                                     // Default construtor.
    workthread_o(const workthread_o&);                  // Copy constructor.
    workthread_o(const thread_o&,queue_o<input_o>&,queue_o<output_o>&);
    virtual      ~workthread_o();                       // Default destrutor.
    workthread_o& operator = (const workthread_o&);     // Assignment operator.

    int             doWork();
    unsigned long   numberAdvanced()      const;
};


/******************************************************************************/

inline unsigned long workthread_o::numberAdvanced() const  {
    return  NumberAdvanced;
}


#endif

/******************************************************************************/
