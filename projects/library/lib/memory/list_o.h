/**  list_o.h  *****************************************************************

    12.31.1999  Performance Server Library v2.000




    List Object Template.

    This list is not thread safe.  Try thread safe memory objects in the
    memory directory.



changed log
date
5.5.99    Dan    Created.




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef ListTEMPLATE_API
#define ListTEMPLATE_API


template<class o> class list_o;

template<class o> class listParcel_o  {
  friend class list_o<o>;
  private:
    o*                object;
    listParcel_o<o>*  next;

  public:
    listParcel_o();
    listParcel_o(const listParcel_o<o>&);
    listParcel_o(o*);
    virtual         ~listParcel_o();
    listParcel_o<o>& operator = (const listParcel_o<o>&);
};

template<class o> class list_o  {
  private:
    listParcel_o<o>*  First;
    listParcel_o<o>*  Last;
    listParcel_o<o>*  Current;
    unsigned int      Cardinal;

  public:   
    list_o();
    list_o(const list_o<o>&);
    virtual   ~list_o();
    list_o<o>& operator = (const list_o<o>&);

    void            put(o*);         // Places the given object at the tail of
                                     // the list.
    o*              get();           // Returns the object at the head of the
                                     // list and removes the object from the
                                     // list.
    o*              first();         // Returns the first object in the list
                                     // and does not remove the object.
    o*              next();          // Returns the next object on the list,
                                     // after calling first, returns successive
                                     // list objects.  Does not remove the
                                     // objects from the list.

    unsigned int    cardinality()   const;
                                     // Returns the number of objects in
                                     // the list.

    o*              operator++(void);
    o*              operator++(int);
};


/******************************************************************************/


template<class o> listParcel_o<o>::listParcel_o()  {
    object = NULL;
    next   = NULL;
}

template<class o> listParcel_o<o>::listParcel_o(o* obj)  {
    object = obj;
    next   = NULL;
}

template<class o> listParcel_o<o>::~listParcel_o()  {}

template<class o> list_o<o>::list_o()  {
    First = Last = Current  = NULL;
    Cardinal                = 0;
}

template<class o> list_o<o>::~list_o()  {
    listParcel_o<o>* lp;
    while(First)  {
        lp    = First;
        First = First->next;
//      delete lp->object;
        delete lp;
    }
}

template<class o> void list_o<o>::put(o* obj)  {
    listParcel_o<o>* lp = new listParcel_o<o>(obj);

    if(!Last)  First = Last = lp;
    else  {
        Last->next = lp;
        Last = lp;
    }
    Cardinal++;
}

template<class o> o* list_o<o>::get()  {
    listParcel_o<o>*  lp;
    o*                obj;

    lp = First;
    if(First)  {
        First = First->next;
        if(!First)  Last = First;
        Cardinal--;
    }

    if(lp)  {
        obj = lp->object;
        delete lp;
    }
    else  obj = NULL;
    return  obj;
}

template<class o> o* list_o<o>::operator++(int)  {
    return  get();
}

template<class o> o* list_o<o>::operator++(void)  {
    return  get();
}

template<class o> inline unsigned int list_o<o>::cardinality() const  {
    return  Cardinal;
}

template<class o> inline o* list_o<o>::first()  {
    Current = First;
    if(Current)  return First->object;
    return NULL;
}

template<class o> inline o* list_o<o>::next()  {
    if(Current)  Current = Current->next;
    if(Current)  return Current->object;
    return NULL;
}



#endif

/******************************************************************************/
