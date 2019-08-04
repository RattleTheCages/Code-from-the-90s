/**  time_o.cc  ****************************************************************

    12.31.1999  Performance Server Library v2.000



    Time System Resource Abstraction Object.



changes log
Date      who     what
4.29.99   Dan     Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include "time_o"


time_o::time_o()  {
    time_t t;
    ::time(&t);
    SetNanoseconds = 0;
    SetSeconds     = t;
    Nanoseconds    = 0;
    Seconds        = 0;
}

time_o::~time_o()  {}

time_o& time_o::operator = (const time_o& t)  {
    SetNanoseconds = t.SetNanoseconds;
    SetSeconds     = t.SetSeconds;
    Nanoseconds    = t.Nanoseconds;
    Seconds        = t.Seconds;
    return *this;
}

void time_o::reset()  {
    time_t t;
    ::time(&t);
    SetNanoseconds = 0;
    SetSeconds     = t;
    Nanoseconds    = 0;
    Seconds        = 0;
}

void time_o::adjust()  {
    time_t t;
    ::time(&t);
    Nanoseconds = 0;
    Seconds     = t - SetSeconds;
}

string_o& operator << (string_o& s, const time_o& t)  {
    s << "time_o: " << t.seconds() << '.' << t.nanoseconds() << ": ";
    return s;
}


/******************************************************************************/
