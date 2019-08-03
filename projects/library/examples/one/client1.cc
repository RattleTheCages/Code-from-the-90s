/**  client1.cc  ***************************************************************

    12.31.1999  Performance Server Library v2.000



    Example One.  Client.                                             5.4.99
    Simple Performance Client-Server.


    This example demonostrates the prowess of Performance Server Library
    v2.000 by creating performance client-server communications
    with a minimum of programming and effort.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/

#include "string_o"                         // Include a minimal set of objects
#include "log_o"                            // from the Performance Server
#include "client_o"                         // Library v2.000.

log_o   log;        // All objects that do error reporting send the report to
                    // this global log object.  The log object is thread-safe
                    // and prevents one message from cutting off another message
                    // during concurrent thread error reports.  This log can
                    // also be used during debugging and to log non-error
                    // occurances.


int main(int argc, char* argv[])  {
    int       rcode;
    string_o  rstring;
    string_o  logmsg;
    client_o  client;                   // Instantiate the client object.

    rcode = client.connect("server.ip.net", 1999);

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
