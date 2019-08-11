/**  thread_o.h  ***************************************************************

    08.08.1999  Performance Server Library v2.000           (The Lost Episodes.)


    File Abstraction Object.





                          Copyright  2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef FileOBJECT_API
#define FileOBJECT_API

#include "string_o"
#include "error_o"


class file_o: public error_o  {
  private:

  public:
    file_o();
    file_o(const file_o&);
    virtual  ~file_o();
    file_o& operator = (const file_o&);

    int read(const string_o&, string_o&);
    int write(const string_o&, const string_o&);
};
string_o& operator << (string_o&, const file_o&);


/******************************************************************************/



#endif

/******************************************************************************/
