/**  server_o.h  ***************************************************************

  12.31.1999  Performance Server Library v2.000


    Server Object.


211 - Listen.
212 - Disconnect.
213 - Accept.
214 - Send.
215 - Recv.



changes log
when      who       when
4.28.99   Dan       Creation


                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ServerOBJECT_API
#define ServerOBJECT_API

#include "string_o.h"
#include "sendrecv_o.h"


class server_o: public sendrecv_o  {
  protected:
    int                 Socket;
    int                 Accept;
    int                 Port;
    struct sockaddr_in  server;
    struct sockaddr     client;
    struct hostent*     chost;
    struct linger       linger;

    string_o            ClientIp;
    string_o            ClientHost;

  public:   
    server_o();                             // Default constructor.
    server_o(const server_o&);              // Copy constructor.
    server_o(int);                          // Opens a listen socket on the
                                            // given int as a port.
    virtual  ~server_o();                   // Closes the listen socket.
    server_o& operator = (const server_o&); // Assignment operator. 

    int         accept();             // Blocks until a connection from a
                                      // client is established.  Returns
                                      // the client accept socket.

    int         close(int);           // Closes the given accept socket.

    int         send(const string_o&);// Sends given string_o to the client.
                                      // Returns the number of bytes sent.
    int         send(int,const string_o&);
                                      // Sends given string_o to the client
                                      // connected to by the given socket.
                                      // Returns the number of bytes sent.
    int         recv(string_o&);      // Receives a message from the client and
                                      // appends it to the given string_o.

    int         port()       const;   // Return the port number this server is
                                      // listening to.
    const char* clientIp()   const;   // Returns the client's ip address.
    const char* clientHost() const;   // Returns the client's host name.

};


/******************************************************************************/

inline int server_o::port() const  {
    return  Port;
}

inline const char* server_o::clientIp() const  {
    return  ClientIp.string();
}

inline const char* server_o::clientHost() const  {
    return  ClientHost.string();
}


#endif

/******************************************************************************/
