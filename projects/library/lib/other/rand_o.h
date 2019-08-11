/**  rand_o.h  *****************************************************************

    12.31.1999  Performance Server Library v2.000



    Random Number Abstration Object.


when      who       what
9.24.96   Dan       Creation.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef RandOBJECT_API
#define RandOBJECT_API


#include "thread_o"
#include "queue_o"
#include "mutex_o"


class rand_o : protected thread_o  {
  private:
    int srandSet;
    mutex_o condition;
    queue_o<int> randomNumbers;
    queue_o<int> recycleNumbers;

  public:
    rand_o();
    rand_o(const rand_o&);
    virtual ~rand_o();
    rand_o&  operator = (const rand_o&);

    int i(int);

    void threadLoop();
};


/******************************************************************************/

/*
inline int rand_o::i(int limit)  {
    return (int)((double)limit*((double)rand()/RAND_MAX));
}
*/


#endif

/******************************************************************************/
