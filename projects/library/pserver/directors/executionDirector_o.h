/**  executionDirector_o.h  ****************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Execution Director Object.


changes log
when      who     what
5.1.99    Dan     Creation.
5.2.99    Dan     Added:    Using serverDirector_o object now.
5.4.99    Dan     Added:    Method string operator.
12.25.99  Dan     Changed:  Moved Number of thread counters to here.

*******************************************************************************/


#ifndef ExecutionDirectorOBJECT_API
#define ExecutionDirectorOBJECT_API

#include "string_o.h"
#include "error_o.h"
#include "queue_o.h"
#include "server_o.h"
#include "workThread_o.h"
#include "queueDirector_o.h"
#include "threadDirector_o.h"
#include "serverDirector_o.h"
#include "inputGate_o.h"
#include "outputGate_o.h"


class executionDirector_o: public error_o  {
  private:
public://!!
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
    executionDirector_o();                              // Default constructor.
    executionDirector_o(const executionDirector_o&);    // Copy constuctor.
    virtual  ~executionDirector_o();                    // Default desructor.
    executionDirector_o& operator = (const executionDirector_o&);
                                                        // Assignment operator.


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
