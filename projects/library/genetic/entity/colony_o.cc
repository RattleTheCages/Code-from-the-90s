/**  colony_o.cc  **************************************************************

    12.31.1999  Performance Server Library v2.000



    DNA Artifical Intellegence Colony Object.




when        who        what
6.27.98     Dan        Creation.
6.29.98     Dan        Added:    Constructor colony_o(const colony_o&).
8.9.98      Dan        Added:    Mutation rate.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "parse_o"
#include "file_o"
#include "colony_o"


colony_o::colony_o()  {
    Population      = 0;
    MutationRate    = 0;
    LastGeneration  = 0;
    OriginDate      = "0.0.00";
    ChangeDate      = "0.0.00";
    LastOperation   = "null";

    Entities = new entity_o*[COLONY_MAX_POPULATION];
    for(int x=0;x<COLONY_MAX_POPULATION;x++)  {
        Entities[x] = NULL;
    }
}

colony_o::colony_o(const char* name, int size, const char* info, int generation, int mr)  {
    Name            = name;
    Population      = size;
    MutationRate    = mr;
    Info            = info;
    LastGeneration  = generation;
    OriginDate      = "0.0.00";
    ChangeDate      = "0.0.00";
    LastOperation   = "constructor";

    Entities = new entity_o*[Population];
    for(int x=0;x<Population;x++)  {
        Entities[x] = NULL;
    }
}

colony_o::~colony_o()  {}

entity_o* colony_o::get(int uniqueId)  {
    for(int x=0; x<Population; x++)  {
        if(Entities[x]->uniqueid() == uniqueId)  return Entities[x];
    }
    return  NULL;
}

void colony_o::load(const string_o& filename)  {
    string_o colonyString;
    file_o file;
    file.read(filename, colonyString);
    *this << colonyString.string();
}

void colony_o::unload(const string_o& filename)  {
    string_o colonyString;
    file_o file;
    *this >> colonyString;
    file.write(filename, colonyString);
}

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
    s << '\n' << COLONY_POPULATION << '=' << Population;
    for(x=0;x<Population;x++)  {
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
