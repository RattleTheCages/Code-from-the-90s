/**  carapace_o.h  **************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman


    Carapace Object.

    Inhert and overload this object to provide unique server functionality.


changes log
when      who       what
4.28.99   Dan       Creation
9.9.99    Dan       Changed:  Method process arguments.

*******************************************************************************/


#ifndef CarapaceOBJECT_API
#define CarapaceOBJECT_API

#include "input_o.h"
#include "output_o.h"

class carapace_o  {
  public:
    carapace_o();                                       // Default construtor.
    carapace_o(const carapace_o&);                      // Copy constructor.
    virtual    ~carapace_o();                           // Default destrutor.
    carapace_o& operator = (const carapace_o&);         // Assignment operator.

    virtual int process(input_o&,output_o&);
};


#endif

/******************************************************************************/
