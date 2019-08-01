/**  performanceTuning_o.h  ****************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Performance Server Performace Tuning Object.


changes log
when      who     what
12.22.99  Dan     Creation.
12.24.99  Dan     Added:    Genetic performance monitoring.

*******************************************************************************/


#ifndef PerformanceTuningOBJECT_API
#define PerformanceTuningOBJECT_API

#include "log_o.h"
#include "executionDirector_o.h"
#include "carapace_o.h"
#include "entity_o.h"


#define PerformanceTuning_DNA_NUMBER_OF_CHROMOSOMES     24
#define PerformanceTuning_DNA_NUMBER_OF_GENES         2048



#define PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES 1024
#define PerformanceTuning_MAX_PERFORMANCE_CYCLEPERIOD          1024



class performanceTuning_o  {
  private:
    entity_o*   Entity;

    int CycleNumberOfSamples;
    int Period[PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int NumberOfWorkThreads[PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int NumberOfOutputGateThreads[PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int StartReleaseDelay[PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];
    short int FinishReleaseDelay[PerformanceTuning_MAX_PERFORMANCE_CYCLENUMBEROFSAMPLES];


  public:
    performanceTuning_o();                              // Default constructor.
    performanceTuning_o(const performanceTuning_o&);    // Copy constructor.
    performanceTuning_o(const entity_o&);               // Performance DNA.
    virtual ~performanceTuning_o();                     // Default destructor.
    performanceTuning_o& operator = (const performanceTuning_o&);
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

inline int performanceTuning_o::numberOfWorkThreads(int sample) const  {
    if(sample > 0 && sample < CycleNumberOfSamples)  {
        return NumberOfWorkThreads[sample];
    }
    return NumberOfWorkThreads[0];
}

inline int performanceTuning_o::numberOfOutputGateThreads(int sample) const  {
    if(sample > 0 && sample < CycleNumberOfSamples)  {
        return NumberOfOutputGateThreads[sample];
    }
    return NumberOfOutputGateThreads[0];
}


#endif

/******************************************************************************/
