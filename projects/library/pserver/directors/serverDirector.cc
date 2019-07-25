/**  serverDirector.cc  ********************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




Log Debug Levels
451 - Aquire server objects.
452 - Relinquish server objects.


changes log
when       who      what
5.2.99     Dan      Creation.
5.3.99     Dan      Added:    Method aquireServer(null).
5.4.99     Dan      Added:    Debug to method relinquishThread.


*******************************************************************************/


#include "log.h"
#include "../directors/serverDirector.h"

extern log_o log;


serverDirector_o::serverDirector_o()  {}

serverDirector_o::~serverDirector_o()  {}

server_o* serverDirector_o::aquireServer(int p)  {
    string_o    message;
    server_o*   server;

    server = new server_o(p);
    if(!server)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << *this << "aquireServer(" << p;
        message << "): " << *(error_o*)this;
        ::log.error(message);
        return NULL;
    }
    if(server->error())  {
        *(error_o*)this = *(error_o*)server;
        (message = "") << *this << "aquireServer(" << p;
        message << "): " << *(error_o*)this;
        ::log.error(message);
    }

    servers.put(server);
    if(!server->error() || !Server)  Server = server;

    if(::log.debug(451))  {
        (message = "") << *this << "aquireServer(" << p;
        message << "): cirulating " << *server;
        ::log << message;
    }

    return server;
}

server_o* serverDirector_o::exsitingServer()  {
    string_o message;

    if(Server)  {
        if(::log.debug(451))  {
            (message = "") << *this << "exsitingServer(): " << *Server;
            ::log << message;
        }
        return Server;
    }
    else  {
        *(error_o*)this = ERROR_FAIL;
        (message = "") << *this << "exsitingServer(): " << *(error_o*)this;
        ::log.error(message);
        return NULL;
    }
}

int serverDirector_o::relinquishServer(server_o* server)  {
    string_o message;

    if(::log.debug(452))  {
        (message = "") << *this <<  "relinquishServer: not implemented yet.";
        ::log << message;
    }

    return error();
}

/******************************************************************************/
