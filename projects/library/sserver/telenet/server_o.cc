/**  server_o.cc  **************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999





changes log
when      who       what
4.28.99   Dan       Creation
9.9.99    Dan       Changed:  Removed and netdb.h because it does not work
                              in a multithreaded enviroment.

*******************************************************************************/

#include <errno.h>
#include <unistd.h>

#include "log_o.h"
#include "error_o.h"
#include "server_o.h"
#include "succession_o.h"

extern log_o  log;


server_o::server_o(int port)  {
    string_o    message;
    size_t      size;

    Port                    = port;

    succession_o::memset(&server, 0, sizeof(server));
    server.sin_family       = AF_INET;
    server.sin_port         = htons(port);
    server.sin_addr.s_addr  = INADDR_ANY;
    linger.l_onoff          = 1;
    linger.l_linger         = 16;

    if((Socket = ::socket(PF_INET,SOCK_STREAM,0)) == -1)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: socket(): " << *(error_o*)this;
        ::log.error(message);
        return;
    }

    if(::bind(Socket,(sockaddr*)&server,sizeof(server)) != 0)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: bind(): " << *(error_o*)this;
        ::log.error(message);
        return;
    }

    size = sizeof(server);
    if(::getsockname(Socket,(sockaddr*)&server,(socklen_t*)&size) != 0)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: getsockname(): " << *(error_o*)this;
        ::log.error(message);
        return;
    }

    if(::listen(Socket,SOMAXCONN) != 0)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: listen(): " << *(error_o*)this;
        ::log.error(message);
        return;
    }

    if(::log.debug(211)) {
        (message = "") << "server_o: socket: " << Socket;
        message << " listening to port: " << Port;
        ::log << message;
    }
}

server_o::~server_o()  {
    string_o message;

    if(::shutdown(Socket,0) < 0  && errno != ETIMEDOUT)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: destructor: ::shutdown(): " << *(error_o*)this;
        ::log.error(message);
        return;
    }

    if(::log.debug(212)) {
        message << "server_o: shutdown listen socket: " << Socket;
        ::log << message;
    }
}

int server_o::accept()  {
    string_o          message;
    int               flag;
    size_t            size;
    int               ci;

    ((error_o*)this)->clear();
    size = sizeof(client);

    if((Accept = ::accept(Socket,&client,(socklen_t*)&size)) == -1)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: accept: accept(): " << *(error_o*)this;
        ::log.error(message);
        return -1;
    }

    if(::setsockopt(Accept,SOL_SOCKET,SO_LINGER,(const char*)&linger,sizeof(linger)) != 0)  {
        ((error_o*)this)->socket(errno);
        (message = "") << "server_o: accept: setsockopt(): " << *(error_o*)this;
        ::log.error(message);
        return -1;
    }

    ClientIp = "000.000.000.000";
/*
    memset(&ci,0,sizeof(ci));
    memcpy(&ci,(client.sa_data+2),1);
    ClientIp << (int)ci << '.';
    memset(&ci,0,sizeof(ci));
    memcpy(&ci,(client.sa_data+3),1);
    ClientIp << (int)ci << '.';
    memset(&ci,0,sizeof(ci));
    memcpy(&ci,(client.sa_data+4),1);
    ClientIp << (int)ci << '.';
    memset(&ci,0,sizeof(ci));
    memcpy(&ci,(client.sa_data+5),1);
    ClientIp << (int)ci;
*/


    if(::log.debug(213))  {
        (message = "") << "server_o: socket " << Accept;
        message << " connect to client: " << clientHost() << ", " << clientIp();
        ::log << message;
    }

    return  Accept;
}

int server_o::close(int s)  {
    string_o message;

    ((error_o*)this)->clear();

    (void)sendrecv_o::close(s);

    if(::log.debug(214)) {
        (message = "") << "server_o: close(" << s << "): connection closed.";
        ::log << message;
    }


    return  error();
}

int server_o::recv(string_o& rs)  {
    return  sendrecv_o::recv(Accept,rs);
}

int server_o::send(const string_o& ss)  {
    return  sendrecv_o::send(Accept,ss);
}

int server_o::send(int S,const string_o& ss)  {
    return  sendrecv_o::send(S,ss);
}


/******************************************************************************/
