/**  log.cc  *******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman





changes log
when     who      what
4.29.99  Dan      Creation.
5.2.99   Dan      Added:    Debug levels to log.


*******************************************************************************/


#include <iostream.h>
#include "../log/log.h"

log_o::log_o(): mutex("log_o"), Toggle(1)  {
    unsigned int x;
    for(x=0;x<LOG_MAX_DEBUG_LEVEL;x++)  Debug[x] = 0;
}

log_o::~log_o()  {}

void log_o::commitLog(const string_o& entry)  {
    string_o s;
    if(!Toggle)  return;
    if(entry.length() > 0 && entry.charat(entry.length()-1) == '\n')  {
        s << entry;
        s.cut(s.length()-1);
        mutex.lock("commitLog()");
            cout << s.string() << endl;
        mutex.unlock("commitLog()");
    }
    else  {
        mutex.lock("commitLog()");
            cout << entry.string() << endl;
        mutex.unlock("commitLog()");
    }
}

void log_o::commitError(const string_o& entry)  {
    string_o s;
    if(entry.length() > 0 && entry.charat(entry.length()-1) == '\n')  {
        s << entry;
        s.cut(s.length()-1);
        mutex.lock("commitError()");
            cerr << s.string() << endl;
        mutex.unlock("commitError()");
    }
    else  {
        mutex.lock("commitError()");
            cerr << entry.string() << endl;
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
    return Toggle;
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
