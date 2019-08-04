/**   workThread_o.h  **********************************************************

    12.31.1999  Performance Server Library v2.000


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




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef WorkThreadOBJECT_API
#define WorkThreadOBJECT_API


#include "thread_o"
#include "queue_o"
#include "input_o"
#include "output_o"


class workThread_o: public thread_o  {
  private:
    unsigned long       NumberAdvanced;
    queue_o<input_o>*   InputQueue;
    queue_o<output_o>*  OutputQueue;

  protected:
    int             workLoop();

  public:
    workThread_o();
    workThread_o(const workThread_o&);
    workThread_o(const thread_o&,queue_o<input_o>&, queue_o<output_o>&);
    virtual      ~workThread_o();
    workThread_o& operator = (const workThread_o&);

    int             doWork();
    unsigned long   numberAdvanced()      const;
};


/******************************************************************************/

inline unsigned long workThread_o::numberAdvanced() const  {
    return  NumberAdvanced;
}


#endif

/******************************************************************************/
