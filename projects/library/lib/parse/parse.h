/**  parse.h  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Parse Object.


changes log
when      who       what
4.28.99   Dan       Creation.

*******************************************************************************/


#ifndef PARSEOBJECT_API
#define PARSEOBJECT_API

#include "../../lib/string/string.h"
#include "../../lib/memory/bstree.h"

#define PARSE_MAX_STRING_LENGTH 65535

class parse_o  {
  private:
    bstree_o<string_o>          parsetree;
    bstreeSearch_o<string_o>    stree;

  public:
    parse_o();
    parse_o(const parse_o&);
    parse_o(const char*);
   ~parse_o();
    parse_o& operator = (const parse_o&);

    void it(const char*,string_o&);
    void it(const char*,int&);
    void it(const char*,long int&);
    void it(const char*,short&);
    void it(const char*,double&);
};


#endif

/******************************************************************************/
