/**  input.h  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999


    Input Object.


changes log
when      who     what
4.28.99   Dan     Creation. 


*******************************************************************************/


#ifndef INPUTOBJECT_API
#define INPUTOBJECT_API

#include "string.h"
#include "time.h"

#define CLIENT_STATE_INVALID           0
#define CLIENT_STATE_VALID             1
#define CLIENT_STATE_12STAR_PROTOCOL  12

class input_o: public time_o  {
  protected:
    int       State;
    int       Socket;
    int       Priority;
    string_o  IpAddress;
    string_o  Message;

  public:   
    input_o();                                      // Default constructor.
    input_o(const input_o&);                        // Copy constructor.
    input_o(int);                                   // Socket given.
    virtual    ~input_o();                          // Default destructor.
    input_o&    operator = (const input_o&);        // Assignment operator.
    void        clear();                            // Reset fields.

    int         state()                 const;
    int         socket()                const;
    int         priority()              const;
    const char* ipAddress()             const;
    string_o&   message();

    void        setState(int);
    void        setSocket(int);
    void        setPriority(int);
    void        setMessage(const char*);
};


/******************************************************************************/

inline int input_o::state() const  {
    return  State;
}

inline int input_o::socket() const  {
    return  Socket;
}

inline int input_o::priority() const  {
    return  Priority;
}

inline const char* input_o::ipAddress() const  {
    return  IpAddress.string();
}

inline string_o& input_o::message()  {
    return  Message;
}


inline void input_o::setState(int s)  {
    State = s;
}

inline void input_o::setSocket(int socket)  {
    Socket = socket;
}

inline void input_o::setPriority(int p)  {
    Priority = p;
}

inline void input_o::setMessage(const char* me)  {
    Message = me;
}


#endif

/******************************************************************************/
