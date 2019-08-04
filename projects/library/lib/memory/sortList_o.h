/**  sortList_o.h  **  ********************************************************

    07.31.2019  Performance Server Library v2.000           (The Lost Episodes.)



    Sorted List Object Template.

    This list is not thread safe.  Try thread safe memory objects in the
    memory directory.



changes log
when      who     what
7.31.19   Dan     Creation.





                           Copyright 2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef SortedListTEMPLATE_API
#define SortedListTEMPLATE_API


template<class o> class sortList_o;

template<class o> class listClutch_o  {
  friend class sortList_o<o>;
  private:
    o*                object;
    int               key;
    listClutch_o<o>*  next;

  public:
    listClutch_o();
    listClutch_o(const listClutch_o<o>&);
    listClutch_o(int, o*);
    virtual         ~listClutch_o();
    listClutch_o<o>& operator = (const listClutch_o<o>&);
};

template<class o> class sortList_o  {
  private:
    listClutch_o<o>*  First;
    listClutch_o<o>*  Current;
    unsigned int      Cardinal;

  public:   
    sortList_o();
    sortList_o(const sortList_o<o>&);
    virtual       ~sortList_o();
    sortList_o<o>& operator = (const sortList_o<o>&);

    void            put(int, o*);    // Places the given object in order in
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


template<class o> listClutch_o<o>::listClutch_o()  {
    object = NULL;
    key    = 0;
    next   = NULL;
}

template<class o> listClutch_o<o>::listClutch_o(int key, o* obj)  {
    object = obj;
    this->key = key;
    next   = NULL;
}

template<class o> listClutch_o<o>::~listClutch_o()  {}

template<class o> sortList_o<o>::sortList_o()  {
    First = Current  = NULL;
    Cardinal                = 0;
}

template<class o> sortList_o<o>::~sortList_o()  {
    listClutch_o<o>* lp;
    while(First)  {
        lp    = First;
        First = First->next;
        delete lp;
    }
}

template<class o> void sortList_o<o>::put(int key, o* obj)  {
    listClutch_o<o>* lp = new listClutch_o<o>(key, obj);
    listClutch_o<o>* last;
    listClutch_o<o>* current;

    if(!First)  First = lp;
    else  {
        current = First;
        if(First->key > key)  {
            First = lp;
            lp->next = current;
        }
        else  { 
            while(current)  {
                last = current;
                current = current->next;
               if(!current)  last->next = lp;
               else if(current->key > key)  {
                   last->next = lp;
                   lp->next = current;
                   break;
               }
           }
        }
    }
    Cardinal++;
}

template<class o> o* sortList_o<o>::get()  {
    listClutch_o<o>*  lp;
    o*                obj;

    lp = First;
    if(First)  {
        First = First->next;
        Cardinal--;
    }

    if(lp)  {
        obj = lp->object;
        delete lp;
    }
    else  obj = NULL;
    return  obj;
}

template<class o> o* sortList_o<o>::operator++(int)  {
    return  get();
}

template<class o> o* sortList_o<o>::operator++(void)  {
    return  get();
}

template<class o> inline unsigned int sortList_o<o>::cardinality() const  {
    return  Cardinal;
}

template<class o> inline o* sortList_o<o>::first()  {
    Current = First;
    if(Current)  return First->object;
    return NULL;
}

template<class o> inline o* sortList_o<o>::next()  {
    if(Current)  Current = Current->next;
    if(Current)  return Current->object;
    return NULL;
}



#endif

/******************************************************************************/
