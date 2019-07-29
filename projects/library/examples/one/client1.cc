/**  client1.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Example One.  Client.                                             5.4.99
    Simple Performance Client-Server.


    This example demonostrates the prowess of Performance Server Library
    v2.000 by creating performance client-server communications
    with a minimum of programming and effort.


*******************************************************************************/

#include <iostream>
#include "string.h"                         // Include a minimal set of objects
#include "log.h"                            // from the Performance Server
#include "../../sserver/telenet/client.h"   // Library v2.000.

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
    client_o  client;                   // Instantiate the client object.

    rcode = client.connect("server.ip.net",1999);

    if(rcode)  {                        // Check the error state.
        std::cerr << "client reports error " << rcode << std::endl;
        return rcode;
    }

    client.send("Hello there.");


    client.recv(rstring);               // Receive the reply!
    std::cout << "recving: " << rstring.string() << std::endl;


    client.disconnect();                // Disconnect from the server.
    return 0;
}

/******************************************************************************/
