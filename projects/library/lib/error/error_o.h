/**  error_o.h  ****************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman

Copyright Daniel Huffman 1999



    Error Object.        


changes log
Date      who       what
4.29.99   Dan       Creation.
5.3.99    Dan       Added:    Error defintion ERROR_SOCKET_PORT_OUT_OF_RANGE.

*******************************************************************************/


#ifndef ErrorOBJECT_API
#define ErrorOBJECT_API

#include "string_o.h"


/*******************************************************************************
**  Errors.                                                                   **
*******************************************************************************/
#define ERROR_OK                            0000
#define ERROR_FAIL                          0001
#define ERROR_UNKNOWN                       0002


/*******************************************************************************
**  Thread Errors.                                                            **
*******************************************************************************/
#define ERROR_THREAD_TERMINATE_REQUEST      1201
#define ERROR_THREAD_WOULD_BLOCK            1202
#define ERROR_THREAD_DEADLOCK               1203
#define ERROR_THREAD_BUSY                   1204
#define ERROR_THREAD_INTERRUPTED            1205
#define ERROR_THREAD_ALREADY_DONE           1206


/*******************************************************************************
**  Permission or attrubute errors.                                           **
*******************************************************************************/
#define ERROR_INVALID_PERMISSION            2201
#define ERROR_INVALID_ATTRUBUTE             2202


/*******************************************************************************
**  Memory access or resource errors.                                         **
*******************************************************************************/
#define ERROR_NULL_PASSED                   3201
#define ERROR_BAD_FILE_DESCRIPTOR           3202
#define ERROR_FILE_DESCRIPTOR_TABLE_FULL    3203
#define ERROR_SYSTEM_FILE_TABLE_FULL        3204
#define ERROR_FILE_DESCRIPTOR_NOT_SOCKET    3205
#define ERROR_OUT_OF_BOUNDS                 3206
#define ERROR_NOT_WRITABLE_ADDRESS          3207
#define ERROR_OUT_OF_RESOURCES              3208
#define ERROR_OUT_OF_MEMORY                 3209


/*******************************************************************************
**  Socket errors.                                                            **
*******************************************************************************/
#define ERROR_SOCKET_UNAVAILABLE            4201
#define ERROR_SOCKET_UNREGISTERED           4202
#define ERROR_SOCKET_TIMED_OUT              4203
#define ERROR_SOCKET_NOT_CONNECTED          4205
#define ERROR_SOCKET_IS_CONNECTED           4206
#define ERROR_SOCKET_CONNECT_REFUSED        4207
#define ERROR_SOCKET_IN_PROGRESS            4204
#define ERROR_SOCKET_ALREADY                4204
#define ERROR_SOCKET_NO_HOST                4208
#define ERROR_SOCKET_NETWORK_DOWN           4209
#define ERROR_SOCKET_NETWORK_UNREACHABLE    4210
#define ERROR_SOCKET_HOST_UNREACHABLE       4210
#define ERROR_SOCKET_ADDR_IN_USE            4211
#define ERROR_SOCKET_ADDR_NOT_AVAILABLE     4212
#define ERROR_SOCKET_ADDR_NO_PERMISSION     4213
#define ERROR_SOCKET_INVAL                  4214 
#define ERROR_SOCKET_BIND_NO_DEV            4215 
#define ERROR_SOCKET_OP_NOT_SUPPORTED       4216
#define ERROR_SOCKET_OPTION_UNKNOWN         4217
#define ERROR_SOCKET_NO_SPACE               4218
#define ERROR_SOCKET_RECV_NO_DATA           4219 
#define ERROR_SOCKET_SEND_NO_DATA           4220
#define ERROR_SOCKET_RECV_INCOMPLETE_DATA   4221
#define ERROR_SOCKET_PORT_OUT_OF_RANGE      4222


/*******************************************************************************
**  Data Base errors.                                                         **
*******************************************************************************/
#define ERROR_DB_NOT_CONNECTED              5201
#define ERROR_DB_HANDLE_INVALID             5202
#define ERROR_DB_TABLE_NOT_IN_MEMORY        5203



/*******************************************************************************
**  Error Object Class Definition.                                            **
*******************************************************************************/

class error_o  {
  private:
    int         Number;
    string_o    Text;

  public:
    error_o();                                          // Default constructor.
    error_o(const error_o&);                            // Copy constructor.
    virtual    ~error_o();                              // Default destructor.
    error_o&    operator = (const error_o&);            // Assignment operator.
    void        clear();                                // Set no error state.


    error_o&    operator = (int);       // Make this error given error int.
    int         operator == (int);      // Returns non-zero if error number in
                                        // this is equivalent to the compared
                                        // int.
    int         operator != (int);      // Returns non-zero id error number in
                                        // this is not equivalent to the given
                                        // compared int.

    int         error()     const;      // Return error code.
    const char* text()      const;      // Returns the error in human readable
                                        // text format.

    int         socket(int);            // Give errno to a socket error.
    int         thread(int);            // Give errno to a thread error.
};
string_o& operator << (string_o&, const error_o&);


/******************************************************************************/

inline int error_o::error() const  {
    return  Number;
}

inline const char* error_o::text() const  {
    return  Text.string();
}

inline int error_o::operator == (int e)  {
    return  (Number == e);
}

inline int error_o::operator != (int e)  {
    return  (Number != e);
}


#endif

/******************************************************************************/
