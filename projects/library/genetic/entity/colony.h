/**  colony.h  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    DNA Artifical Intellegence Colony Object.




when        who        what
9.27.96     Dan        Creation.
7.29.98     Dan        Added:    Method setSize().
8.2.98      Dan        Added:    setLastGeneration(), lastOperation.
8.9.98      Dan        Added:    Mutation rate.
                       Changed:  StartDate and LastchangeDate type from
                                 int to string_o.

*******************************************************************************/


#ifndef COLONYOBJECT_API
#define COLONYOBJECT_API

#include "string.h"
#include "entity.h"

#define COLONY_OBJECT         "colony_o"
#define COLONY_NAME           "name"
#define COLONY_POPULATION     "population"
#define COLONY_ENTITY         "entity"
#define COLONY_MUTATIONRATE   "mutationrate"
#define COLONY_INFO           "info"
#define COLONY_LASTGENERATION "lastgeneration"
#define COLONY_ORIGINDATE     "origindate"
#define COLONY_CHANGEDATE     "changedate"
#define COLONY_LASTOPERATION  "lastoperation"


#define COLONY_MAX_POPULATION 8192

class colony_o  {
  private:
    string_o  Name;
    int       Population;
//  entity_o** Entities;
    int       MutationRate;
    string_o  Info;
    int       LastGeneration;
    string_o  OriginDate;
    string_o  ChangeDate;
    string_o  LastOperation;

  public:
    colony_o();                                         // Default constructor.
    colony_o(const colony_o&);                          // Copy constructor.
    colony_o(const char*,int,const char*,int,int);  // Colony name, starting
                                                    // colony size, infomation,
                                                    // generation,
                                                    // Mutation Rate.
    virtual  ~colony_o();                           // Destructor.
    colony_o& operator = (const colony_o&);             // Assignment operator.
    void            operator >> (string_o&) const;      // OLP representation.
    void            operator << (const char*);          // Reconstruct.

entity_o** Entities; //!!


    const char* name()            const;
    int         population()      const;
    int         mutationRate()    const;
    const char* info()            const;
    int         lastGeneration()  const;
    const char* originDate()      const;
    const char* changeDate()      const;
    const char* lastOperation()   const;
    void        setPopulation(int);
    void        setMutationRate(int);
    void        setLastGeneration(int);
    void        setOriginDate(const char*);
    void        setChangeDate(const char*);
    void        setLastOperation(const char*);
};


/******************************************************************************/

inline const char* colony_o::name() const  {
    return  Name.string();
}

inline int colony_o::population() const  {
    return  Population;
}

inline int colony_o::mutationRate() const  {
    return  MutationRate;
}

inline const char* colony_o::info() const  {
    return  Info.string();
}

inline int colony_o::lastGeneration() const  {
    return  LastGeneration;
}

inline const char* colony_o::originDate() const  {
    return  OriginDate.string();
}

inline const char* colony_o::changeDate() const  {
    return  ChangeDate.string();
}

inline const char* colony_o::lastOperation() const  {
    return  LastOperation.string();
}

inline void colony_o::setPopulation(int s)  {
    Population = s;
}

inline void colony_o::setMutationRate(int m)  {
    MutationRate = m;
}

inline void colony_o::setOriginDate(const char* cd)  {
    OriginDate = cd;
}

inline void colony_o::setChangeDate(const char* cd)  {
    ChangeDate = cd;
}

inline void colony_o::setLastGeneration(int l)  {
    LastGeneration = l;
}

inline void colony_o::setLastOperation(const char* l)  {
    LastOperation = l;
}


#endif

/******************************************************************************/
