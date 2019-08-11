/**  traits_o.h  **************************************************************

    08.08.2019  Performance Server Library v2.000          (The Lost Episodes.)


    Traits interpreter interface.



    DNA Artifical Intellegence Interperter Object.





                           Copyright 2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef TraitsOBJECT_API
#define TraitsOBJECT_API


#include "string_o"
#include "entity_o"


class traits_o  {
  private:

  public:
    traits_o();
    traits_o(const traits_o&);
    virtual    ~traits_o();
    traits_o&   operator = (const traits_o&);
    void        operator >> (string_o&) const;      // OLP representation.
    void        operator << (const char*);          // Reconstruct from OLP.

    int         operator [](int) const;

    int         trait(int,  entity_o&);

};

/******************************************************************************/



#endif

/******************************************************************************/
