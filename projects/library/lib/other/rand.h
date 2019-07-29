/**  rand.h  *******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Random Number Abstration Object.


when      who       what
9.24.96   Dan       Creation.

*******************************************************************************/


#ifndef RANDOBJECT_API
#define RANDOBJECT_API


#include <stdlib.h>

class rand_o  {
  private:

  public:
    rand_o();
    rand_o(const rand_o&);
    virtual ~rand_o();
    rand_o&  operator = (const rand_o&);

    int i(int) const;
};


/******************************************************************************/

inline int rand_o::i(int limit) const  {
    return (int)((double)limit*((double)rand()/RAND_MAX));
}


#endif

/******************************************************************************/
