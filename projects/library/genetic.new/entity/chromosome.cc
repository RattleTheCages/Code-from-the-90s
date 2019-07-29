/**  chromosome.cc  ************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    DNA Artifical Intellegence Chromosome Object.




when        who        what
9.24.96     Dan        Creation.
6.14.98     Dan        Changed:  Object name from chromosome_ to chromosome_o.
            Dan        Added:    Some constructors, genes method.
9.2.99      Dan        Changed:  Using global_o object now.
12.24.99    Dan        Changed:  Object serial definition to OLP.


*******************************************************************************/


#include "rand.h"
#include "chromosome.h"


extern rand_o rndm;

chromosome_o::chromosome_o()  {
    NumberOfGenes = 0;
}

chromosome_o::chromosome_o(int nog)  {
    NumberOfGenes = nog;
    if(nog < 0 || nog > CHROMOSOME_MAX_NUMBER_OF_GENES)
        NumberOfGenes = CHROMOSOME_MAX_NUMBER_OF_GENES;
    for(int x=0;x<NumberOfGenes;x++)  Genes << (char)rndm.i(26)+97;
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

void chromosome_o::crossover(chromosome_o* m)  {
    int smaller;
    int crosspoint;
    string_o ftoppart;
    string_o mtoppart;
    string_o fbotpart;
    string_o mbotpart;

    smaller = numberOfGenes();
    if(m->numberOfGenes() < smaller)  smaller = m->numberOfGenes();
    crosspoint = rndm.i(smaller);

    ftoppart = Genes;
    ftoppart.cut(crosspoint);
    fbotpart = Genes;
    fbotpart.upcut(crosspoint);

    mtoppart = m->Genes;
    mtoppart.cut(crosspoint);
    mbotpart = m->Genes;
    mbotpart.upcut(crosspoint);

    Genes = ftoppart;
    Genes << mbotpart;

    m->Genes = mtoppart;
    m->Genes << fbotpart;
}

void chromosome_o::display(string_o& s,int n) const  {
    string_o t(Genes);
    t.cut(n);
    s << numberOfGenes() << ' ' << t;
}

void chromosome_o::setGene(int n,char v)  {
    if(n < 0 || n >= NumberOfGenes)  return;
    if(v < 'a' || v > 'z')  return;
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
