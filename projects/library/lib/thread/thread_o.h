/**  thread_o.h  ***************************************************************

    12.31.1999  Performance Server Library v2.000


    Thread Abstraction Object.



changes log
when      who     what
4.29.99   Dan     Creation.
9.9.99    Dan     Added:    Method usleep().
10.5.99   Dan     Added:    Method int start(void*,void*).




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ThreadOBJECT_API
#define ThreadOBJECT_API

#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <pthread.h>
//#include <thread.h>  for sunos
#include <signal.h>

#include "string_o"
#include "error_o"


class thread_o: public error_o  {
  private:
    pthread_t       PThread;
    int             Number;
    int             Priority;
    string_o        Name;

  public:
    thread_o();                             // Default constructor.
    thread_o(const thread_o&);              // Copy constructor.
    thread_o(int, const char*);             // Thread number and name given.
    virtual  ~thread_o();                   // Default destructor.
    thread_o& operator = (const thread_o&); // Assignment operator.


    int             start(void*, void*);    // Start this thread with the
                                            // given c++ method (first
                                            // argument), pointer to
                                            // object (second argument).
    int             start(void*(*)(void*), void*);
                                            // Start this thread with the
                                            // given function (first argument).
    void            exit();                 // Terminate this thread.
    void            yeild();                // Yeild this thread.
    void            usleep(unsigned int);   // Sleep for microsceonds.

    int             number()    const;      // Return this thread's number.
    int             priority()  const;      // Return this thread's priority.
    const char*     name()      const;      // Return this thread's name and
                                            // number.
};
string_o& operator << (string_o&, const thread_o&);


/******************************************************************************/

inline int thread_o::number() const  {
    return  Number;
}

inline int thread_o::priority() const  {
    return  Priority;
}

inline const char* thread_o::name() const  {
    return  Name.string();
}


#endif

/******************************************************************************/
