/**  parse_o.h  ****************************************************************

    12.31.1999  Performance Server Library v2.000


    Parse Object.



changes log
when      who       what
4.28.99   Dan       Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ParseOBJECT_API
#define ParseOBJECT_API

#include "string_o.h"
#include "bstree_o.h"

#define Parse_MAX_STRING_LENGTH 65535

class parse_o  {
  private:
    bstree_o<string_o>          parsetree;
    bstreeSearch_o<string_o>    stree;

  public:
    parse_o();
    parse_o(const parse_o&);
    parse_o(const char*);
    virtual ~parse_o();
    parse_o& operator = (const parse_o&);

    void it(const char*, string_o&);
    void it(const char*, int&);
    void it(const char*, long int&);
    void it(const char*, short&);
    void it(const char*, double&);
};


#endif

/******************************************************************************/
