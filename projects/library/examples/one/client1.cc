/**  client1.cc  ***************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Example One.  Client.                                             5.4.99
    Simple Performance Client-Server.


    This example demonostrates the prowess of Performance Server Library
    v2.000 by creating performance client-server communications
    with a minimum of programming and effort.


*******************************************************************************/

#include "string_o.h"                       // Include a minimal set of objects
#include "log_o.h"                          // from the Performance Server
#include "client_o.h"                       // Library v2.000.

log_o   log;        // All objects that do error reporting send the report to
                    // this global log object.  The log object is thread-safe
                    // and prevents one message from cutting off another message
                    // during concurrent thread error reports.  This log can
                    // also be used during debugging and to log non-error
                    // occurances.

                    // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       rcode;
    string_o  rstring;
    string_o  logmsg;
    client_o  client;                   // Instantiate the client object.

    rcode = client.connect("server.ip.net",1999);

    if(rcode)  {                        // Check the error state.
        logmsg << "client reports error " << rcode;
        log << logmsg;
        return rcode;
    }

    client.send("Hello there.");

                                        // Receive the reply!
    while(rstring.length() < 2)  client.recv(rstring);
    logmsg << "received: " << rstring.string();
    log << logmsg;


    client.disconnect();                // Disconnect from the server.
    return 0;
}

/******************************************************************************/
