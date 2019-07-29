/**  client2.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




    Example Two.  Client.                                             5.4.99
    P is for performance.

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
    int       x;
    int       rcode;
    string_o  message;
    string_o  sstring;
    string_o  rstring;
    time_o    time;
    client_o  client;                   // Instantiate the client object.

    time.reset();
    (message = "t0: ") << time;
    ::log << message;

    for(x=0;x<8192;x++)  sstring << x % 10;
                                        // Take some processing time and place
                                        // 8192 bytes in the send string.

    time.adjust();
    (message = "t1: ") << time;
    ::log << message;

    rcode = client.connect(argv[1],6600);
                                        // Ask for a connection to the server
                                        // name given as the first argument on
                                        // the command line.  Ask to use port
                                        // 6600 to establish the connection.

    if(rcode)  {                        // Check the error state.
        (message = "client reports error ") << rcode;
        ::log.error(message);
        return rcode;
    }

    client.send(sstring.string());        // Send a message!
    time.adjust();
    (message = "t2: ") << time;
    ::log << message;

    client.recv(rstring);               // Receive the reply!
    time.adjust();
    (message = "t17: ") << time;
    ::log << message;

    client.disconnect();                // Disconnect from the server.
    return 0;
}


/******************************************************************************/
