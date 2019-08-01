/**  client_o.cc  **************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999





changes log
when      who       what
5.3.99    Dan       Creation
9.9.99    Dan       Changed:  Since ::gethostbyname does not work in a threaded
                                    program, now only accept IP address and
                                    removed any use of netdb.h.

*******************************************************************************/


#include </usr/include/string.h>
#include <errno.h>
#include <unistd.h>

#include "log_o.h"
#include "error_o.h"
#include "client_o.h"

extern log_o    log;


client_o::client_o()  {
    State             = CLIENT_NOT_CONNECTED;

    Socket            = -1;
    Port              = -1;

    (void)::memset(&server,0,sizeof(server));

    server.sin_family = AF_INET;
}

client_o::~client_o()  {
    string_o message;

    if(State == CLIENT_CONNECTED)  {
        while(::close(Socket) < 0)  {
            if(errno != EINTR)  {
                ((error_o*)this)->socket(errno);
                (message = "") << "client_o: destructor(): " << *(error_o*)this;
                message << "unable to close socket " << Socket << '.';
                ::log.error(message);
            }
            ::shutdown(Socket,2);
        }
    }
}

int client_o::connect(const char* serverName, int port)  {
    string_o u;
    string_o v;
    string_o message;

    char adr[24];
    (void)::memset(adr,0,sizeof(adr));


    if(State == CLIENT_CONNECTED)  {
        *(error_o*)this = ERROR_SOCKET_IS_CONNECTED;
        (message = "") << "client_o: connect(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    if(!serverName)  {
        *(error_o*)this = ERROR_NULL_PASSED;
        (message = "") << "client_o: connect(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    if(port < 0 || port >= CLIENT_MAX_PORT)  {
        *(error_o*)this = ERROR_SOCKET_PORT_OUT_OF_RANGE;
        (message = "") << "client_o: connect(" << serverName << ",";
        message << port << "): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }


    IPAddress = serverName;


    if(::log.debug(251))  {
        (message = "") << "client_o: connect(" << IPAddress << ",";
        message << port << "): attempting to connect to host.";
        ::log << message;
    }


    ((error_o*)this)->clear();

    server.sin_port   = htons(port);


    if((Socket = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == -1)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "client_o: connect(" << serverName << ",";
        message << port << "): ::socket(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    if(::log.debug(251))  {
        (message = "") << "client_o: connect(" << serverName << ",";
        message << port << "): open socket: " << Socket;
        ::log << message;
    }


    u = serverName;
    v = serverName;

    u.cut('.');
    adr[0] = (char)u.stoi();
    v.upcut('.');
    u = v;
    u.cut('.');
    adr[1] = (char)u.stoi();
    v.upcut('.');
    u = v;
    u.cut('.');
    adr[2] = (char)u.stoi();
    v.upcut('.');
    u = v;
    u.cut('.');
    adr[3] = (char)u.stoi();

    (void)::memcpy(&server.sin_addr,adr,4);


    if(::connect(Socket,(sockaddr*)&server,sizeof(server)) < 0)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "client_o: connect(" << serverName << ",";
        message << port << "): ::connect(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    State = CLIENT_CONNECTED;


    if(::log.debug(251))  {
        (message = "") << "client_o: connect(" << serverName << ",";
        message << port << "): connection established.";
        ::log << message;
    }

    return error();
}

int client_o::disconnect()  {
    string_o message;

    if(State == CLIENT_NOT_CONNECTED)  {
        *(error_o*)this = ERROR_SOCKET_NOT_CONNECTED;
        (message = "") << "client_o: disconnect(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    ((error_o*)this)->clear();
    sendrecv_o::close(Socket);
/*
    while(::close(Socket) < 0)  {
        if(errno != EINTR)  {
            ((error_o*)this)->socket(errno);
            (message = "") << "client_o: destructor(): " << *(error_o*)this;
            message << "unable to close socket " << Socket << '.';
            ::log.error(message);
            return error();
        }
::usleep(50000);//!!
    }
*/

    IPAddress = "";
    State  = CLIENT_NOT_CONNECTED;


    if(::log.debug(251))  {
        (message = "") << "client_o: disconnect(): disconnected socket: " << Socket << '.';
        ::log << message;
    }

    return  error();
}

long int client_o::send(const char* s, long int l)  {
    return  sendrecv_o::send(Socket,s,l);
}

long int client_o::send(const string_o& ss)  {
    string_o message;

    if(State == CLIENT_NOT_CONNECTED)  {
        *(error_o*)this = ERROR_SOCKET_NOT_CONNECTED;
        (message = "") << "client_o: send(): " << *(error_o*)this;
        ::log.error(message);
        return error();
    }

    if(::log.debug(251))  {
        (message = "") << "client_o: send(): sending on socket " << Socket;
        ::log << message;
    }

    ((error_o*)this)->clear();
    return  sendrecv_o::send(Socket,ss);
}

long int client_o::recv(char* s,long int l)  {
    return  sendrecv_o::recv(Socket,s,l);
}

long int client_o::recv(string_o& rs)  {
    string_o message;

    if(State == CLIENT_NOT_CONNECTED)  {
        *(error_o*)this = ERROR_SOCKET_NOT_CONNECTED;
        (message = "") << "client_o: recv(): " << *(error_o*)this;
        ::log.error(message);
        return  error();
    }

    if(::log.debug(251))  {
        (message = "") << "client_o: recv(): receiving on socket " << Socket;
        ::log << message;
    }

    ((error_o*)this)->clear();
    return  sendrecv_o::recvC(Socket,rs);
//    return sendrecv_o::recv(Socket,rs);
}


/******************************************************************************/
