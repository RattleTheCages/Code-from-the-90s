/**  log_o.h  ******************************************************************

    12.31.1999  Performance Server Library v2.000


    Log Object.



changes log
when      when    what
4.29.99   Dan     Creation.
5.2.99    Dan     Added:    Debug levels to log.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef LogOBJECT_API
#define LogOBJECT_API

#include "string_o"
#include "mutex_o"


#define LOG_MAX_DEBUG_LEVEL 2048


class log_o  {
  private:
    mutex_o         mutex;
    string_o        Name;
    int             Toggle;
    short           Debug[LOG_MAX_DEBUG_LEVEL];


    void            commitLog(const string_o&);     // Do the log write.
    void            commitError(const string_o&);   // Do the error log write.

  public:   
    log_o();
    log_o(const log_o&);
    virtual  ~log_o();
    log_o&    operator = (const log_o&);

    void      error(const char*);           // Report an error.
    void      error(const string_o&);       // Report an error.

    void      operator << (const char*);    // Write a log entry.
    void      operator << (const string_o&);// These operators return void to
    void      operator << (const string_o*);// force a complete log entry when
                                            // used.

    void      registerName(const char*);    // Assign a name to this log.
    int       setDebugLevel(int);           // Set given debug level.
    int       debug(int);                   // 
    int       toggle();                     // Toggle on and off the logging to
                                            // standard log.  Has no effect on
                                            // error logging.  Return:
                                            // 1- log now on, 0- log now off.

};


/******************************************************************************/


inline int log_o::debug(int dbl)  {
    if(dbl > 0 && dbl < LOG_MAX_DEBUG_LEVEL)  return  (int)Debug[dbl];
    return  0;
}

inline int log_o::setDebugLevel(int dbl)  {
    if(dbl > 0 && dbl < LOG_MAX_DEBUG_LEVEL)  Debug[dbl] = 1;
    return  dbl;
}


#endif

/******************************************************************************/
