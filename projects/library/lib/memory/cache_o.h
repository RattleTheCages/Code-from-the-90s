/**  cache_o.h  ****************************************************************

 Copyright 12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Thread Safe Cache Binary Search Tree Object Template.

    The Cache Binary Search Tree Template Object is included because the AIX
    system included hash table methods are not supported in a multithreaded
    environment.  This information is disclosed in the AIX system manuals.

    This Cache Binary Search Tree Template Object is designed to support
    multiple threads searching the tree concurrently and allow threads to
    insert objects into the tree at anytime.  This tree is not balanced;
    balancing would lock out searching threads for a long period of time.
    Tree balancing is omitted for the sake of search availability.  Since
    balancing is not done, the objects inserted in this tree should not be in
    sorted order.  Generally, a cache is meant to hold objects that have been
    called up in random order.  Use this Cache Object when inserted objects
    are generally not in order.  Searching, then, has an upper bound of
    O(lg n).  Variable n being the cardinality of the cache.

    In adhering to the general concept of a cache, in the successive insertion
    of matching keys, the new object replaces the old object for that key.  The
    old object's destructor is called.


    This tree guarantees that threads can search and insert concurrently, and
    without starvation for either searchers or inserters.  This problem
    parallels the famous Computer Science readers-writers problem.  Looking
    through my copy of Operating Systems Concepts by Silberschatz and Galvin,
    ISBN 0-201-50480-4, there are three solutions to this problem.  One,
    creates a situation where starvation for writers can occur.  Two, creates
    a solution where starvation for readers may occur.  Solution three,
    the solution that neither readers nor writers will starve, was left as an
    exercise, and appeared on the mid-term test.  My archive contains the
    solution, but is hard to access.  In the interest of saving time, the
    readers-writers algorithm used below was designed this evening, not
    researched.

    lock: write
    lock: read
    int:  R = 0
    int:  W = 0
 
    Reader:                                 Writer:
    lock(write)                             lock(write)
        while(W != 0)  wait(write)              while(W != 0)  wait(write)
    unlock(write)                               W++
    lock(read)                              unlock(write)
        R++                                 lock(read)
    unlock(read)                                while(R != 0)  wait(read)
                                            unlock(read)

    Read Object                             Write Object

    lock(read)                              lock(write)
        R--                                     W--
    unlock(read)                            unlock(write)
    broadcast(read)                         broadcast(write)


    One final design question must be addressed.  It is feasible to place
    one set of reader-writer locks around each object in the tree, or place
    one set of reader-writer locks around the entire tree.

    Placing one set of locks in each object in the tree would take more memory
    for each object in the tree; so the total memory this tree would use would
    be larger.  The question of how many outstanding lock resources the
    underlying operating system can assign is not answered.  If this resource
    is limited, the cache size would be limited, and other problems would
    occur as other parts of the system wants lock resources.

    The draw back of using one set of reader-writer locks around the entire
    tree, is that performance will be slightly degraded compared to the other
    solution.

    This Cache Object chooses the slight performance hit over the possible
    robustness problems.  One reader-writer lock set is placed around the
    entire tree.


    It is the user of this Cache Object responsiblity to make sure that all
    instantiated Cache Search Objects have their destructor's called.  Until
    the destructor for a Cache Search Object is called, threads that need
    to insert will be locked out.  Keeping a Cache Search Object instantiated
    indefinitely can cause deadlock.

    Objects placed into this Cache Object become the property of this Cache
    Object.  Do not use, change, or delete objects after being placed into
    the cache.  When the Cache Object's destructor is called, all the
    destructors of the objects placed in the cache are called.

    Cache Search Objects searching a Cache Object whose destructor has been
    called may yield unpredictable results.  Do not delete a Cache Object
    until all of the Cache Search Objects have been deleted.


    Reuse of this object can be done by removing all references of the Memory
    Manager Object, if desired.  The Mutex Object abstracts the operating
    systems locking resources.  Replace the Mutex Object with the navtive
    operating system's lock resources.  With the Memory Manager Object and the
    Mutex Object removed, this Cache Binary Search Tree Object is not dependant
    opon any other objects, and can be easily reused.




changes log
when      who       when
5.9.99    Dan       Creation.
9.9.99    Dan       Fixed:    Bug in cacheSearch_o::listhead().


*******************************************************************************/


