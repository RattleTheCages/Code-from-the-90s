/**  queue.h  ******************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Queue Object Template.

    This Queue Object is designed for and safe in multithreaded environments.
    Objects are placed at the tail of the queue via the put method.  Objects
    are removed from the head of the queue via the get method.  It is
    guaranteed that each distinct object, placed in this Queue Object, will be
    obtained by only one thread, even in the worst case, concurrent get calls.

    This Queue Object Template functions in two states, retain and release
    modes.  The default mode is the retain mode.

    In the retain mode, if there are objects on the queue, threads pass through
    the get method call obtaining an object.  If there are no objects on the
    queue, threads are blocked on the get method call until an object arrives
    on the queue or the release method is called.  If the release method is
    called when there are waiting threads, the threads are sent on their way
    with NULL objects.

    In the release mode, if there are objects on the queue, threads pass
    through the get method call obtaining an object.  If there are no objects
    on the queue, threads pass through the get method call obtaining a NULL
    object.

    Objects placed in this queue, via a put call, are this Queue Object's
    responsibility to delete.  Objects removed from the queue, via the get
    call, are the responsibility of the get method's caller to delete.  If the
    Queue Object's destructor is called, it will call the destructor of any and
    all objects remaining in the queue.

    Some copy constructors and assignement operators are declared but do not
    have code associated with them.  This is so the assignment operators and
    copy constuctors are not inadvertently used.  If they are used, without
    code assigned to them, the linker will flag an unresolved symbol.  Since
    the objects contained in the Queue Container Object are not really the
    property of the Queue Container Object, it has no business making copies of
    the object.  Similarly, the entire queue should not be allowed to make a
    copy via a copy constructor.

    Daniel Huffman




changes log:
when       who     what
4.28.99    Dan     Creation.

*******************************************************************************/


#ifndef QUEUETEMPLATE_API
#define QUEUETEMPLATE_API

#include "../../lib/thread/mutex.h"


template<class o> class queuePouch_o  {
  //friend class queue_o;
  //private
  public:
    o*                  object;
    queuePouch_o<o>*    next;

  public:
    queuePouch_o();                                     // Default constructor.
    queuePouch_o(const queuePouch_o<o>&);               // Copy constructor.
    queuePouch_o(o*);                                   // Store this object.
   ~queuePouch_o();                                     // Default destructor.
    queuePouch_o<o>& operator = (const queuePouch_o<o>&);
                                                        // Assignment operator.
};

template<class o> class queue_o  {
  private:
    mutex_o             mutex;

    queuePouch_o<o>*    first;
    queuePouch_o<o>*    last;

    unsigned int        Retain;
    unsigned int        Cardinal;
    unsigned int        DormentThreads;

  public:   
    queue_o();                                          // Default constructor.
    queue_o(const queue_o<o>&);                         // Copy constructor.
   ~queue_o();                                          // Default destructor.
    queue_o<o>& operator = (const queue_o<o>&);         // Assignment operator.

    unsigned int    put(o*);         // Places the given object at the tail of
                                     // the queue.  Returns queue cardinality.
    o*              get();           // Returns the object at the head of the
                                     // queue and removes the object from the
                                     // queue.

    unsigned int    cardinality()     const;
                                     // Returns the number of objects waiting 
                                     // on the queue.
    int             dormentThreads()  const;
                                     // Returns the number of threads waiting
                                     // for objects to be placed ob the queue.

    void            retain();        // Have threads wait on the queue for
                                     // queue objects to be placed on the queue
                                     // via a put method.
    int             release();       // Releases dorment threads without an
                                     // object from the queue.  Any threads
                                     // that come into the queue are sent on
                                     // their way with NULL objects until a
                                     // retain method is called.  The default
                                     // toggle status is retain.  Returns the
                                     // number of threads released.
};


/******************************************************************************/


template<class o> queuePouch_o<o>::queuePouch_o()  {
    object  = NULL;
    next    = NULL;
}

template<class o> queuePouch_o<o>::queuePouch_o(o* obj)  {
    object = obj;
    next   = NULL;
}

template<class o> queuePouch_o<o>::~queuePouch_o()  {}

template<class o> queue_o<o>::queue_o():mutex("queue_o")  {
    first           = NULL;
    last            = NULL;
    Retain          = 1;
    Cardinal        = 0;
    DormentThreads  = 0;
}

template<class o> queue_o<o>::~queue_o()  {
    queuePouch_o<o>*  qc;
    while(first)  {
        qc      = first;
        first   = first->next;
        delete qc->object;
        delete qc;
    }
}

template<class o> unsigned int queue_o<o>::put(o* obj)  {
    unsigned int          c;
    queuePouch_o<o>*  qc = new queuePouch_o<o>(obj);

    mutex.lock("put()");
        if(!last)  first = last = qc;
        else  {
            last->next = qc;
            last = qc;
        }
        c = (Cardinal++);
    mutex.broadcast("put()");
    mutex.unlock("put()");
    return c;
}

template<class o> o* queue_o<o>::get()  {
    o*                    obj;
    queuePouch_o<o>*  qc;

    mutex.lock("get()");
        DormentThreads++;
        while(!first && Retain)  mutex.wait("get()");
        DormentThreads--;

        qc = first;
        if(first)  {
            first = first->next;
            if(!first)  last = first;
            Cardinal--;
        }
    mutex.unlock("get()");

    if(qc)  {
        obj = qc->object;
        delete qc;
    }
    else  obj = NULL;
    return obj;
}

template<class o> inline unsigned int queue_o<o>::cardinality() const  {
    return Cardinal;
}

template<class o> inline int queue_o<o>::dormentThreads() const  {
    return DormentThreads;
}

template<class o> void queue_o<o>::retain()  {
    mutex.lock("retain()");
        Retain = 1;
    mutex.unlock("retain()");
}

template<class o> int queue_o<o>::release()  {
    int nt;
    mutex.lock("release()");
        Retain    = 0;
        nt        = Cardinal;
    mutex.broadcast("release()");
    mutex.unlock("release()");
    return nt;
}


#endif

/******************************************************************************/
