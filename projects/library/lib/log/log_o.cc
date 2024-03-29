/**  log_o.cc  *****************************************************************

    12.31.1999  Performance Server Library v2.000


    Log Object Implementation.




changes log
when     who      what
4.29.99  Dan      Creation.
5.2.99   Dan      Added:    Debug levels to log.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include <iostream>
#include "log_o"

log_o::log_o(): mutex("log_o"), Toggle(1)  {
    for(unsigned int x=0;x<LOG_MAX_DEBUG_LEVEL;x++)  Debug[x] = 0;
}

log_o::~log_o()  {}

void log_o::commitLog(const string_o& entry)  {
    string_o s;
    if(!Toggle)  return;
    if(entry.length() > 0 && entry.charat(entry.length()-1) == '\n')  {
        s << entry;
        s.cut(s.length()-1);
        mutex.lock("commitLog()");
            std::cout << s.string() << std::endl;
        mutex.unlock("commitLog()");
    }
    else  {
        mutex.lock("commitLog()");
            std::cout << entry.string() << std::endl;
        mutex.unlock("commitLog()");
    }
}

void log_o::commitError(const string_o& entry)  {
    string_o s;
    if(entry.length() > 0 && entry.charat(entry.length()-1) == '\n')  {
        s << entry;
        s.cut(s.length()-1);
        mutex.lock("commitError()");
            std::cerr << s.string() << std::endl;
        mutex.unlock("commitError()");
    }
    else  {
        mutex.lock("commitError()");
            std::cerr << entry.string() << std::endl;
        mutex.unlock("commitError()");
    }
}

void log_o::error(const char* cc)  {
    string_o entry;
    if(Name.length() > 0)  entry << Name.string() << ": ";
    entry << cc << '\n';
    commitError(entry);
}

void log_o::error(const string_o& s)  {
    error(s.string());
}

void log_o::registerName(const char* cc)  {
    Name = cc;
}

int log_o::toggle()  {
    Toggle = (Toggle+1) % 2;
    return  Toggle;
}

void log_o::operator << (const char* cc)  {
    string_o entry;
    if(!Toggle)  return;
    if(Name.length() > 0)  entry << Name.string() << ": ";
    entry << cc << '\n';
    commitLog(entry);
}

void log_o::operator << (const string_o& ls)  {
    *this << ls.string();
}


/******************************************************************************/
