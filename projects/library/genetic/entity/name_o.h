/**  name_o.h  *****************************************************************

    12.31.1999  Performance Server Library v2.000





when      who     what
9.24.96   Dan     Creation.
6.22.96   Dan     Changed:  Name of object from name_ to name_o.  Using string_o
                            object now.
7.31.98   Dan     Changed:  Placed names in a const char, removed file i/o. 
9.2.99    Dan     Changed:  Using global object's rand object now.
12.24.99  Dan     Changed:  Not using global object.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef NameOBJECT_API
#define NameOBJECT_API


static const char* Names[] = {"joey","kim","ray","kathy","harry","johnny",
"liz","lynn","norman","anable","paul","robert","justin","lori","lonnie",
"dora","regina","claudia","max","frank","jennifer","ed","jane","joe",
"jill","jack","misty","jessica","dan","mike","matt","dave","mary","tom",
"jerry","homer","bart","snoopy","lucy","rob","robin","terri","terry",
"lou","bob","randy","pat","art","mary-ann","mary-joe","mary-jane",
"russle","pops","daddyo","phil"};

static const int NumberOfNames = 55;


class name_o  {
  private:

  public:
    name_o();
    name_o(const name_o&);
    virtual    ~name_o();
    name_o&     operator = (const name_o&);

    const char* name() const;
    int         id() const;
};


#endif

/******************************************************************************/
