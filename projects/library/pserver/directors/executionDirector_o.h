/**  executionDirector_o.h  ****************************************************

    12.31.1999  Performance Server Library v2.000


    Execution Director Object.





changes log
when      who     what
5.1.99    Dan     Creation.
5.2.99    Dan     Added:    Using serverDirector_o object now.
5.4.99    Dan     Added:    Method string operator.
12.25.99  Dan     Changed:  Moved Number of thread counters to here.





                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ExecutionDirectorOBJECT_API
#define ExecutionDirectorOBJECT_API

#include "string_o"
#include "error_o"
#include "queue_o"
#include "server_o"
#include "workThread_o"
#include "queueDirector_o"
#include "threadDirector_o"
#include "serverDirector_o"
#include "inputGate_o"
#include "outputGate_o"

class pserver_o;

class executionDirector_o: public error_o  {
  friend pserver_o;
  private:
    mutex_o                     mutex;
    int                         NumberOfWorkThreads;
    queue_o<workThread_o>       workthreads;
    queue_o<server_o>           servers;
    queue_o<inputGate_o>        inputGates;
    int                         NumberOfOutputGateThreads;
    queue_o<outputGate_o>       outputGates;
    queueDirector_o             queueDirector;
    threadDirector_o            threadDirector;
    serverDirector_o            serverDirector;

  public:
    executionDirector_o();
    executionDirector_o(const executionDirector_o&);
    virtual  ~executionDirector_o();
    executionDirector_o& operator = (const executionDirector_o&);


    int     startWorkThreads(int);              // Start given number of
                                                // workThread_o threads.
    int     startInputGate(int);                // Start an inputgate_o
                                                // thread listening to the
                                                // given port.
    int     stopInputGate(int);                 // Stop the input watch
                                                // listening to given port.
    int     startOutputGate();                  // Start an outputgate_o
                                                // thread.
    int     startOutputGate(int);               // Start given number of
                                                // outputgate_o threads.
    int     stopOutputGate();                   // Stop an outputgate_o thread.


    int     numberOfWorkThreads() const;
    int     numberOfOutputGateThreads() const;
};
string_o& operator << (string_o&, const executionDirector_o&);


/******************************************************************************/

inline string_o& operator << (string_o& s,const executionDirector_o& ed)  {
    s << "executionDirector_o: ";
    return  s;
}

inline int executionDirector_o::numberOfWorkThreads() const  {
    return  NumberOfWorkThreads;
}

inline int executionDirector_o::numberOfOutputGateThreads() const  {
    return  NumberOfOutputGateThreads;
}


#endif

/******************************************************************************/
