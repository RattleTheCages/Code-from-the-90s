/**  error.cc  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




changes log
Date      who       what
4.29.99   Dan       Creation.

*******************************************************************************/


#include <errno.h>
#include "error.h"


error_o::error_o(): Number(ERROR_OK)  {}

error_o::error_o(const error_o& e)  {
    Number  = e.error();
    Text    = e.text();
}

error_o::~error_o()  {}

error_o& error_o::operator = (const error_o& e)  {
    Number  = e.error();
    Text    = e.text();
    return  *this;
}

void error_o::clear()  {
    Number = ERROR_OK;
    Text   = "";
}

error_o& error_o::operator = (int en)  {
    Number = en;
    Text   = "";
    return  *this;
}

int error_o::socket(int errornumber)  {
    switch(errornumber)  {

        case EBADF:
            Number  =  ERROR_BAD_FILE_DESCRIPTOR;
            Text    = "ERROR_BAD_FILE_DESCRIPTOR";
            break;

        case ENOTCONN:
            Number  =  ERROR_SOCKET_NOT_CONNECTED;
            Text    = "ERROR_SOCKET_NOT_CONNECTED";
            break;

        case ENOTSOCK:
            Number  =  ERROR_FILE_DESCRIPTOR_NOT_SOCKET;
            Text    = "ERROR_FILE_DESCRIPTOR_NOT_SOCKET";
            break;

        case EWOULDBLOCK:
            Number  =  ERROR_THREAD_WOULD_BLOCK;
            Text    = "ERROR_THREAD_WOULD_BLOCK";
            break;

        case EINTR:
            Number  =  ERROR_THREAD_INTERRUPTED;
            Text    = "ERROR_THREAD_INTERRUPTED";
            break;

        case EINPROGRESS:
            Number  =  ERROR_SOCKET_IN_PROGRESS;
            Text    = "ERROR_SOCKET_IN_PROGRESS";
            break;

        case EALREADY:
            Number  =  ERROR_SOCKET_IN_PROGRESS;
            Text    = "ERROR_SOCKET_IN_PROGRESS";
            break;

        case EOPNOTSUPP:
            Number  =  ERROR_SOCKET_OP_NOT_SUPPORTED;
            Text    = "ERROR_SOCKET_OP_NOT_SUPPORTED";
            break;

        case EMFILE:
            Number  =  ERROR_FILE_DESCRIPTOR_TABLE_FULL;
            Text    = "ERROR_FILE_DESCRIPTOR_TABLE_FULL";
            break;

        case ENFILE:
            Number  =  ERROR_SYSTEM_FILE_TABLE_FULL;
            Text    = "ERROR_SYSTEM_FILE_TABLE_FULL";
            break;

        case EFAULT:
            Number  =  ERROR_NOT_WRITABLE_ADDRESS;
            Text    = "ERROR_NOT_WRITABLE_ADDRESS";
            break;

        case EADDRNOTAVAIL:
            Number  =  ERROR_SOCKET_ADDR_NOT_AVAILABLE;
            Text    = "ERROR_SOCKET_ADDR_NOT_AVAILABLE";
            break;

        case EADDRINUSE:
            Number  =  ERROR_SOCKET_ADDR_IN_USE;
            Text    = "ERROR_SOCKET_ADDR_IN_USE";
            break;

        case EACCES:
            Number  =  ERROR_SOCKET_ADDR_NO_PERMISSION;
            Text    = "ERROR_SOCKET_ADDR_NO_PERMISSION";
            break;

        case EISCONN:
            Number  =  ERROR_SOCKET_IS_CONNECTED;
            Text    = "ERROR_SOCKET_IS_CONNECTED";
            break;

        case ETIMEDOUT:
            Number  =  ERROR_SOCKET_TIMED_OUT;
            Text    = "ERROR_SOCKET_TIMED_OUT";
            break;

        case ECONNREFUSED:
            Number  =  ERROR_SOCKET_CONNECT_REFUSED;
            Text    = "ERROR_SOCKET_CONNECT_REFUSED";
            break;

        case ENETUNREACH:
            Number  =  ERROR_SOCKET_NETWORK_UNREACHABLE;
            Text    = "ERROR_SOCKET_NETWORK_UNREACHABLE";
            break;

        case EHOSTUNREACH:
            Number  =  ERROR_SOCKET_HOST_UNREACHABLE;
            Text    = "ERROR_SOCKET_HOST_UNREACHABLE";
            break;

        case ENOBUFS:
            Number  =  ERROR_OUT_OF_RESOURCES;
            Text    = "ERROR_OUT_OF_RESOURCES";
            break;

        case EMSGSIZE:
            Number  =  ERROR_FAIL;
            Text    = "ERROR_FAIL";
            break;

        default:
            Number  =  ERROR_FAIL;
            Text    = "ERROR_FAIL";
            break;
    }

    return  Number;
}

int error_o::thread(int errornumber)  {
    Number = errornumber;
    return  Number;
}

string_o& operator << (string_o& s, const error_o& error)  {
    s << "E-" << error.error() << ": " << error.text();
    return  s;
}


/******************************************************************************/
