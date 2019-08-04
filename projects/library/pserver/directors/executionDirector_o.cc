/**  executionDirector_o.cc  ***************************************************

    12.31.1999  Performance Server Library v2.000

    Execution Director Implementation.




Debug Levels
401 - Starting workThread_o threads.
402 - Stopping workThread_o threads.
403 - Starting inputGate_o threads.
404 - Stopping inputGate_o threads.
405 - Starting outputGate_o threads.
406 - Stopping outputGate_o threads.


changes log
when      who       what
5.1.99    Dan       Creation.
5.4.99    Dan       Added:    Some error responces.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "log_o"
#include "executionDirector_o"
#include "inputGate_o"
#include "outputGate_o"

extern log_o    log;

//extern "C" {

void* workthreadLoop(void* workthread)  {
    (void)((workThread_o*)workthread)->doWork();
    (void)((workThread_o*)workthread)->exit();
    return workthread;
}

void* inputGateThreadLoop(void* inputGateThread)  {
    (void)((inputGate_o*)inputGateThread)->tendgate();
    (void)((thread_o*)inputGateThread)->exit();
    return inputGateThread;
}

void* outputGateThreadLoop(void* outputGateThread)  {
    (void)((outputGate_o*)outputGateThread)->tendgate();
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
    workThread_o*       workthread;

    NumberOfWorkThreads = NumberOfWorkThreads + nw;

    if(::log.debug(401))  {
        (message = "") << *this << "starting " << nw;
        message << " workThread_o threads.";
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

        workthread = new workThread_o(*thread,*inputqueue,*outputqueue);
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

    return  error();
}

int executionDirector_o::startInputGate(int p)  {
    string_o            message;
    thread_o*           thread;
    server_o*           server;
    queue_o<input_o>*   queue;
    inputGate_o*        inputGate;

    if(::log.debug(403))  {
        (message = "") << *this << "starting inputGate_o at port ";
        message << p << '.';
        ::log << message;
    }

    thread = threadDirector.aquireThread("inputGate");
    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);
        return  error();
    }
    if(thread->error())  {
        *(error_o*)this = *(error_o*)thread;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        delete thread;
        return  error();
    }

    server = serverDirector.aquireServer(p);
    if(!server)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);
        return  error();
    }
    if(server->error())  {
        *(error_o*)this = *(error_o*)server;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return  error();
    }

    queue = queueDirector.inputQueue(0);//!!
    if(!queue)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return  error();
    }

    inputGate = new inputGate_o(*thread,*server,*queue);
    if(!inputGate)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        (message = "") << *this << "startInputGate: ";
        message << "inputGate_o constructor returned null.";
        ::log.error(message);

        serverDirector.relinquishServer(server);
        return  error();
    }
    if(inputGate->error())  {
        *(error_o*)this = *(error_o*)inputGate;
        (message = "") << *this << "startInputGate: " << *(error_o*)this;
        ::log.error(message);

        delete inputGate;
        serverDirector.relinquishServer(server);
        return  error();
    }

    inputGates.put(inputGate);
    inputGate->start(inputGateThreadLoop,inputGate);

    return  error();
}

int executionDirector_o::stopInputGate(int p)  {
    string_o message;

    if(::log.debug(404))  {
        (message = "") << *this << "stopping inputGate_o at port ";
        message << p << '.';
        ::log << message;
    }

    return  ERROR_OK;
}

int executionDirector_o::startOutputGate()  {
    string_o            message;
    thread_o*           thread;
    server_o*           server;
    queue_o<output_o>*  outqueue;
    outputGate_o*       outputGate;


    NumberOfOutputGateThreads = NumberOfOutputGateThreads + 1;

    if(::log.debug(405))  {
        (message = "") << *this << "starting outputGate_o object.";
        ::log << message;
    }

    thread = threadDirector.aquireThread("outputGate");
    if(!thread)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputgate(): " << *(error_o*)this;
        ::log.error(message);
        return  error();
    }
    if(thread->error())  {
        *(error_o*)this = *(error_o*)thread;
        (message = "") << *this << "startOutputgate(): " << *(error_o*)this;
        ::log.error(message);

        delete thread;
        return  error();
    }

    server = serverDirector.existingServer();
    if(!server)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        return  error();
    }
    if(server->error())  {
        *(error_o*)this = *(error_o*)server;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return  error();
    }

    outqueue = queueDirector.outputQueue();
    if(!outqueue)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return  error();
    }

    outputGate = new outputGate_o(*thread,*outqueue);
    if(!outputGate)  {
        *(error_o*)this = ERROR_OUT_OF_RESOURCES;
        (message = "") << *this << "startOutputGate(): " << *(error_o*)this;
        ::log.error(message);

        threadDirector.relinquishThread(thread);
        delete server;
        return  error();
    }


    outputGates.put(outputGate);
    outputGate->start(outputGateThreadLoop,outputGate);


    return  error();
}


/******************************************************************************/
