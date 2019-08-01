/**  succession_o.h  ***********************************************************

 Copyright 07.31.2019  Performance Server Library v2.000  Daniel Huffman


    Remove dependencies on /usr/include/strings.h by providing
    bzero(), memset, and memcpy.  Maybe others in the future.


changes log
when      who     what
7.31.19   Dan     Creation.

*******************************************************************************/


#ifndef SuccessionOBJECT_API
#define SuccessionOBJECT_API


class succession_o  {
  private:
    int             State;

  public:
    succession_o();
    succession_o(const succession_o&);
    virtual      ~succession_o();
    succession_o& operator = (const succession_o&);

           int      state() const;

    static void     bzero(void*, int);
    static void     memset(void*, char, int);
    static int      memcpy(void*, const char*, int);


};


/******************************************************************************/

inline int succession_o::state() const  {
    return  State;
}


inline void succession_o::bzero(void* tobbz, int length)  {
    for(unsigned long int x=0; x < length; x++)  *((char*)tobbz + x) = '\0';
}

inline void succession_o::memset(void* tobms, char setto, int length)  {
    for(unsigned long int x=0; x < length; x++)  *((char*)tobms+x) = setto;
}

inline int  succession_o::memcpy(void* tobcpy, const char* tobcpyed, int length)  {
    for(unsigned long int x=0; x< length; x++)  *((char*)tobcpy+x) = *(tobcpyed+x);
}


#endif

/******************************************************************************/
