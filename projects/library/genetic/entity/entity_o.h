/**  entity_o.h  ***************************************************************

    12.31.1999  Performance Server Library v2.000




    DNA Artifical Intellegence Entity Object.





when        who        what
9.24.96     Dan        Creation.
9.4.96      Dan        Removed:  NUMBER_OF_CHROMOSOMES define.
                       Added:    _number_of_chromosomes as a private member,
                                 number_of_chromosomes().
5.17.98     Dan        Changed:  Name of object from entity_ to entity_o,
                                 _number_of_chromosomes to NumberOfChromosomes.
6.14.98     Dan        Added:    Some constructors.
6.15.98     Dan        Added:    A rand_o object as a argument.
6.22.98     Dan        Changed:  Data member name to a string_o object,
                                 arguments of the active constructors.
6.23.98     Dan        Added:    Data member mutate, and supporting methods.
                                 Methods name, setName.
6.24.98     Dan        Added:    Data members score, and object.
6.27.98     Dan        Added:    Inheritance of a thread object.
7.12.98     Dan        Changed:  method duplicate to return type chromosome_o*
                                 and removed DulicateChromosome data member.
8.9.98      Dan        Added:    Method mutate().
2.20.99     Dan        Added:    Data members RunningScore and Iterations.
9.2.99      Dan        Removed:  Passing a rand_o object, and rand object.





                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef EntityOBJECT_API
#define EntityOBJECT_API

#include "string_o"
#include "chromosome_o"


#define ENTITY_OBJECT                "entity_o"
#define ENTITY_NUMBER_OF_CHROMOSOMES "numberofchromosomes"
#define ENTITY_CHROMOSOME            "chromosome"
#define ENTITY_MUTATION_RATE         "mutationrate"
#define ENTITY_NAME                  "name"
#define ENTITY_UNIQUEID              "uniqueid"
#define ENTITY_GENERATION            "generation"
#define ENTITY_SCORE                 "score"
#define ENTITY_RUNNING_SCORE         "runningscore"

#define ENTITY_MAX_NUMBER_OF_GENES       8192
#define ENTITY_MAX_NUMBER_OF_CHROMOSOMES   32


class entity_o  {
  protected:
    int             NumberOfChromosomes;
    int             MutationRate;
    chromosome_o**  Chromosomes;
    string_o        Name;
    int             Uniqueid;
    int             Generation;
    int             Score;
    long            RunningScore;
    int             Iteration;
    void*           Object;

  public:
    entity_o();                                         // Default constructor.
    entity_o(const entity_o&);                          // Copy constructor.
    entity_o(const char*);
    entity_o(int,int,int,int,const char*,int);  // Generation, number of
                                                // chromosomes, number of genes,
                                                // uniqueid, name,
                                                // and mutation rate given.
    virtual        ~entity_o();                 // Destructor.
    entity_o&       operator = (const entity_o&);       // Assignment operator.
    void            operator >> (string_o&) const;      // OLP representation.
    void            operator << (const char*);          // Reconstruct.


//!!
//chromosome_o**   Chromosomes;

    chromosome_o* duplicate(int);               // Return a dupilcate of
                                                // chromosome at index int.
    entity_o*   reproduce(const entity_o&,int) const;
    void        display(string_o&,int) const;
    int         numberOfChromosomes() const;

    void        crossover(const entity_o&,int,int,int,int);
    void        mutate();

    const char* name()                const;
    int         uniqueid()            const;
    int         generation()          const;

    int         mutationRate()        const;
    void        setMutationRate(int);
    void        setName(const string_o&);

    int         score()               const;
    long        runningScore()        const;
    double      trscore() const;
    int         iteration()           const;
    void        iterate();
    void        setScore(int);
    void        inRunningScore(int);
    void*       object()              const;
    void        setObject(void*);

    chromosome_o** chromosomes();
};


/******************************************************************************/

inline int entity_o::numberOfChromosomes() const  {
    return  NumberOfChromosomes;
}

inline int entity_o::mutationRate() const  {
    return  MutationRate;
}

inline void entity_o::setMutationRate(int m)  {
    MutationRate = m;
}

inline void entity_o::setName(const string_o& n)  {
    Name = n;
}

inline const char* entity_o::name() const  {
    return  Name.string();
}

inline int entity_o::uniqueid() const  {
    return  Uniqueid;
}

inline int entity_o::score() const  {
    return  Score;
}

inline long entity_o::runningScore() const  {
    return  RunningScore;
}

inline double entity_o::trscore() const  {
    return  ((double)RunningScore)/((double)Iteration);
}

inline int entity_o::iteration() const  {
    return  Iteration;
}

inline void entity_o::setScore(int s)  {
    Score = s;
}

inline void entity_o::inRunningScore(int s)  {
    RunningScore+=s;
}

inline void* entity_o::object() const  {
    return  Object;
}

inline void entity_o::setObject(void* o)  {
    Object = o;
}

inline int entity_o::generation() const  {
    return  Generation;
}

inline chromosome_o** entity_o::chromosomes()  {
    return  Chromosomes;
}


#endif

/******************************************************************************/
