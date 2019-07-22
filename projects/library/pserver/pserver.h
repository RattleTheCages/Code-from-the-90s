/**  pserver.h  ****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Performance Server Base Class Object.



changes log
when      who     what
4.30.99   Dan     Creation.
9.9.99    Dan     Added:    Method outputQueue(output_o*).
10.31.99  Dan     Boo!      Data member number of workthreads.
12.24.99  Dan     Added:    Performance Tuning using DNA.

*******************************************************************************/


#ifndef PSERVEROBJECT_API
#define PSERVEROBJECT_API

#include "../lib/log/log.h"
#include "./directors/executionDirector.h"
#include "./carapace/carapace.h"
//#include "./performancetuning.h"


class pserver_o  {
  private:
//    performancetuning_o Performancetuning;
public://!!
    executionDirector_o executionDirector;


  public:
    pserver_o();                                        // Default constructor.
    pserver_o(const pserver_o&);                        // Copy constructor.
//    pserver_o(const entity_o&);                         // Server DNA given.
   ~pserver_o();                                        // Default destructor.
    pserver_o& operator = (const pserver_o&);           // Assignment operator.


    int     serveport(int);             // Start a server on the given port.
    int     discontinueServiceOnPort(int);

    void    persist();

    int     outputQueue(output_o*);


    //int     tunePerformance();
    //int     setEntity(const entity_o&);
};


#endif

/******************************************************************************/
