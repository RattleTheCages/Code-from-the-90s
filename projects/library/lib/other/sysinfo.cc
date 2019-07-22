/**  sysinfo.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




changes log
Date      who      what
4.29.99   Dan      Creation.

*******************************************************************************/


#include <unistd.h>
#include <time.h>
#include "../../lib/other/sysinfo.h"

sysinfo_o::sysinfo_o()  {
    NumberOfCpus                 = 1;
    ThreadCeiling                = 512;

    Pid    = ::getpid();
}

sysinfo_o::~sysinfo_o()  {}

void sysinfo_o::currentTime(string_o& s) const  {
    char*  b;
    time_t time;
    time = ::time(NULL);
    b = ::ctime(&time);
    s << b;
    s.transpose("\n","\0");
}

int sysinfo_o::currentYear() const  {
    time_t time;
    struct tm* t;
    time = ::time(NULL);
    t = ::localtime(&time);
    return t->tm_year+1900;
}

int sysinfo_o::currentMonth() const  {
    time_t time;
    struct tm* t;
    time = ::time(NULL);
    t = ::localtime(&time);
    return t->tm_mon;
}

int sysinfo_o::currentDay() const  {
    time_t time;
    struct tm* t;
    time = ::time(NULL);
    t = ::localtime(&time);
    return t->tm_mday;
}


/******************************************************************************/
