/**  mutex_o.h  ****************************************************************

   Copyright 12.31.1999  Performance Server Library v2.000



    Mutal Exclusion Abstration Object.


changes log
when      who       what
4.29.99   Dan       Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef MutexOBJECT_API
#define MutexOBJECT_API

#include <pthread.h>
//#include <thread.h>  for sunos
#include <signal.h>

#include "string_o"
#include "error_o"


class mutex_o: private error_o  {
  protected:
    string_o        ObjectName;

    pthread_mutex_t Mutex;
    pthread_cond_t  ConditionVariable;

  public:
    mutex_o();                                  // Default constructor.
    mutex_o(const mutex_o&);                    // Copy constuctor.
    mutex_o(const char*);                       // Object name given.
    virtual ~mutex_o();                         // Default destuctor.
    mutex_o& operator = (const mutex_o&);       // Assignment operator.

    int     lock();                             // Lock mutex.
    int     unlock();                           // Unlock mutex.
    int     lock(const char*);                  // Lock mutex.
    int     unlock(const char*);                // Unlock mutex.

    int     wait(const char*);                  // Wait on this's condition
                                                // variable.
    int     wait(mutex_o&,const char*);         // Wait on given mutex_o's
                                                // condition variable.
    int     broadcast(const char*);             // Broadcast on this's
                                                // condition variable.
};


#endif

/*********************************************************************************/
