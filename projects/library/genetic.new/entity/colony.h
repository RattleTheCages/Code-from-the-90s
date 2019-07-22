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

#include "../../lib/string/string.h"
#include "../../lib/thread/queue.h"
#include "../entity/entity.h"

#define COLONY_OBJECT         "colony_o"
#define COLONY_NAME           "name"
#define COLONY_ID             "id"
#define COLONY_MUTATIONRATE   "mutationrate"
#define COLONY_INFO           "info"
#define COLONY_LASTGENERATION "lastgeneration"
#define COLONY_ORIGINDATE     "origindate"
#define COLONY_CHANGEDATE     "changedate"
#define COLONY_LASTOPERATION  "lastoperation"
#define COLONY_POPULATION     "population"
#define COLONY_ENTITY         "entity"



class colony_o  {
  private:
    string_o  Name;
    string_o  Id;
    int       MutationRate;
    string_o  Info;
    int       Generation;
    string_o  OriginDate;
    string_o  ChangeDate;
    string_o  LastOperation;
    queue_o<entity_o> Entities;

  public:
    colony_o();                                         // Default constructor.
    colony_o(const colony_o&);                          // Copy constructor.
    colony_o(const char*,const char*,const char*,int,int);  // Colony name, starting
                                                    // colony size, infomation,
                                                    // generation,
                                                    // Mutation Rate.
   ~colony_o();                                         // Destructor.
    colony_o& operator = (const colony_o&);             // Assignment operator.
    void            operator >> (string_o&) const;      // OLP representation.
    void            operator << (const char*);          // Reconstruct.

    const char* name()            const;
    const char* id()              const;
    int         population()      const;
    int         mutationRate()    const;
    const char* info()            const;
    int         generation()      const;
    const char* originDate()      const;
    const char* changeDate()      const;
    const char* lastOperation()   const;
    void        setMutationRate(int);
    void        incrementGeneration();
    void        setChangeDate(const char*);
    void        setLastOperation(const char*);
    void        addEntity(entity_o*);
};


/******************************************************************************/

inline const char* colony_o::name() const  {
    return Name.string();
}

inline const char* colony_o::id() const  {
    return Id.string();
}

inline int colony_o::population() const  {
    return Entities.cardinality();
}

inline int colony_o::mutationRate() const  {
    return MutationRate;
}

inline const char* colony_o::info() const  {
    return Info.string();
}

inline int colony_o::generation() const  {
    return Generation;
}

inline const char* colony_o::originDate() const  {
    return OriginDate.string();
}

inline const char* colony_o::changeDate() const  {
    return ChangeDate.string();
}

inline const char* colony_o::lastOperation() const  {
    return LastOperation.string();
}

inline void colony_o::setMutationRate(int m)  {
    MutationRate = m;
}

inline void colony_o::setChangeDate(const char* cd)  {
    ChangeDate = cd;
}

inline void colony_o::incrementGeneration()  {
    Generation++;
}

inline void colony_o::setLastOperation(const char* l)  {
    LastOperation = l;
}


#endif

/******************************************************************************/
