/**  name_o.cc  ****************************************************************

    12.31.1999  Performance Server Library v2.000






when      who     what
9.24.96   Dan     Creation.
6.22.96   Dan     Changed:  Name of object from name_ to name_o.  Using string_o
                            object now.
7.31.98   Dan     Changed:  Names are now in a const char, not in a file.
                            Removed file i/o.
9.2.99    Dan     Changed:  Using global_o object's rand_o object now.
12.24.99  Dan     Changes:  Not using global object.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "rand_o"
#include "name_o"

extern rand_o rndm;

name_o::name_o()  {}

name_o::~name_o()  {}

const char* name_o::name() const  {
    return Names[rndm.i(NumberOfNames)]; 
}

int name_o::id() const  {
    return rndm.i(9000)+1000;
}


/******************************************************************************/
