/**  time.h  *******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Time System Resource Abstraction Object.        



changes log
when      who     when
4.29.99   Dan     Creation.
5.4.99    Dan     Added     Method string operator.

*******************************************************************************/


#ifndef TIMEOBJECT_API
#define TIMEOBJECT_API

#include <time.h>

#include "../../lib/string/string.h"


class time_o  {
  private:
    int     SetNanoseconds;
    int     SetSeconds;
    int     Nanoseconds;
    int     Seconds;

  public:
    time_o();                                           // Default constructor.
    time_o(const time_o&);                              // Copy constructor.
   ~time_o();                                           // Default destructor.
    time_o& operator = (const time_o&);                 // Assignment operator.

    void    reset();
    void    adjust();

    int     seconds()       const;
    int     nanoseconds()   const;
};
string_o& operator << (string_o&,const time_o&);


/******************************************************************************/

inline int time_o::nanoseconds() const  {
    return Nanoseconds;
}

inline int time_o::seconds() const  {
    return Seconds;
}


#endif

/******************************************************************************/
