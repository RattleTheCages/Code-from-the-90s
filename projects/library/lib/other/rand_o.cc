/**  rand_o.cc  ****************************************************************

    12.31.1999  Performance Server Library v2.000




changes log
when      who       what
8.24.96   Dan       Creation.
5.2.99    Dan       Changed:  Seeds off of the processes's pid now.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "rand_o.h"
#include "sysinfo_o.h"

extern sysinfo_o sysinfo;

rand_o::rand_o()  {
    (void)::srand(::sysinfo.pid());
}

rand_o::~rand_o()  {}


/******************************************************************************/
