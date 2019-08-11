/**  file_o.cc  ****************************************************************

    08.08.2019  Performance Server Library v2.000           (The Lost Episodes.)

    Thread Abstraction Object.




changes log
when      who     what
4.29.99   Dan     Creation.
9.9.99    Dan     Added:    Method usleep().
10.5.99   Dan     Added:    Method int start(void*,void*).




                           Copyright 2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include <fstream>
#include "file_o"
#include "log_o"

extern log_o log;

file_o::file_o()  {}

file_o::~file_o()  {}


int file_o::read(const string_o& filename, string_o& s)  {
    int x;
    string_o ls;
    std::ifstream in;
    char buffer[8096];
    in.open(filename.string());
    if(!in)  {
        (ls = "") << "File not found: " << filename;
        log.error(ls);
        return  -1;
    }

    while(!in.eof())  {
        for(x = 0; x<8096; x++)  {
            in.get(buffer[x]);
            if(in.eof())  break;
        }
        s.fill(x, buffer);
    }
    in.close();

}

int file_o::write(const string_o& filename, const string_o& s)  {
    std::ofstream out(filename.string());
    out << s.string();
    out.close();
}


string_o& operator << (string_o& s, const file_o& file)  {
    s << /*file.name() <<*/ "file_o: ";
    return  s;
}


/******************************************************************************/
