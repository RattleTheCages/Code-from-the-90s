/**  reproduce_o.h  ************************************************************

    12.31.1999  Performance Server Library v2.000



    DNA Artifical Intellegence Entity Reproduction Process Object.




when      who     what
6.29.98   Dan     Creation.
7.14.98   Dan     Added:  Method threadloop.
8.2.98    Dan     Changed:  Inherit an Entity Object now.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ReproduceOBJECT_API
#define ReproduceOBJECT_API


#include "queue_o"
#include "colony_o"
#include "entity_o"


class reproduce_o/*: public entity_o*/  {
  private:
    queue_o<entity_o> newentities;

    queue_o<void> reproduceQueue;

  private:
    int                 Generation;
    const entity_o*     GuestEntity;

  public:
    reproduce_o();                                      // Default constructor.
    reproduce_o(const reproduce_o&);                    // Copy constructor.
    reproduce_o(entity_o*,const entity_o&,int);
    virtual     ~reproduce_o();                         // Default destructor.
    reproduce_o& operator = (const reproduce_o&);       // Assignment operator.


    void threadloop();
};


#endif

/******************************************************************************/
