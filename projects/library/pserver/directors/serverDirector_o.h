/**  serverDirector_o.h  *******************************************************

    12.31.1999  Performance Server Library v2.000


    Server Director Object.





changes log
when      who     what
5.2.99    Dan     Creation
5.3.99    Dan     Added     Method aquireServer(null).
5.4.99    Dan     Added     An operator method.





                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ServerDirectorOBJECT_API
#define ServerDirectorOBJECT_API

#include "error_o"
#include "queue_o"
#include "input_o"
#include "output_o"
#include "server_o"


class serverDirector_o: public error_o  {
  private:
    server_o*           Server;
    queue_o<server_o>   servers;

  public:
    serverDirector_o();
    serverDirector_o(const serverDirector_o&);
    virtual          ~serverDirector_o();
    serverDirector_o& operator = (const serverDirector_o&);


    server_o*   aquireServer(int);                  // Aquire a server listening
                                                    // to port given.
    int         relinquishServer(server_o*);        // Relinquish given server.
    server_o*   existingServer();                   // Return an already
                                                    // aquired server_o object.

};
string_o& operator << (string_o&, const serverDirector_o&);


/******************************************************************************/

inline string_o& operator << (string_o& s, const serverDirector_o& sd)  {
    s << "serverDirector_o: ";
    return  s;
}

#endif

/******************************************************************************/
