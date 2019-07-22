/**  rand.cc  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




changes log
when      who       what
8.24.96   Dan       Creation.
5.2.99    Dan       Changed:  Seeds off of the processes's pid now.

*******************************************************************************/


#include "../../lib/other/rand.h"
//#include "../../lib/other/sysinfo.h"



//extern sysinfo_o sysinfo;

rand_o::rand_o()  {
//    (void)::srand(::sysinfo.pid());
}

rand_o::~rand_o()  {}


/******************************************************************************/
