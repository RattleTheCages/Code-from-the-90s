/**  client.h  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999




    Client Object.

log_o debug levels
251 - Connect and disconnect.
252 - Send and receive.


changes log
when      who       what
5.3.99    Dan       Creation
9.9.99    Dan       Changed:  Since ::gethostbyname does not work in a threaded
                                    program, now only accept IP address, and
                                    removed any use of netdb.h.

*******************************************************************************/


#ifndef CLIENTOBJECT_API
#define CLIENTOBJECT_API

#include <sys/types.h>
#include <sys/socket.h>

#include "string.h"
#include "sendrecv.h"

#define CLIENT_MAX_PORT         32767
#define CLIENT_CONNECTED            1
#define CLIENT_NOT_CONNECTED        0


class client_o: public sendrecv_o  {
  protected:
    int                 State;
    string_o            IPAddress;

    int                 Socket;
    int                 Port;
    struct sockaddr_in  server;

  public:
    client_o();                                     // Default constructor.
    client_o(const client_o&);                      // Copy constructor.
    virtual  ~client_o();                           // Default destructor.
    client_o& operator = (const client_o&);         // Assignment operator.

    int          connect(const char*, int);         // Connect to given server
                                                    // using given int as port.
    int          disconnect();                      // Disconnect from server.
    long int     send(const string_o&);             // Send given string.
    long int     send(const char*, long int);

    long int     recv(string_o&);                   // Receive string.
    long int     recv(char*, long int);

    int          state()  const;                    // Return client state.
    int          socket() const;                    // Return socket number.
    int          port()   const;                    // Return port number.
    const char*  ip()     const;                    // Return server connected.

};


/******************************************************************************/

inline int client_o::state() const  {
    return  State;
}

inline int client_o::socket() const  {
    return  Socket;
}

inline int client_o::port() const  {
    return  Port;
}

inline const char* client_o::ip() const  {
    return  IPAddress.string();
}


#endif

/******************************************************************************/
