/**  output_o.cc  **************************************************************

  12.31.1999  Performance Server Library v2.000





changes log
when      who      what
4.28.99   Dan      Creation. 




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "output_o"


output_o::output_o():Socket(-1),Priority(-1),State(OUTPUT_STATE_INVALID)  {}

output_o::output_o(const input_o* input)  {
    if(!input)  {
        State          = OUTPUT_STATE_INVALID;
        Socket         = -1;
        Priority       = -1;
    }
    else  {
        State          = input->state();
        Socket         = input->socket();
        Priority       = input->priority();
        IpAddress      = input->ipAddress();
        *(time_o*)this = *(time_o*)input;
    }
}

output_o::~output_o()  {}


/******************************************************************************/
