/**  input_o.cc  ***************************************************************

  12.31.1999  Performance Server Library v2.000





changes log
when      who       what
4.28.99   Dan       Creation




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "input_o"


input_o::input_o():Socket(-1),Priority(-1),State(CLIENT_STATE_INVALID)  {}

input_o::input_o(int s):Socket(s),Priority(-1),State(CLIENT_STATE_VALID)  {}

input_o::~input_o()  {}

input_o& input_o::operator = (const input_o& i)  {
    State       = i.State;
    Socket      = i.Socket;
    Priority    = i.Priority;
    Message     = i.Message;
    IpAddress   = i.IpAddress;
    return *this;
}

void input_o::clear()  {
    State       = CLIENT_STATE_INVALID;
    Socket      = -1;
    Priority    = -1;
    Message     = "";
    IpAddress   = "";
}


/******************************************************************************/