#ifndef CacheTEMPLATE_API
#define CacheTEMPLATE_API

#define CacheTEMPLATE_MAX_CACHE_SIZE    65535

#include "string_o.h"
#include "mutex_o.h"


template<class o> class cachePouch_o  {
  friend class cache_o<o>;
  friend class cacheSearch_o<o>;
  private:
    o*                  object;
    string_o            key;
    cachePouch_o<o>*    left;
    cachePouch_o<o>*    right;
    cachePouch_o<o>*    next;

  public:
    cachePouch_o();
    cachePouch_o(const cachePouch_o<o>&);
    cachePouch_o(const string_o&,o*);
    virtual         ~cachePouch_o();
    cachePouch_o<o>& operator = (const cachePouch_o<o>&);

    int       leaf()    const;
    const o*  Object()  const;
};

template<class o> class cache_o  {
  private:
    cachePouch_o<o>*   root;
    cachePouch_o<o>*   listhead;
    cachePouch_o<o>*   listtail;
    unsigned long      cardinal;
    unsigned long      maxsize;
    mutex_o            readersmutex;
    mutex_o            writersmutex;
    int                readers;
    int                writers;

    unsigned long   insert(cachePouch_o<o>*);
    void            clear(cachePouch_o<o>*);

  public:   
    cache_o();
    cache_o(const cache_o<o>&);
    cache_o(unsigned long);         
   ~cache_o();
    cache_o<o>& operator = (const cache_o<o>&);

          unsigned long         insert(const string_o&,o*);
                                          // The string is copied, the object
                                          // is placed in the tree as is,
                                          // (Don't delete or use it after
                                          // placing it into the tree!)
                                          // The insert will insert objects
                                          // until max cache size is reached.
                                          // Returns number of objects in the
                                          // cache.
            
          unsigned long     cardinality()             const;
    const cachePouch_o<o>*  getroot()                 const;
    const cachePouch_o<o>*  list()                    const;

          void              newsearcher();
          void              deletesearcher();
};


template<class o> class cacheSearch_o  {
  private:
          cache_o<o>*      bstree;
    const cachePouch_o<o>* listcurrent;

  public:
    cacheSearch_o();
    cacheSearch_o(const cacheSearch_o<o>&);
    cacheSearch_o(cache_o<o>*);
   ~cacheSearch_o();
    cacheSearch_o<o>& operator = (const cacheSearch_o<o>&);

    const o*                    find(const string_o&)     const;
          int                   contains(const string_o&) const;
    const o*                    listhead();
    const o*                    listnext();
          unsigned long         cardinality()             const;

};


/******************************************************************************/


template<class o> cachePouch_o<o>::cachePouch_o()  {
    object  = NULL;
    right   = NULL;
    left    = NULL;
    next    = NULL;
}

template<class o> cachePouch_o<o>::cachePouch_o(const string_o& k,o* obj)  {
    key     = k;
    object  = obj;
    right   = NULL;
    left    = NULL;
    next    = NULL;
}

template<class o> cachePouch_o<o>::~cachePouch_o()  {
    delete object;
}

template<class o> inline const o* cachePouch_o<o>::Object() const  {
    return object;
}

template<class o> inline int cachePouch_o<o>::leaf() const  {
    if(right == NULL && left == NULL)  return 1;
    return 0;
}

template<class o> cache_o<o>::cache_o():
    readersmutex("cache reader"), writersmutex("cache writer")  {
    root     = NULL;
    listhead = NULL;
    listtail = NULL;
    cardinal = 0;
    maxsize  = CacheTEMPLATE_MAX_CACHE_SIZE;
    readers  = 0;
    writers  = 0;
}

template<class o> cache_o<o>::cache_o(unsigned long ms):
    readersmutex("cache reader"), writersmutex("cache writer")  {
    root     = NULL;
    listhead = NULL;
    listtail = NULL;
    cardinal = 0;
    maxsize  = ms;
    readers  = 0;
    writers  = 0;
}

template<class o> cache_o<o>::~cache_o()  {
    while(listhead)  {
        root = listhead;
        listhead = listhead->next;
        delete root;
    }
}

