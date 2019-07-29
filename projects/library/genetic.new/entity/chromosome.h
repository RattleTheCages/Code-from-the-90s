/**  chromosome.h  *************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    DNA Artifical Intellegence Chromosome Object.



when        who        what
9.24.96     Dan        Creation.
6.14.98     Dan        Changed:  Object name from chromosome_ to chromosome_o.
                                 Moved genes object to private.
            Dan        Added:    Some constructors, genes method.
6.15.98     Dan        Added:    Constructor chromosome_o(rand_o&).
9.2.99      Dan        Removed:  Constructor chromosome_o(rand_o&), and rand_o
                                 object from data members.
12.24.99    Dan        Changed:  Object serial definition to OLP.

*******************************************************************************/


#ifndef CHROMOSOMEOBJECT_API
#define CHROMOSOMEOBJECT_API


#include "../../lib/string/string.h"


#define CHROMOSOME_OBJECT          "chromosome_o"
#define CHROMOSOME_NUMBER_OF_GENES "numofgenes"
#define CHROMOSOME_GENES           "genes"

#define CHROMOSOME_MAX_NUMBER_OF_GENES 16384


class chromosome_o  {
  private:
    int      NumberOfGenes;
    string_o Genes;

  public:
    chromosome_o();                                     // Default constructor.
    chromosome_o(int);
    chromosome_o(const chromosome_o&);                  // Copy constructor.
   ~chromosome_o();                                     // Default destructor.
    chromosome_o&   operator = (const chromosome_o&);   // Assignment operator.
    void            operator >> (string_o&) const;      // OLP representation.
    void            operator << (const char*);          // Reconstruct from OLP.


    int     numberOfGenes()         const;
    void    display(string_o&,int)  const;
    char    operator [](int)        const;

    void    setGene(int,char);

    void    reverse();

    void    crossover(chromosome_o*);

};

/******************************************************************************/

inline int chromosome_o::numberOfGenes() const  {
    return NumberOfGenes;
}

inline char chromosome_o::operator [](int index) const  {
    if(index < 0 || index > numberOfGenes())  return '0';
    return Genes.charat(index);
}


#endif

/******************************************************************************/
