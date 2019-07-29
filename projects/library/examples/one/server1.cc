/**  server1.cc  ***************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman


    Example One.  Server.                                             5.4.99
    Simple Performance Client-Server.


    This example demonstrates the prowess of the Performance Server Library
    v2.000 by creating performance client-server communications
    with a minimum of programming and effort.

*******************************************************************************/

#include "../../pserver/pserver.h"  // Include the Performance Server Library
                                    // v2.000 with a base class server.

log_o   log;        // All objects that do error reporting send the report to
                    // this global log object.  The log object is thread-safe
                    // and prevents one message from cutting off another message
                    // during concurrent thread error reports.  This log can
                    // also be used during debugging and to log non-error
                    // occurrences.
sysinfo_o sysinfo;  // The sysinfo object provides information such as the
                    // number of underlying cpus this host possesses
carapace_o carapace;// This carapace shell is where a programmer can manipulate
                    // data flowing through the server.

    // Overload this virtual process method from the carapace class.
    // This is where programmers can receive input and send output.
    // A filled input object comes in over the first argument.  Fill the
    // second argument, output object, before exiting the method.  The output
    // object is sent on to the client.
    // Careful!  Multiple threads can concurrently execute this method.
    // All shared memory across these threads must be dealt with appropriately.

int carapace_o::process(input_o* input,output_o* output)  {
    output->setMessage("right back at ya.");
    return 0;
}

                    // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       rcode;
    pserver_o pserver;                  // Instantiate the server object.

    rcode = pserver.serveport(1999);    // Ask the server to listen and
                                        // service port 1999.

    if(rcode)  return rcode;            // Check the error state.

    pserver.persist();                  // Tell the server object to continue
                                        // executing while this main function
                                        // is suspended.
    return 0;                           // Execution should never reach here.
}

