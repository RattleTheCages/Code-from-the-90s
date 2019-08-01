/**  server2.cc  ***************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman


    Example Two.  Server.                                             5.4.99
    P is for performance.



    How can the performance of a client-server pair be measured?  What about
    all the propagation delays networking contributes?  How can bottlenecks
    be found and accelerated?



    The timeline below highlights propagation delays as the data flow passes
    through processes.


   |---------------CLIENT-----------------|     |-------NETWORK-------|

  client      PObjs    Operating system         Network
  program              and hardware

t0         t1        t2          t3          t4
|----------|---------|-----------|-----------|--------------->
  custom     PObj      OS and      TCP/IP      Network
  program -> client -> TCP/IP   -> hardware -> transmission ->
  delay      output    software    layers
                       layers



   |-------------------SERVER-------------------------------

   Operating system           PObjs          server
   and hardware                              program

t5          t6        t7        t8       t9
|-----------|---------|---------|--------|------------------->
  TCP/IP      OS and    PObj      PObj     custom
  hardware -> TCP/IP -> server -> input -> program ->
  layers      software  input     queue    delay
              layers    loop



   --------------------SERVER-------------|    |------NETWORK------|

         PObjs          Operating system         Network
                        and hardware

t10       t11       t12         t13         t14
|---------|---------|-----------|-----------|---------------->
  PObj      PObj      OS and      TCP/IP      Network
  output -> server -> TCP/IP   -> hardware -> transmission ->
  queue     output    software    layers
            loop      layers



   |---------------CLIENT-----------------|

   Operating system       PObjs     client
   and hardware                     program

t15         t16         t17       t18
|-----------|-----------|---------|---------|
  TCP/IP      OS and      PObj      custom
  hardware -> TCP/IP   -> client -> program
  layers      software    input
              layers


    In the timeline, there are many processes that the Hufflynx Performance
    Server Object Library 1.0 can not affect.

I)      Between t4 & t5, and between t14 & t15, the data is flowing over the
        network.
        Delays here need to be addressed by Network Administrators.

II)     Between t2 & t4, t5 & t7, t12 & t14, and between t15 & t17 the data
        is flowing through the TCP/IP layers and the operating system.
        Improvements can be made by upgrading hardware and operating system
        software.

III)    Between t0 & t1, and between t9 & t10, propagation delays are the
        result of programmer's custom programs.  These are the programs
        that do the variety of things desired.
        Improvements can be made by analyzing programmer's custom code for
        optimization improvements and implementing them.  Improvements
        may also be found by upgrading hardware and operating system software.


    The timeline reveals how little of the data flow propagation delay can
    be found in the Hufflynx Performance Server Object Library.  However, to
    remove data flow bottlenecks, these objects must perform their jobs quickly.

IV)     Between t1 & t2, t7 & t9, t10 & t12, and between t17 & t18 are
        the propagation delay of the Performance Server Object Library objects.
        Ways to improve the performance of these objects is on going by
        the creators of the Performance Server Library v2.000.



    In example two, the client-server pair will demonstrate the performance
    of as many of the independent data flow points as the Performance Server
    Object Library 1.0 can time.  PObjs are limited.  For example, PObjs
    can not time the difference of t3 and t4.  The code simply can not place
    a hook to trigger the timer storage between where the operating system
    hands the data over to the hardware and when the hardware actually places
    the data on the conduits of the network.  However, careful analyzation
    of the performance times against difference hardware and software
    configurations, can reveal much of the gray performance area.

    Performance Server Object Library can record the data flow time at data
    flow points:

t1  - Client program sends data to PObjs.
t2  - PObjs client sends data to the OS.

t7  - Data appears at the PObjs server input loop.
t8  - Time the server input loop takes to place the data on the input queue.
t9  - Time data waits on the input queue before the start of processing.
t10 - Server program finished processing and places data on the output queue.
t11 - Time data waits on the output queue for an output loop.
t12 - Time the server output loop takes to hand the data to the OS.

t17 - Data appears at the PObjs client input.
t18 - PObjs advances data to the client program.


    The Performance Server Object Library's input and output data container
    objects inherit the attributes of the PObjs's time object.  The time object
    can be set to time zero, and asked how much time has transpired.  The
    utilization of this inherited object facilitates the performance measure
    points stated.


    In this data transaction schema, the server is oblivious to the network
    propagation delay.  The server can only measure time between when the
    data appears to the server process and when the data is handed back
    to the operating system.

    These performance time measurement points are easily available for
    inspection via the debug levels included in the Performance Server
    Library v2.000.  By setting the performance time debug levels to on, the
    server's log will record performance time as data flows through the time
    points.



*******************************************************************************/


#include "../../pserver/pserver_o.h"// Include the Performance Server
                                    // Library v2.000 with a base class server.

log_o       log;        // The performance timings will be placed in this log.
sysinfo_o   sysinfo;    // Some PObjs optimize themselves with information from
                        // this object.
carapace_o  carapace;   // Give the programmer a shell to turn input into
                        // output.

    // Overload this virtual process method from the carapace class.
    // This is where programmers can receive input and send output.
    // Careful!  Multiple threads can concurrently execute this method.
    // All shared memory across these threads must be dealt with appropriately.

int carapace_o::process(input_o& input, output_o& output)  {
    output.setMessage("right back at ya.");
    return 0;
}

                        // Create the starting point, main function.

int main(int argc,char* argv[])  {
    int       rcode;
    pserver_o pserver;                  // Instantiate the server object.

    ::log.registerName(argv[1]);
    ::log.setDebugLevel(119);           // Set the performance timing debug
    ::log.setDebugLevel(309);           // levels to on.
    ::log.setDebugLevel(319);

    rcode = pserver.serveport(6600);    // Ask the server to listen and
                                        // service port 6600.

    if(rcode)  return rcode;            // Check the error state.

    pserver.persist();                  // Tell the server object to continue
                                        // executing while this main function
                                        // is suspended.
    return 0;                           // Execution should never reach here.
}

/******************************************************************************/
