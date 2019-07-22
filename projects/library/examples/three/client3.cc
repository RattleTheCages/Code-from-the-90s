/**  client3.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Example Three.  Client.                                           5.9.99
    Taking care of shared memory.
    

*******************************************************************************/


#include "../../lib/string/string.h"        // Include a minimal set of objects
#include "../../lib/cron/time.h"            // from the Performance Server
#include "../../lib/log/log.h"              // Library v2.000.
#include "../../sserver/telenet/client.h"   // Include the Client Object.

log_o   log;    // All objects that do error reporting send the report to this
                // global log object.  The log object is thread-safe and
                // prevents one message from cutting off another message
                // during concurrent thread error reports.  This log can also
                // be used during debugging and to log non-error occurrences.

    // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       rcode;
    string_o  sstring;
    string_o  rstring;
    client_o  client;                   // Instantiate the client object.

    rcode = client.connect(argv[1],6603);
                                        // Ask for a connection to the server
                                        // name given as the first argument on
                                        // the command line.  Ask to use port
                                        // 6603 to establish the connection.

    if(rcode)  return rcode;            // Check the error state.

                                        // Request for the service name given by
                                        // the second argument of the command
                                        // line.
    sstring << argv[2] << " Requesting Service.";

    client.send(sstring.string());      // Send the service request.

    client.recv(rstring);               // Receive the service reply.
    cout << rstring << endl;

    client.disconnect();                // Disconnect from the server.
    return 0;
}


/******************************************************************************/
