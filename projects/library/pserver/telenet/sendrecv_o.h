/**  sendrecv_o.h  *************************************************************

    12.31.1999  Performance Server Library v2.000


    Send Recv Object.


changes log
when      who       what
4.28.99   Dan       Creation


                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef SendRecvOBJECT_API
#define SendRecvOBJECT_API

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "string_o"
#include "error_o"


class sendrecv_o: public error_o  {
  protected:
    long int  recv(int,char*,long int);// Receive a memory block over a socket.
    long int  send(int,const char*,long int);
                                       // Send a memory block over a socket.
                                       // int-   socket descriptor.
                                       // char*- memory block address.
                                       // int-   number of bytes to be sent.
                                       // Return the actual number of bytes
                                       // sent or received.

  public:
    sendrecv_o();                                       // Default constructor.
    sendrecv_o(const sendrecv_o&);                      // Copy constructor.
    virtual    ~sendrecv_o();                           // Default destructor.
    sendrecv_o& operator = (const sendrecv_o&);         // Assignment operator.



    long int   send(int,const string_o&);   // Send given string_o.
    long int   recv(int,string_o&);         // Receive a string_o into given.
                                       // The send and recv methods return the
                                       // number of bytes actually sent or
                                       // received.
long int   recvC(int,string_o&);         // Receive a string_o into given.
int        close(int);
};


#endif

/******************************************************************************/
