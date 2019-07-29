/**  input.cc  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999



changes log
when      who       what
4.28.99   Dan       Creation

*******************************************************************************/


#include "input.h"


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
