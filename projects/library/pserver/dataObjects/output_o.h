/**  output_o.h  ***************************************************************

  12.31.1999  Performance Server Library v2.000 


    Output Data Object.




changes log
when      who       what
4.28.99   Dan       Creation
5.3.99    Dan       Changed:  Argument to method setMessage.
9.9.99    Dan       Added:    Meathod setInvalidCode(int).




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef OutputOBJECT_API
#define OutputOBJECT_API

#include "string_o"
#include "time_o"
#include "input_o"

#define OUTPUT_STATE_INVALID           0
#define OUTPUT_STATE_VALID             1


class output_o: public time_o  {
  private:
    int         State;
    int         Socket;
    int         Priority;
    string_o    IpAddress;
    string_o    Message;

  public:   
    output_o();
    output_o(const output_o&);
    output_o(const input_o*);
    virtual  ~output_o();
    output_o& operator = (const output_o&);

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
