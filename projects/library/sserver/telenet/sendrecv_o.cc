/**  sendrecv_o.cc  ************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999





changes log
when      who       what
4.28.99   Dan       Creation

*******************************************************************************/


#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#include "error_o.h"
#include "sendrecv_o.h"
#include "succession_o.h"


sendrecv_o::sendrecv_o()  {}

sendrecv_o::~sendrecv_o()  {}

long int sendrecv_o::send(int S,const string_o& ss)  { 
    //long int      sflags;
    if(ss.length() < 1)  return 0;
    ((error_o*)this)->clear();

    //sflags =::fcntl(S,F_GETFL,NULL);
    //if(  ::fcntl(S,F_SETFL, O_NONBLOCK) == -1)  {
    if(  ::fcntl(S,F_SETFL,(::fcntl(S,F_GETFL,NULL) ^ O_NONBLOCK)) == -1)  {

        ((error_o*)this)->socket(errno);
    }

    return  send(S,ss.string(), ss.length());
}

long int sendrecv_o::recv(int S,string_o& rs)  {
    char          buf[8192];
    long int      thisrecv;
    long int      nrecv;
    long int      sflags;
    long int      retry = 4096L;

    ((error_o*)this)->clear();

    sflags =::fcntl(S,F_GETFL,NULL);
    if(  ::fcntl(S,F_SETFL, O_NONBLOCK) == -1)  {
    //if(  ::fcntl(S,F_SETFL,(::fcntl(S,F_GETFL,NULL) ^ O_NONBLOCK)) == -1)  {
        ((error_o*)this)->socket(errno);
    }

    nrecv = 0;
    while(*(error_o*)this == ERROR_OK ||
          (*(error_o*)this == ERROR_THREAD_WOULD_BLOCK && nrecv == 0) ||
          (*(error_o*)this == ERROR_THREAD_INTERRUPTED && nrecv == 0))  {
        succession_o::memset(buf, 0, 8192);
::usleep(4);
        thisrecv = recv(S,buf,8192);
if(thisrecv > 0)  {
        nrecv += thisrecv;
    //    rs << buf;
rs.fill(thisrecv,buf);
}
else  {
        retry = retry - 1;
}
        if(retry < 1)  break;
    }
    

    if(error() == ERROR_OK &&
       ::fcntl(S,F_SETFL,sflags) == -1)  {
        ((error_o*)this)->socket(errno);
    }

    return nrecv;
}

long int sendrecv_o::recvC(int S, string_o& rs)  {
    char     buf[8192];
    long int      thisrecv;
    long int      nrecv;
    long int      sflags;
    long int      retry = 4096L;

    ((error_o*)this)->clear();

 //   sflags =::fcntl(S,F_GETFL,NULL);
    //if(  ::fcntl(S,F_SETFL, O_NONBLOCK) == -1)  {
/*
    if(  ::fcntl(S,F_SETFL,(::fcntl(S,F_GETFL,NULL) ^ O_NONBLOCK)) == -1)  {
        ((error_o*)this)->socket(errno);
    }
*/

    nrecv = 0;
    while(*(error_o*)this == ERROR_OK ||
          (*(error_o*)this == ERROR_THREAD_WOULD_BLOCK && nrecv == 0) ||
          (*(error_o*)this == ERROR_THREAD_INTERRUPTED && nrecv == 0))  {
        succession_o::memset(buf, 0, 8192);
::usleep(4);
        thisrecv = recv(S,buf,8192);
if(thisrecv > 0)  {
        nrecv += thisrecv;
//        rs << buf;
rs.fill(thisrecv,buf);
}else{
        retry = retry - 1;
}
        if(retry < 1)  break;
    }
    

/*
    if(error == ERROR_OK &&
       ::fcntl(S,F_SETFL,sflags) == -1)  {
        ((error_o*)this)->socket(errno);
    }
*/

    return nrecv;
}

long int sendrecv_o::recv(int S, char* buf, long int size)  {
    long int    count;
    long int    nbytes;
    long int    ndata;

    ndata   = 0;
    count   = 0;

    while(count < size)  {
        nbytes = ::recv(S,(buf+count),size-count,0);
        if(nbytes == 0)  {
            ndata++;
            if(ndata > 2220)  {
                *(error_o*)this = ERROR_SOCKET_RECV_NO_DATA;
                return count;
            }
        }
        if(nbytes < 0)  {
            ((error_o*)this)->socket(errno);
            return count;
        }
        if(nbytes > 0)  count = count + nbytes;
    }
    return  count;
}


long int sendrecv_o::send(int S, const char* buf, long int size)  {
    long int    count;
    long int    nbytes;
    long int    ndata;

    ndata   = 0;
    count   = 0;


    while(count != size)  {
        nbytes = ::send(S,(buf+count),size-count,0);
        if(nbytes == 0)  {
            ndata++;
            if(ndata > 2220)  {
                *(error_o*)this = ERROR_SOCKET_SEND_NO_DATA;
                return count;
            }
        }
        if(nbytes < 0)  {
            ((error_o*)this)->socket(errno);
            return count;
        }
        if(nbytes > 0)  count = count + nbytes;
    }
    return  count;
}


int sendrecv_o::close(int s)  {

    if(*(error_o*)this == ERROR_OK)  {
        ::close(s);
    }
/*
    while(::shutdown(s,2) < 0)  {
        if(errno != EINTR)  {
            ((error_o*)this)->socket(errno);
            ::close(s);
            return error();
        }
    }
*/

    return  error();
}


/******************************************************************************/