template<class o> void cache_o<o>::newsearcher()  {
    writersmutex.lock("newsearcher()");
        while(writers != 0)  writersmutex.wait("new searcher()");
    writersmutex.unlock("new searcher()");
    readersmutex.lock("new searcher()");
        readers++;
    readersmutex.unlock("new searcher()");
}

template<class o> void cache_o<o>::deletesearcher()  {
    readersmutex.lock("delete searcher()");
        readers--;
    readersmutex.unlock("delete searcher()");
    readersmutex.broadcast("delete searcher()");
}

template<class o> unsigned long cache_o<o>::insert(const string_o& key,o* obj) {
    unsigned long ret;
    if(maxsize <= cardinal)  return cardinal;


    writersmutex.lock("insert()");
        while(writers != 0)  writersmutex.wait("insert()");
        writers++;
    writersmutex.unlock("insert");
    readersmutex.lock("insert");
        while(readers != 0)  readersmutex.wait("insert()");
    readersmutex.unlock("insert");


        if(cardinal < CacheTEMPLATE_MAX_CACHE_SIZE)  {
            cachePouch_o<o>*  bstC = new cachePouch_o<o>(key,obj);
            if(!listhead)  listhead = listtail = bstC;
            else  {
                listtail->next = bstC;
                listtail = bstC;
            }
            ret = insert(bstC);
        }
        else  ret = cardinal;


    writersmutex.lock("insert()");
        writers--;
    writersmutex.unlock("insert()");
    writersmutex.broadcast("insert()");


    return ret;
}

template<class o> unsigned long cache_o<o>::insert(cachePouch_o<o>* bstC)  {
    cachePouch_o<o>*  current;
    cachePouch_o<o>*  previous;
    if(!root)  root = bstC;
    else  {
        current = root;
        while(current && !(current->key == bstC->key))  {
            previous = current;
            if(bstC->key < current->key)  current = current->left;
            else  current = current->right;
        }
        if(previous->key == bstC->key)  {
            current = previous;
            bstC->left  = previous->left;
            bstC->right = previous->right;
            bstC->next  = previous->next;
            previous = bstC;
            delete current;
        }
        if(bstC->key < previous->key)  previous->left = bstC;
        else  previous->right = bstC;
    }
    cardinal++;
    return cardinal;
}

template<class o> inline unsigned long cache_o<o>::cardinality() const  {
    return cardinal;
}

template<class o> inline const cachePouch_o<o>* cache_o<o>::getroot() const  {
    return root;
}

template<class o> inline const cachePouch_o<o>* cache_o<o>::list() const  {
    return listhead;
}

template<class o> cacheSearch_o<o>::cacheSearch_o(cache_o<o>* bstreeIn)  {
    bstree      = bstreeIn;
    listcurrent = NULL;
    bstree->newsearcher();
}

template<class o> cacheSearch_o<o>::~cacheSearch_o()  {
    bstree->deletesearcher();
}

template<class o> const o* cacheSearch_o<o>::find(const string_o& key) const  {
    const cachePouch_o<o>*  place;
    const o*                    obj;

    if(!bstree || !bstree->getroot())  return NULL;
    place = bstree->getroot();
    while(place)  {
        if(place->key == key)  break;
        if(key < place->key)   place = place->left;
        else  place = place->right;
    }

    if(place)  obj = place->object;
    else       obj = NULL;
    return obj;
}

template<class o> int cacheSearch_o<o>::contains(const string_o& key) const  {
    const cachePouch_o<o>* place;
    if(!bstree || !bstree->getroot())  return 0;
    place = bstree->getroot();
    while(place)  {
        if(place->key == key)  return 1;
        if(place->key  > key)  place = place->left;
        else  place = place->right;
    }
    return 0;
}

template<class o> inline const o* cacheSearch_o<o>::listhead()  {
    listcurrent = bstree->list();
    if(listcurrent)  return listcurrent->Object();
    return NULL;
}

template<class o> inline const o* cacheSearch_o<o>::listnext()  {
    if(listcurrent)  listcurrent = listcurrent->next;
    if(listcurrent)  return listcurrent->object;
    return NULL;
}

template<class o> inline unsigned long cacheSearch_o<o>::cardinality() const  {
    return bstree->cardinality();
}


#endif

/******************************************************************************/
