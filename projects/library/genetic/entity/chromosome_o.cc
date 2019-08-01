/**  chromosome_o.cc  **********************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    DNA Artifical Intellegence Chromosome Object.




when        who        what
9.24.96     Dan        Creation.
6.14.98     Dan        Changed:  Object name from chromosome_ to chromosome_o.
            Dan        Added:    Some constructors, genes method.
9.2.99      Dan        Changed:  Using global_o object now.
12.24.99    Dan        Changed:  Object serial definition to OLP.


*******************************************************************************/


#include "chromosome_o.h"


chromosome_o::chromosome_o()  {
    NumberOfGenes = 0;
}

chromosome_o::chromosome_o(int nog)  {
    NumberOfGenes = nog;
    for(int x=0;x<nog;x++)  Genes << '0';//!!!!
}

chromosome_o::chromosome_o(const chromosome_o& c)  {
    NumberOfGenes = c.NumberOfGenes;
    Genes         = c.Genes;
}

chromosome_o::~chromosome_o()  {}

chromosome_o& chromosome_o::operator = (const chromosome_o& h)  {
    NumberOfGenes = h.NumberOfGenes;
    Genes         = h.Genes;
    return *this;
}


void chromosome_o::reverse()  {
    Genes.reverse();
}

int chromosome_o::cut(int place)  {
    return Genes.cut(place);
}

int chromosome_o::upcut(int place)  {
    return Genes.upcut(place);
}

int chromosome_o::splice(int place,int length)  {
    Genes.upcut(place);
    Genes.cut(length);
    return numberOfGenes();
}

int chromosome_o::append(const chromosome_o& attament)  {
    Genes << attament.Genes;
    return numberOfGenes();
}


void chromosome_o::display(string_o& s,int n) const  {
    string_o t(Genes);
    t.cut(n);
    s << numberOfGenes() << ' ' << t;
}

void chromosome_o::setGene(int n,char v)  {
    int x;
    if(n < 0 || n > CHROMOSOME_MAX_NUMBER_OF_GENES)  return;
    if(Genes.length() < n)  {
        for(x=0;x<n;x++)  Genes << '0';
    }
    if(n+1 > NumberOfGenes)  NumberOfGenes = n+1;
    Genes << '0';

    Genes.setCharat(n,v);
}

void chromosome_o::operator << (const char* cc)  {
    string_o s(cc);
    s.upcut(CHROMOSOME_OBJECT);
    s.upcut(CHROMOSOME_NUMBER_OF_GENES);
    s.upcut('=');
    NumberOfGenes = s.stoi();
    if(NumberOfGenes > CHROMOSOME_MAX_NUMBER_OF_GENES)
        NumberOfGenes = CHROMOSOME_MAX_NUMBER_OF_GENES;

    s.upcut(CHROMOSOME_GENES);
    s.upcut('=');
    s.cut(NumberOfGenes);

    Genes = s;
}

void chromosome_o::operator >> (string_o& s) const  {
    s << '\n' << CHROMOSOME_OBJECT << ':';
    s << '\n' << CHROMOSOME_NUMBER_OF_GENES << '=' << NumberOfGenes;
    s << '\n' << CHROMOSOME_GENES << '=' << Genes;
    s << '\n';
}


/******************************************************************************/
