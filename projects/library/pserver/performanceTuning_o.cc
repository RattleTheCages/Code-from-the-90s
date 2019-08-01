/**  performanceTuning_o.cc  ***************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Performance Server Performace Tuning Object.


changes log
when      who     what
12.22.99  Dan     Creation.


*******************************************************************************/


#include "log_o.h"
#include "performanceTuning_o.h"

extern log_o log;


performancetuning_o::performancetuning_o()  {
    Entity = new entity_o(0,PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES,PerformanceTuning_DNA_NUMBER_OF_GENES,0,"",0);


    readDNAforCycleNumberOfSamples();
    readDNAforPeriods();
    readDNAforNumberOfWorkThreads();
    readDNAforNumberOfOutputGateThreads();
    readDNAforStartReleaseDelay();
    readDNAforFinishReleaseDelay();
}


performancetuning_o::performancetuning_o(const entity_o& e)  {
    Entity = new entity_o(e);


    readDNAforCycleNumberOfSamples();
    readDNAforPeriods();
    readDNAforNumberOfWorkThreads();
    readDNAforNumberOfOutputGateThreads();
    readDNAforStartReleaseDelay();
    readDNAforFinishReleaseDelay();
}


performancetuning_o::~performancetuning_o()  {}


int performancetuning_o::setEntity(const entity_o& e)  {
    delete Entity;
    Entity = new entity_o(e);

    readDNAforCycleNumberOfSamples();
    readDNAforPeriods();
    readDNAforNumberOfWorkThreads();
    readDNAforNumberOfOutputGateThreads();
    readDNAforStartReleaseDelay();
    readDNAforFinishReleaseDelay();

    return ERROR_OK;
}


int performancetuning_o::readDNAforCycleNumberOfSamples()  {
    string_o message;
    int x,y;
    int offset,length;
    int cyclenumberofsamples;


    offset = 0;
    length = 24;


    cyclenumberofsamples = 0;
    for(x=0;x<PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES;x++)  {
        for(y=offset;y<length+offset;y++)  {
            cyclenumberofsamples = cyclenumberofsamples +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }
    }


    if(cyclenumberofsamples > 0 && 
       cyclenumberofsamples < PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES)
        CycleNumberOfSamples = cyclenumberofsamples;
    else  CycleNumberOfSamples = 1;


    if(::log.debug(33))  {
        (message = "") << "performancetuning_o: Performance Cycle Number of Samples set to ";
        message << CycleNumberOfSamples << ".";
        ::log << message;
    }


    return ERROR_OK;
}


int performancetuning_o::readDNAforPeriods()  {
    string_o message;
    int x,y,z;
    int offset,length;
    int period;


    offset = 24;
    length = 24;


    x = 0;
    for(z=0;z<CycleNumberOfSamples;z++)  {

        x = x + 1;
        if(PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES<=x)  x = 0;

        period = 0;
        for(y=offset;y<length+offset;y++)  {
            period = period +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }

        Period[z] = period;

        if(::log.debug(33))  {
            (message = "") << "performancetuning_o: Period in Cycle Sample " << z << " to " << Period[z] << ".";
            ::log << message;
        }
    }

    return ERROR_OK;
}

int performancetuning_o::readDNAforNumberOfWorkThreads()  {
    string_o message;
    int x,y,z;
    int offset,length;
    int numberOfWorkThreads;


    offset = 48;
    length = 24;


    x = 0;
    for(z=0;z<CycleNumberOfSamples;z++)  {

        x = x + 1;
        if(PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES<=x)  x = 0;

        numberOfWorkThreads = 0;
        for(y=offset;y<length+offset;y++)  {
            numberOfWorkThreads = numberOfWorkThreads +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }


        NumberOfWorkThreads[z] = numberOfWorkThreads;

        if(::log.debug(33))  {
            (message = "") << "performancetuning_o: Number of Work Threads in Cycle Sample " << z << " to " << NumberOfWorkThreads[z] << ".";
            ::log << message;
        }
    }

    return ERROR_OK;
}

int performancetuning_o::readDNAforNumberOfOutputGateThreads()  {
    string_o message;
    int x,y,z;
    int offset,length;
    int numberOfOutputGateThreads;


    offset = 72;
    length = 4;


    x = 0;
    for(z=0;z<CycleNumberOfSamples;z++)  {

        x = x + 1;
        if(PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES<=x)  x = 0;

        numberOfOutputGateThreads = 0;
        for(y=offset;y<length+offset;y++)  {
            numberOfOutputGateThreads = numberOfOutputGateThreads +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }


        NumberOfOutputGateThreads[z] = numberOfOutputGateThreads;

        if(::log.debug(33))  {
            (message = "") << "performancetuning_o: Number of Output Gate Threads in Cycle Sample " << z << " to " << NumberOfOutputGateThreads[z] << ".";
            ::log << message;
        }
    }

    return ERROR_OK;
}


int performancetuning_o::readDNAforStartReleaseDelay()  {
    string_o message;
    int x,y,z;
    int offset,length;
    int startReleaseDelay;


    offset = 72;
    length = 24;


    x = 0;
    for(z=0;z<CycleNumberOfSamples;z++)  {

        x = x + 1;
        if(PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES<=x)  x = 0;

        startReleaseDelay = 0;
        for(y=offset;y<length+offset;y++)  {
            startReleaseDelay = startReleaseDelay +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }


        StartReleaseDelay[z] = startReleaseDelay;

        if(::log.debug(33))  {
            (message = "") << "performancetuning_o: Start Release Delay in Cycle Sample " << z << " to " << StartReleaseDelay[z] << ".";
            ::log << message;
        }
    }

    return ERROR_OK;
}


int performancetuning_o::readDNAforFinishReleaseDelay()  {
    string_o message;
    int x,y,z;
    int offset,length;
    int finishReleaseDelay;


    offset = 96;
    length = 24;


    x = 0;
    for(z=0;z<CycleNumberOfSamples;z++)  {

        x = x + 1;
        if(PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES<=x)  x = 0;

        finishReleaseDelay = 0;
        for(y=offset;y<length+offset;y++)  {
            finishReleaseDelay = finishReleaseDelay +
                (((*(Entity->Chromosomes[x]))[y])-97);
        }


        FinishReleaseDelay[z] = finishReleaseDelay;

        if(::log.debug(33))  {
            (message = "") << "performancetuning_o: Finish Release Delay in Cycle Sample " << z << " to " << FinishReleaseDelay[z] << ".";
            ::log << message;
        }
    }

    return ERROR_OK;
}



/******************************************************************************/
