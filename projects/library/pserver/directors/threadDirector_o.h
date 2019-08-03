/**  threadDirector_o.h  *******************************************************

    12.31.1999  Performance Server Library v2.000



    Thread Director Object.



changes log
when      who     what
4.28.99   Dan     Creation.
5.4.99    Dan     Added:    Method string operator.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ThreadDirectorOBJECT_API
#define ThreadDirectorOBJECT_API

#include "thread_o.h"
#include "queue_o.h"
#include "error_o.h"
#include "sysinfo_o.h"
#include "server_o.h"


class threadDirector_o: public error_o  {
  private:
    mutex_o                     mutex;

    int                         NumberOfOutstandingThreads;
    short*                      ThreadNumbers;
    int                         ThreadNumberIndex;

    int                         aquireThreadNumber();
    int                         aquireTopThreadNumber();
    int                         relinquishThreadNumber(int);

  public:
    threadDirector_o();                             // Default constructor.
    threadDirector_o(const threadDirector_o&);      // Copy constuctor.
    virtual          ~threadDirector_o();           // Default desructor.
    threadDirector_o& operator = (const threadDirector_o&);
                                                    // Assignment operator.
    thread_o*       aquireThread(const char*);
    int             relinquishThread(thread_o*);
    int             numberOfOutstandingThreads()                  const;
};
string_o& operator << (string_o&, const threadDirector_o&);


/******************************************************************************/


inline int threadDirector_o::numberOfOutstandingThreads() const  {
    return  NumberOfOutstandingThreads;
}

inline string_o& operator << (string_o& s,const threadDirector_o& td)  {
    s << "threadDirector_o: ";
    return  s;
}


#endif

/******************************************************************************/
