/**  performancetuning.h  ******************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Performance Server Performace Tuning Object.


changes log
when      who     what
12.22.99  Dan     Creation.
12.24.99  Dan     Added:    Genetic performance monitoring.

*******************************************************************************/


#ifndef PERFORMANCETUNINGOBJECT_API
#define PERFORMANCETUNINGOBJECT_API

#include "../lib/log/log.h"
#include "./directors/executionDirector.h"
#include "./carapace/carapace.h"
#include "../genetic/entity/entity.h"


#define PERFORMANCETUNING_DNA_NUMBER_OF_CHROMOSOMES     24
#define PERFORMANCETUNING_DNA_NUMBER_OF_GENES         2048



#define PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES 1024
#define PERFORMANCETUNING_MAX_PERFORMANCE_CYCLEPERIOD          1024



class performancetuning_o  {
  private:
    entity_o*   Entity;

    int CycleNumberOfSamples;
    int Period[PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int NumberOfWorkThreads[PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int NumberOfOutputGateThreads[PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int StartReleaseDelay[PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int FinishReleaseDelay[PERFORMANCETUNING_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];


  public:
    performancetuning_o();                              // Default constructor.
    performancetuning_o(const performancetuning_o&);    // Copy constructor.
    performancetuning_o(const entity_o&);               // Performance DNA.
   ~performancetuning_o();                              // Default destructor.
    performancetuning_o& operator = (const performancetuning_o&);
                                                        // Assignment operator.


    int     setEntity(const entity_o&);


    int     readDNAforCycleNumberOfSamples();
    int     readDNAforPeriods();
    int     readDNAforNumberOfWorkThreads();
    int     readDNAforNumberOfOutputGateThreads();
    int     readDNAforStartReleaseDelay();
    int     readDNAforFinishReleaseDelay();

    int     numberOfWorkThreads(int) const;
    int     numberOfOutputGateThreads(int) const;
};


/******************************************************************************/

inline int performancetuning_o::numberOfWorkThreads(int sample) const  {
    if(sample > 0 && sample < CycleNumberOfSamples)  {
        return NumberOfWorkThreads[sample];
    }
    return NumberOfWorkThreads[0];
}

inline int performancetuning_o::numberOfOutputGateThreads(int sample) const  {
    if(sample > 0 && sample < CycleNumberOfSamples)  {
        return NumberOfOutputGateThreads[sample];
    }
    return NumberOfOutputGateThreads[0];
}


#endif

/******************************************************************************/
