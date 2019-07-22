/**  pserver.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman


    Performance Server Base Class Object.



changes log
when      who     what
4.28.99   Dan     Creation.
9.9.99    Dan     Added:    Method outputQueue(output_o*).
10.31.99  Dan     Boo!      Data member number of workthreads.
12.24.99  Dan     Added:    Perofrmance Tuning useing DNA.


*******************************************************************************/


#include "../lib/log/log.h"
#include "./pserver.h"

extern log_o log;


pserver_o::pserver_o()  {}

/*
pserver_o::pserver_o(const entity_o& e): Performancetuning(e)  {
    NumberOfWorkthreads = Performancetuning.numberOfWorkThreads(0);
    if(NumberOfWorkthreads < 16)  NumberOfWorkthreads = 16;
}
*/

pserver_o::~pserver_o()  {}


int pserver_o::serveport(int port)  {
    int         err;
    string_o    message;


    if(::log.debug(10))  {
        (message = "") << "pserver_o: Starting to serve port: " << port << ".";
        ::log << message;
    }

    if(executionDirector.startInputGate(port))  {
        (message = "") << "pserver_o: serveport: ";
        message << *(error_o*)&executionDirector;
        ::log.error(message);
        return executionDirector.error();
    }

    if(executionDirector.startOutputGate())  {
        (message = "") << "pserver_o: serveport: ";
        message << *(error_o*)&executionDirector;
        ::log.error(message);
        return executionDirector.error();
    }


    if(::log.debug(10))  {
        (message = "") << "pserver_o: Starting work threads.";
        ::log << message;
    }

    //if(executionDirector.startWorkThreads(24))  {//!!!!!!!!!!!!
    if(executionDirector.startWorkThreads(2))  {//!!!!!!!!!!!!
        (message = "") << "pserver_o: startWorkThreads: ";
        message << *(error_o*)&executionDirector;
        ::log.error(message);
    }

    return 0;
}

int pserver_o::discontinueServiceOnPort(int port)  {
    string_o message;

    if(::log.debug(11))  {
        (message = "") << "pserver_o: discontinuing service to port: " << port << ".";
        ::log << message;
    }

    if(executionDirector.stopInputGate(port))  {
        (message = "") << "pserver_o: discontinueServiceOnPort: ";
        message << *(error_o*)&executionDirector;
        ::log.error(message);
    }
    return ERROR_OK;
}

#include <unistd.h>
void pserver_o::persist()  {
    while(1)  {
      //  tunePerformance();

        //::sleep(240);
        ::sleep(30);
    }
}

int pserver_o::outputQueue(output_o* output)  {
    return executionDirector.queueDirector.outputQueue()->put(output);
}

/*
int pserver_o::tunePerformance()  {
    int x;
    string_o message;


    if(::log.debug(19))  {
        (message = "") << "pserver_o: Tune Performace Called.";
        ::log << message;
    }




    if(Performancetuning.numberOfWorkThreads(0) > executionDirector.numberOfWorkThreads())  {
        executionDirector.startWorkThreads(Performancetuning.numberOfWorkThreads(0)-executionDirector.numberOfWorkThreads());
    }

    if(::log.debug(19))  {
        (message = "") << "pserver_o: Performancetuning Object requests ";
        message << executionDirector.numberOfWorkThreads() << " work threads.";
        ::log << message;
    }



    if(Performancetuning.numberOfOutputGateThreads(0) > executionDirector.numberOfOutputGateThreads())  {
        for(x=executionDirector.numberOfOutputGateThreads();x<Performancetuning.numberOfOutputGateThreads(0);x++)  {
            executionDirector.startOutputGate();
        }
    }

    if(::log.debug(19))  {
        (message = "") << "pserver_o: Performancetuning Object requests ";
        message << executionDirector.numberOfOutputGateThreads() << " output gate threads.";
        ::log << message;
    }



    return ERROR_OK;    
}

int pserver_o::setEntity(const entity_o& entity)  {
    Performancetuning.setEntity(entity);

    return ERROR_OK;
}

*/


/******************************************************************************/
