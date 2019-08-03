/**  pserver_o.h  **************************************************************

    12.31.1999  Performance Server Library v2.000



    Performance Server Base Class Object.

    Performance tuned by server DNA.


changes log
when      who     what
4.30.99   Dan     Creation.
9.9.99    Dan     Added:    Method outputQueue(output_o*).
10.31.99  Dan     Boo!      Data member number of workthreads.
12.24.99  Dan     Added:    Performance Tuning using DNA.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef PServerOBJECT_API
#define PServerOBJECT_API

#include "log_o"
#include "executionDirector_o"
#include "carapace_o"
//#include "performanceTuning_o"


class pserver_o  {
  private:
//    performanceTuning_o PerformanceTuning;
public://!!
    executionDirector_o executionDirector;


  public:
    pserver_o();                                        // Default constructor.
    pserver_o(const pserver_o&);                        // Copy constructor.
//    pserver_o(const entity_o&);                         // Server DNA given.
    virtual   ~pserver_o();                             // Default destructor.
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
