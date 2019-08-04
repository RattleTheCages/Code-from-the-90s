/**  rand_o.h  *****************************************************************

    12.31.1999  Performance Server Library v2.000



    Random Number Abstration Object.


when      who       what
9.24.96   Dan       Creation.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef RandOBJECT_API
#define RandOBJECT_API


#include <stdlib.h>

class rand_o  {
  private:

  public:
    rand_o();
    rand_o(const rand_o&);
    virtual ~rand_o();
    rand_o&  operator = (const rand_o&);

    static int i(int);
};


/******************************************************************************/

inline int rand_o::i(int limit)  {
    return (int)((double)limit*((double)rand()/RAND_MAX));
}


#endif

/******************************************************************************/
