/**  output_o.h  ***************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999


    Output Data Object.




changes log
when      who       what
4.28.99   Dan       Creation
5.3.99    Dan       Changed:  Argument to method setMessage.
9.9.99    Dan       Added:    Meathod setInvalidCode(int).


*******************************************************************************/


#ifndef OutputOBJECT_API
#define OutputOBJECT_API

#include "string_o.h"
#include "time_o.h"
#include "input_o.h"

#define OUTPUT_STATE_INVALID           0
#define OUTPUT_STATE_VALID             1
#define OUTPUT_STATE_12STAR_PROTOCOL  12


class output_o: public time_o  {
  private:
    int         State;
    int         Socket;
    int         Priority;
    string_o    IpAddress;
    string_o    Message;

  public:   
    output_o();                                 // Default constructor.
    output_o(const output_o&);                  // Copy constructor.
    output_o(const input_o*);
    virtual  ~output_o();                       // Default destructor.
    output_o& operator = (const output_o&);     // Assignment operator.

    int             state()           const;
    int             socket()          const;
    int             priority()        const;
    const char*     ipAddress()       const;
    const string_o& message()         const;

    void            setState(int);
    void            setMessage(const string_o&);

};


/******************************************************************************/

inline int output_o::state() const  {
    return  State;
}

inline int output_o::socket() const  {
    return  Socket;
}

inline int output_o::priority() const  {
    return  Priority;
}

inline const char* output_o::ipAddress() const  {
    return  IpAddress.string();
}

inline const string_o& output_o::message() const  {
    return  Message;
}

inline void output_o::setState(int s)  {
    State = s;
}

inline void output_o::setMessage(const string_o& m)  {
    Message = m;
}


#endif

/******************************************************************************/
