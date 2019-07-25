/**  colony.cc  ****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    DNA Artifical Intellegence Colony Object.




when        who        what
6.27.98     Dan        Creation.
6.29.98     Dan        Added:    Constructor colony_o(const colony_o&).
8.9.98      Dan        Added:    Mutation rate.

*******************************************************************************/


#include "parse.h"
#include "colony.h"


colony_o::colony_o()  {
    int x;

    MutationRate    = 0;
    Generation      = 0;
    OriginDate      = "0.0.00";
    ChangeDate      = "0.0.00";
    LastOperation   = "null";
}

colony_o::colony_o(const char* name,const char* id,const char* info,int size,int mr,int numberOfChromosomes,int numberOfGenes)  {
    int x;

    Name            = name;
    Id              = id;
    MutationRate    = mr;
    Info            = info;
    LastGeneration  = generation;
    OriginDate      = "0.0.00";
    ChangeDate      = "0.0.00";
    LastOperation   = "constructor";

    for(x=0;x<size;x++)
        Entities.put(new entity_o(name,1000,100,MutationRate,numberOfChromosomes,numberOfGenes);
}

colony_o::~colony_o()  {}


void colony_o::operator >> (string_o& s) const  {
    long int x;
    string_o t;

    s << '\n' << COLONY_OBJECT << ':';
    s << '\n' << COLONY_NAME << '=' << Name;
    s << '\n' << COLONY_INFO << '=' << Info;
    s << '\n' << COLONY_LASTGENERATION << '=' << LastGeneration;
    s << '\n' << COLONY_ORIGINDATE << '=' << OriginDate;
    s << '\n' << COLONY_CHANGEDATE << '=' << ChangeDate;
    s << '\n' << COLONY_LASTOPERATION << '=' << LastOperation;
    s << '\n' << COLONY_MUTATIONRATE << '=' << MutationRate;
    s << '\n' << COLONY_POPULATION << '=' << population();
    for(x=0;x<population();x++)  {
        t = "";
        *Entities[x] >> t;
        s << '\n' << COLONY_ENTITY << '[' << x << "]=" << t;
    }
}

void colony_o::operator << (const char* cc)  {
    int x;
    string_o s,t;
    parse_o parse(cc);

    (void)parse.it(COLONY_NAME,Name);
    (void)parse.it(COLONY_INFO,Info);
    (void)parse.it(COLONY_LASTGENERATION,LastGeneration);
    (void)parse.it(COLONY_ORIGINDATE,OriginDate);
    (void)parse.it(COLONY_CHANGEDATE,ChangeDate);
    (void)parse.it(COLONY_LASTOPERATION,LastOperation);
    (void)parse.it(COLONY_MUTATIONRATE,MutationRate);
    (void)parse.it(COLONY_POPULATION,Population);
    for(x=0;x<Population;x++)  {
        s = cc;
        t = COLONY_ENTITY;
        t << '[' << x << "]=\n";
        s.upcut(t.string());
        s.cut("\n\n\n");


        Entities[x] = new entity_o(s.string());
    }

}


/******************************************************************************/
