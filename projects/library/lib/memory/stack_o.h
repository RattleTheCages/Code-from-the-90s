/**  stack_o.h  ****************************************************************

    12.31.2019  Performance Server Library v2.000           (The lost episodes.)



    Stack Object Template.

    This list is not thread safe.  Try thread safe memory objects in the
    memory directory.





                           Copyright 2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef StackTEMPLATE_API
#define StackTEMPLATE_API


template<class o> class stack_o;

template<class o> class stackSack_o  {
  friend class stack_o<o>;
  private:
    o*              object;
    stackSack_o<o>* next;

  public:
    stackSack_o();
    stackSack_o(const stackSack_o<o>&);
    stackSack_o(o*);
    virtual        ~stackSack_o();
    stackSack_o<o>& operator = (const stackSack_o<o>&);
};

template<class o> class stack_o  {
  private:
    stackSack_o<o>* Top;
    stackSack_o<o>* Current;
    unsigned int    Cardinal;

  public:   
    stack_o();
    stack_o(const stack_o<o>&);
    virtual    ~stack_o();
    stack_o<o>& operator = (const stack_o<o>&);

    void            push(o*);        // Places the given object at the top of
                                     // the stack.
    o*              pop();           // Returns the object at the top of the
                                     // stack and removes the object from the
                                     // stack.

    unsigned int    cardinality()   const;
                                     // Returns the number of objects in
                                     // the list.
};


/******************************************************************************/


template<class o> stackSack_o<o>::stackSack_o()  {
    object = NULL;
    next   = NULL;
}

template<class o> stackSack_o<o>::stackSack_o(o* obj)  {
    object = obj;
    next   = NULL;
}

template<class o> stackSack_o<o>::~stackSack_o()  {}

template<class o> stack_o<o>::stack_o()  {
    Top = Current  = NULL;
    Cardinal       = 0;
}

template<class o> stack_o<o>::~stack_o()  {
    stackSack_o<o>* ss;
    stackSack_o<o>* ssl;
    ss = Top; 
    while(ss)  {
        ssl = ss->next;
        delete ss;
        ss = ssl;
    }
}

template<class o> void stack_o<o>::push(o* obj)  {
    stackSack_o<o>* ss = new stackSack_o<o>(obj);
    stackSack_o<o>* ssl;

    ssl = Top;
    Top = ss;
    Top->next = ssl;

    Cardinal++;
}

template<class o> o* stack_o<o>::pop()  {
    stackSack_o<o>* ss;
    o*              obj;

    if(!Top)  return  NULL;

    ss = Top;
    Top = Top->next;
    obj = ss->object;
    delete ss;

    Cardinal--;
    return  obj;
}

template<class o> inline unsigned int stack_o<o>::cardinality() const  {
    return Cardinal;
}


#endif

/******************************************************************************/
