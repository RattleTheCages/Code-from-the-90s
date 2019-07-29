/**  thread.cc  ****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman






changes log
when      who     what
4.29.99   Dan     Creation.
9.9.99    Dan     Added:    Method usleep().
10.5.99   Dan     Added:    Method int start(void*,void*).

*******************************************************************************/

#include <stdio.h>

#include <unistd.h>
#include <errno.h>

#include "../../lib/thread/thread.h"


thread_o::thread_o():Number(-1)  {}

thread_o::thread_o(const thread_o& t)  {
    Number  = t.number();
    Name    = t.name();
}

thread_o::thread_o(int tn,const char* tname)  {
    Number = tn;
    Name << tn << '-' << tname;
}

thread_o::~thread_o()  {}

int thread_o::start(void* func,void* obj)  {
printf("thread start1");
fflush(stdout);
    return start((void*(*)(void*))func,obj);
}

int thread_o::start(void*(*func)(void*),void* arg)  {
printf("thread start2");
fflush(stdout);



    if(::pthread_create(&PThread,NULL,func,arg))  {
        ((error_o*)this)->thread(errno);
    }
    return error();
}

void thread_o::exit()  {
    (void)::pthread_exit(NULL);
}

void thread_o::yeild()  {
    (void)::usleep(999);
}

void thread_o::usleep(unsigned int us)  {
    (void)::usleep(us);
}

string_o& operator << (string_o& s,const thread_o& thread)  {
    s << thread.name() << ": ";
    return s;
}


/******************************************************************************/
