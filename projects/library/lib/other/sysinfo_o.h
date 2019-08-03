/**  sysinfo_o.h  **************************************************************

    12.31.1999  Performance Server Library v2.000



    System Information Object.
  
 
changes log
when      who       what
4.29.99   Dan       Creation. 



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef SystemInformationOBJECT_API
#define SystemInformationOBJECT_API

#include "string_o.h"


class sysinfo_o  {
  private:
    int    NumberOfCpus;
    int    ThreadCeiling;
    int    Pid;

  public:   
    sysinfo_o();                                    // Default constructor.
    sysinfo_o(const sysinfo_o&);                    // Copy constructor.
    virtual   ~sysinfo_o();                         // Default destructor.
    sysinfo_o& operator = (const sysinfo_o&);       // Assignment operator.

    int    pid() const;
    int    numberOfCpus() const;
    int    threadCeiling() const;
    void   currentTime(string_o&) const;
    int    currentYear() const;
    int    currentMonth() const;
    int    currentDay() const;
};
string_o& operator << (string_o&, sysinfo_o&);


/******************************************************************************/

inline int sysinfo_o::pid() const  {
    return  Pid;
}

inline int sysinfo_o::numberOfCpus() const  {
    return  NumberOfCpus;
}

inline int sysinfo_o::threadCeiling() const  {
    return  ThreadCeiling;
}


#endif

/******************************************************************************/
