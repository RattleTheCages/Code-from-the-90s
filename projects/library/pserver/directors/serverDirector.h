/**  serverDirector.h  *********************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Server Director Object.


changes log
when      who     what
5.2.99    Dan     Creation
5.3.99    Dan     Added     Method aquireServer(null).
5.4.99    Dan     Added     An operator method.


*******************************************************************************/


#ifndef SERVERDIRECTOROBJECT_API
#define SERVERDIRECTOROBJECT_API

#include "../../lib/error/error.h"
#include "../../lib/thread/queue.h"
#include "../../sserver/dataobjects/input.h"
#include "../../sserver/dataobjects/output.h"
#include "../../sserver/telenet/server.h"


class serverDirector_o: public error_o  {
  private:
    server_o*           Server;
    queue_o<server_o>   servers;

  public:
    serverDirector_o();                             // Default constructor.
    serverDirector_o(const serverDirector_o&);      // Copy constuctor.
   ~serverDirector_o();                             // Default desructor.
    serverDirector_o& operator = (const serverDirector_o&);
                                                    // Assignment operator.


    server_o*   aquireServer(int);                  // Aquire a server listening
                                                    // to port given.
    int         relinquishServer(server_o*);        // Relinquish given server.
    server_o*   exsitingServer();                   // Return an already
                                                    // aquired server_o object.

};
string_o& operator << (string_o&,const serverDirector_o&);


/******************************************************************************/

inline string_o& operator << (string_o& s, const serverDirector_o& sd)  {
    s << "serverDirector_o: ";
    return s;
}

#endif

/******************************************************************************/
