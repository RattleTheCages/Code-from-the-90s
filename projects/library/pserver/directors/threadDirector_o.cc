/**  threadDirector_o.cc  ******************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman




Log Debug Levels
471 - Aquire threads.
472 - Relinquish threads.


changes log
when      who     what
4.28.99   Dan     Creation.

*******************************************************************************/


#include "log_o.h"
#include "sysinfo_o.h"
#include "threadDirector_o.h"
#include "queueDirector_o.h"

extern log_o               log;
extern sysinfo_o           sysinfo;


threadDirector_o::threadDirector_o():mutex("threadDirector_o")  {
    ThreadNumbers       = new short[::sysinfo.threadCeiling()];
    ThreadNumberIndex   = 0;
}

threadDirector_o::~threadDirector_o()  {
    delete[] ThreadNumbers;
}

thread_o* threadDirector_o::aquireThread(const char* n)  {
    string_o            message;
    int                 x;
    thread_o*           thread;

    thread = new thread_o(aquireThreadNumber(),n);
    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << *(error_o*)this;
        ::log.error(message);
        return NULL;
    }
    if(thread->error())  {
        *(error_o*)this = *(error_o*)thread;
        (message = "") << *this << "aquireThread(): " << *(error_o*)this;
        ::log.error(message);
    }

    if(::log.debug(471))  {
        (message = "") << *this <<  "aquireThread(): cirulating thread: " << *thread;
        ::log << message;
    }

    return thread;
}

int threadDirector_o::relinquishThread(thread_o* thread)  {
    string_o message;

    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "relinquishThread(): " << *(error_o*)this;
        ::log.error(message);
        return  0;
    }

    if(::log.debug(472))  {
        (message = "") << *this << "relinquishThread(): not implemented yet. ";
        ::log << message;
    }

}



/*
int threadDirector_o::relinquishWorkThread(workthread_o* workthread)  {
    workthread_o* lookat;
    mutex.lock("relinquishWorkThread()");
        lookat = WorkThreadQueue.get();
        while(lookat)  {
            if(lookat == workthread)  break;
            WorkThreadQueue.put(lookat);
            lookat = WorkThreadQueue.get();
        }
    mutex.unlock("relinquishWorkThread()");
    if(lookat)  relinquishThreadNumber(lookat->number());
    delete lookat;
    return 0;
}
*/

/*
const queue_o<inputWatch_o>* threadDirector_o::inputWatchQueue() const  {
    return &InputWatchQueue;
}
*/

/*
const inputWatch_o* threadDirector_o::inputWatch()  {
    inputWatch_o* inputWatch;
    mutex.lock("inputWatch()");
        inputWatch = InputWatchQueue.get();
        InputWatchQueue.put(inputWatch);
    mutex.unlock("inputWatch()");
    return inputWatch;
}
*/

/*
int threadDirector_o::aquireInputWatch(server_o* server,int priority)  {
    string_o            message;
    inputWatch_o*       inputWatch;
    thread_o            thread(aquireTopThreadNumber(),"inputWatch_o");
    inputWatch = new inputWatch_o(thread,server,priority);
    if(!inputWatch)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        ::log.error("threadDirector_o: new inputWatch_o returned null.");
        return error();
    }
    if(inputWatch->error() != ERROR_OK)  {
        *(error_o*)this = inputWatch->error();
        (message = "") << "threadDirector_o:" << *inputWatch << error();
        ::log.error(&message);
        return error();
    }
    else  {
        InputWatchQueue.put(inputWatch);
        *(error_o*)this = inputWatch->start(inputWatchThreadLoop,(void*)inputWatch);
    }
    return error();
}
*/

/*
int threadDirector_o::relinquishInputWatch(inputWatch_o* inputWatch)  {
    inputWatch_o* lookat;
    lookat = InputWatchQueue.get();
    while(lookat)  {
        if(lookat == inputWatch)  break;
        InputWatchQueue.put(lookat);
        lookat = InputWatchQueue.get();
    }
    if(lookat)  relinquishThreadNumber(lookat->number());
    delete lookat;
    return 0;
}
*/

/*
int threadDirector_o::aquireOutputWatch()  {
    string_o            message;
    outputWatch_o*      outputWatch;
    thread_o            thread(aquireTopThreadNumber(),"outputWatch_o");
    outputWatch = new outputWatch_o(thread);
    if(!outputWatch)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        ::log.error("threadDirector: new outputWatch_o returned null.");
        return error();
    }
    if(outputWatch->error() != ERROR_OK)  {
        *(error_o*)this = outputWatch->error();
        (message = "") << "threadDirector_o:" << *outputWatch << error();
        ::log.error(message);
        return error();
    }
    else  {
        OutputWatchQueue.put(outputWatch);
        *(error_o*)this = outputWatch->start(outputWatchThreadLoop,(void*)outputWatch);
    }
    return error();
}
*/

/*
int threadDirector_o::relinquishOutputWatch(outputWatch_o* outputWatch)  {
    outputWatch_o* lookat;
    lookat = OutputWatchQueue.get();
    while(lookat)  {
        if(lookat == outputWatch)  break;
        OutputWatchQueue.put(lookat);
        lookat = OutputWatchQueue.get();
    }
    if(lookat)  relinquishThreadNumber(lookat->number());
    delete lookat;
}
*/

int threadDirector_o::aquireThreadNumber()  {
    int ret;
    mutex.lock("aquireThreadNumber()");
        while(ThreadNumbers[ThreadNumberIndex] == 1)  {
            if(ThreadNumberIndex >= ::sysinfo.threadCeiling())
                ThreadNumberIndex = 0;
            ThreadNumberIndex++;
        }
        ThreadNumbers[ThreadNumberIndex] = 1;
        ret = ThreadNumberIndex+1;
    mutex.unlock("aquireThreadNumber()");
    return ret;
}

int threadDirector_o::aquireTopThreadNumber()  {
    int ret,x;
    x = ::sysinfo.threadCeiling() - 1;
    mutex.lock("aquireTopThreadNumber()");
        while(ThreadNumbers[x] == 1 && x > 0)  x--;
        if(x >= 0)  ThreadNumbers[x] = 1;
        ret = x+1;
    mutex.unlock("aquireTopThreadNumber()");
    return ret;
}

int threadDirector_o::relinquishThreadNumber(int tn)  {
    mutex.lock("relinquishThreadNumber()");
        ThreadNumbers[tn-1] = 0;
    mutex.unlock("relinquishThreadNumber()");
    return 0;
}


/******************************************************************************/
