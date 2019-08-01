/**  server3.cc  ***************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Example Three.  Server.                                          5.9.99
    Taking care of shared memory.



*******************************************************************************/


#include "pserver_o.h"              // Include the Performance Server
                                    // Library v2.000 with a base class server.
log_o       log;                    // Global thread-safe log.
sysinfo_o   sysinfo;                // System information for optimization.
carapace_o  carapace;               // A hard shell for programming.

mutex_o     mutex;                  // A Mutual Exclusion Object.
int         client[3];              // Count 3 unique client's access.
int         naccess;                // Total number times accessed.


    // Since this method might be executed concurrently by many threads,
    // any shared memory needs to be placed with in a mutex lock.

int carapace_o::process(input_o& input, output_o& output)  {
    int         nac;
    int         cac; 
    string_o    istring;
    string_o    ostring;

    istring = input.message();
    istring.cut(1);
    switch(istring.stoi())  {
        case 1:
            mutex.lock();                       // Many number one clients may
                cac = (client[0]++);            // share the client[0] and the
                nac = (naccess++);              // naccess variables, so their
            mutex.unlock();                     // access needs to be mutually
                                                // exclusive.

                                                // Client 1 gets all available
                                                // informaiton.
            ostring << "Client 1 accessed " << cac;
            ostring << " times, total times accessed " << nac << '.';
            break;

        case 2:
            mutex.lock();                       // Many number two clients may
                cac = (client[1]++);            // share the client[0] and the
                naccess++;                      // naccess variables, so their
            mutex.unlock();                     // access needs to be mutually
                                                // exclusive.

                                                // Client 2 is blind to total
                                                // accesses.
            ostring << "Client 2 accessed " << cac << " times.";
            break;

        case 3:
            mutex.lock();                       // Many number three clients may
                client[3]++;                    // share the client[0] and the
                nac = (naccess++);              // naccess variables, so their
            mutex.unlock();                     // access needs to be mutually
                                                // exclusive.

                                                // Client 3 is blind to the
                                                // number of times it has
                                                // accessed this server.
            ostring << "Clients have accessed " << nac << " times.";
            break;

        default:
            ostring << "Unautherized access attempted `" << istring << "'.";
            ::log.error(ostring);
            break;
    }
            
    output.setMessage(ostring.string());
    return 0;
}


    // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       x;
    int       rcode;
    pserver_o pserver;                  // Instantiate the server object.

    for(x=0;x<3;x++)  client[x] = 0;    // Set shared memory to zero.
    naccess = 0;

    rcode = pserver.serveport(6603);    // Ask the server to listen and
                                        // service port 6603.

    if(rcode)  return rcode;            // Check the error state.

    pserver.persist();                  // Tell the server object to continue
                                        // executing while this main function
                                        // is suspended.
    return 0;                           // Execution should never reach here.
}

/******************************************************************************/
