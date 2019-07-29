/**  list.h  *******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman




    List Object Template.

    This list is not thread safe.  For thread safe memory objects see the
    memory directory.



changed log
date
5.5.99    Dan    Created.

*******************************************************************************/


#ifndef LISTTEMPLATE_API
#define LISTTEMPLATE_API


template<class o> class listPouch_o  {
  friend class list_o<o>;
  private:
    o*                  object;
    listPouch_o<o>* next;

  public:
    listPouch_o();                                      // Default constructor.
    listPouch_o(const listPouch_o<o>&);                 // Copy constructor.
    listPouch_o(o*);                                    // Store this object.
   ~listPouch_o();                                      // Default destructor.
    listPouch_o<o>& operator = (const listPouch_o<o>&); // Assignment operator.
};

template<class o> class list_o  {
  private:
    listPouch_o<o>*  First;
    listPouch_o<o>*  Last;
    listPouch_o<o>*  Current;

    unsigned int     Cardinal;

  public:   
    list_o();                                           // Default constructor.
    list_o(const list_o<o>&);                           // Copy constructor.
   ~list_o();                                           // Default destructor.
    list_o<o>& operator = (const list_o<o>&);           // Assignment operator.

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

    unsigned int    cardinality()     const;
                                     // Returns the number of objects in
                                     // the list.
};


/******************************************************************************/


template<class o> listPouch_o<o>::listPouch_o()  {
    object = NULL;
    next   = NULL;
}

template<class o> listPouch_o<o>::listPouch_o(o* obj)  {
    object = obj;
    next   = NULL;
}

template<class o> listPouch_o<o>::~listPouch_o()  {}

template<class o> list_o<o>::list_o()  {
    First = Last = Current  = NULL;
    Cardinal                = 0;
}

template<class o> list_o<o>::~list_o()  {
    listPouch<o>* lp;
    while(First)  {
        lp    = First;
        First = First->next;
        delete lp->object;
        delete lp;
    }
}

template<class o> void list_o<o>::put(o* obj)  {
    listPouch<o>* lp = new listContainer_o<o>(obj);

    if(!Last)  First = Last = lp;
    else  {
        Last->next = lp;
        Last = lp;
    }
    Cardinal++;
}

template<class o> o* list_o<o>::get()  {
    listPouch<o>* lp;
    o*                  obj;

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
    return obj;
}

template<class o> inline unsigned int list_o<o>::cardinality() const  {
    return Cardinal;
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
