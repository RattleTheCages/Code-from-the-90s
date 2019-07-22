/**  executionDirector.cc  *****************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



Debug Levels
401 - Starting workthread_o threads.
402 - Stopping workthread_o threads.
403 - Starting inputgate_o threads.
404 - Stopping inputgate_o threads.
405 - Starting outputgate_o threads.
406 - Stopping outputgate_o threads.


changes log
when      who       what
5.1.99    Dan       Creation.
5.4.99    Dan       Added:    Some error responces.

*******************************************************************************/

#include <stdio.h>

#include "../../lib/log/log.h"
#include "../directors/executionDirector.h"
#include "../gate/inputgate.h"
#include "../gate/outputgate.h"

extern log_o    log;

//extern "C" {

void* workthreadLoop(void* workthread)  {
    (void)((workthread_o*)workthread)->doWork();
    (void)((workthread_o*)workthread)->exit();
    return workthread;
}

void* inputGateThreadLoop(void* inputGateThread)  {
printf("inputput gate thread look");
fflush(stdout);
    (void)((inputgate_o*)inputGateThread)->tendgate();
    (void)((thread_o*)inputGateThread)->exit();
    return inputGateThread;
}

void* outputGateThreadLoop(void* outputGateThread)  {
    (void)((outputgate_o*)outputGateThread)->tendgate();
    (void)((thread_o*)outputGateThread)->exit();
    return outputGateThread;
}
//}


executionDirector_o::executionDirector_o(): mutex("executionDirector_o")  {
    NumberOfWorkThreads = 0;
    NumberOfOutputGateThreads = 0;
}

executionDirector_o::~executionDirector_o()  {}

int executionDirector_o::startWorkThreads(int nw)  {
    string_o message;
    int      x;
    queue_o<input_o>*   inputqueue;
    queue_o<output_o>*  outputqueue;
    thread_o*           thread;
    workthread_o*       workthread;

    NumberOfWorkThreads = NumberOfWorkThreads + nw;

    if(::log.debug(401))  {
        (message = "") << *this << "starting " << nw;
        message << " workthread_o threads.";
        ::log << message;
    }

    for(x=0;x<nw;x++)  {

        inputqueue = queueDirector.inputQueue(0);//!!
        if(!inputqueue)  {
            *(error_o*)this = ERROR_NULL_PASSED;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);
            return error();
        }

        outputqueue = queueDirector.outputQueue();
        if(!outputqueue)  {
            *(error_o*)this = ERROR_NULL_PASSED;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);
            return error();
        }

        thread = threadDirector.aquireThread("workthread");
        if(!thread)  {
            *(error_o*)this = ERROR_NULL_PASSED;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);
            return error();
        }
        if(thread->error())  {
            *(error_o*)this = *(error_o*)thread;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);

            delete thread;
            return error();
        }

        workthread = new workthread_o(*thread,*inputqueue,*outputqueue);
        if(!workthread)  {
            *(error_o*)this = ERROR_OUT_OF_RESOURCES;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);
        }
        if(workthread->error())  {
            *(error_o*)this = *(error_o*)workthread;
            (message = "") << *this << "startWorkThreads: " << *(error_o*)this;
            ::log.error(message);

            delete workthread;
            delete thread;
            return error();
        }


        workthread->start(workthreadLoop,workthread);

    }

    return error();
}

int executionDirector_o::startInputGate(int p)  {
    string_o            message;
    thread_o*           thread;
    server_o*           server;
    queue_o<input_o>*   queue;
    inputgate_o*        inputgate;

    if(::log.debug(403))  {
        (message = "") << *this << "starting inputgate_o at port ";
        message << p << '.';
        ::log << message;
    }

    thread = threadDirector.aquireThread("inputgate");
    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);
        return error();
    }
    if(thread->error())  {
        *(error_o*)this = *(error_o*)thread;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        delete thread;
        return error();
    }

    server = serverDirector.aquireServer(p);
    if(!server)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);
        return error();
    }
    if(server->error())  {
        *(error_o*)this = *(error_o*)server;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return error();
    }

    queue = queueDirector.inputQueue(0);//!!
    if(!queue)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return error();
    }

    inputgate = new inputgate_o(*thread,*server,*queue);
    if(!inputgate)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        (message = "") << *this << "startInputGate: ";
        message << "inputgate_o constructor returned null.";
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return error();
    }
    if(inputgate->error())  {
        *(error_o*)this = *(error_o*)inputgate;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        delete inputgate;
        serverDirector.relinquishServer(server);
        return error();
    }

    inputgates.put(inputgate);
    inputgate->start(inputGateThreadLoop,inputgate);

    return error();
}

int executionDirector_o::stopInputGate(int p)  {
    string_o message;

    if(::log.debug(404))  {
        (message = "") << *this << "stopping inputgate_o at port ";
        message << p << '.';
        ::log << message;
    }

    return ERROR_OK;
}

int executionDirector_o::startOutputGate()  {
    string_o            message;
    thread_o*           thread;
    server_o*           server;
    queue_o<output_o>*  outqueue;
    outputgate_o*       outputgate;


    NumberOfOutputGateThreads = NumberOfOutputGateThreads + 1;

    if(::log.debug(405))  {
        (message = "") << *this << "starting outputgate_o object.";
        ::log << message;
    }

    thread = threadDirector.aquireThread("outputgate");
    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputgate(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }
    if(thread->error())  {
        *(error_o*)this = *(error_o*)thread;
        (message = "") << *this << "startOutputgate(): " << *(error_o*)this;
        ::log.error(message);

        delete thread;
        return error();
    }

    server = serverDirector.exsitingServer();
    if(!server)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        return error();
    }
    if(server->error())  {
        *(error_o*)this = *(error_o*)server;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return error();
    }

    outqueue = queueDirector.outputQueue();
    if(!outqueue)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return error();
    }

    outputgate = new outputgate_o(*thread,*outqueue);
    if(!outputgate)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return error();
    }


    outputgates.put(outputgate);
    outputgate->start(outputGateThreadLoop,outputgate);


    return error();
}


/******************************************************************************/
