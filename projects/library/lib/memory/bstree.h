/**  bstree.h  *****************************************************************

12.31.1999  Performance Server Library v2.000  Daniel Huffman



    Thread Safe Binary Search Tree Object Template.

    This Binary Search Tree Template Object is designed to support multipule
    threads searching the tree concurrently, where search speed and availablity
    is the top priority.  This is accomplished by the use of read only tree
    objects and search objects that keep place marks during searches.  Each
    thread instanchates its own tree search object.  This tree should not
    be searched and have objects inserted at the same time.  This tree is meant
    to be filled while searching threads are locked out.  The tree balances
    itself; The time the balancing algorithm takes, when the tree is large,
    would be prohibitive to do when searching speed and availablity is 
    paramount.  Because speed and availablity is the goal of this object,
    locks are not provided for searching and inserting.  It is the
    responsiblity of the user of this object to make sure objects are not
    inserted while threads are searching and reading.

    This binary search tree object provides a better then linear search time
    data structure that can be used in a multi-threaded enviroment.  Unlike a
    hash table whose worst case search time can be O(n), (but normaly search
    time is around O(1) plus a little), this balanced binary search tree
    provides a worst case of 2 O(lg n), and an average search time of O(lg n).

    The Binary Search Tree Templates are included because the AIX system
    included hash table methods are not supported in a mulithreaded enviroment.



changes log
when      who       when
5.9.99    Dan       Creation.
9.21.99   Dan       Fixed:    Bug in clear() methods.


*******************************************************************************/


#ifndef BSTREETEMPLATE_API
#define BSTREETEMPLATE_API

#ifndef NULL
#define NULL 0
#endif


#include "string.h"


template<class o> class bstreePouch_o  {
  private:
  public:
    o*                  object;
    string_o            key;
    short               color;
    bstreePouch_o<o>*   left;
    bstreePouch_o<o>*   right;
    bstreePouch_o<o>*   parent;
    bstreePouch_o<o>*   next;

  public:
    bstreePouch_o();
    bstreePouch_o(const bstreePouch_o<o>&);
    bstreePouch_o(const string_o&,o*);
   ~bstreePouch_o();
    bstreePouch_o<o>& operator = (const bstreePouch_o<o>&);

    int       leaf()    const;
    const o*  Object()  const;
};


template<class o> class bstree_o  {
  private:
    bstreePouch_o<o>*   root;
    bstreePouch_o<o>*   listhead;
    bstreePouch_o<o>*   listtail;
    unsigned int        cardinal;

    int   insert(bstreePouch_o<o>*);
    void  rotateRight(bstreePouch_o<o>*);
    void  rotateLeft(bstreePouch_o<o>*);
    void  balance(bstreePouch_o<o>*);
    void  clear(bstreePouch_o<o>*);

  public:   
    bstree_o();                                         // Default constructor.
    bstree_o(const bstree_o<o>&);                       // Copy constructor.
   ~bstree_o();                                         // Default desturctor.
    bstree_o<o>& operator = (const bstree_o<o>&);       // Assignement operator.

          void                  clear();

          int                   insert(const string_o&,o*);
                                          // The string is copied, the object
                                          // is placed in the tree as is,
                                          // (Don't delete or use it after
                                          // placing it into the tree!)
            
          unsigned int          cardinality()             const;
    const bstreePouch_o<o>* getroot()                 const;
    const bstreePouch_o<o>* list()                    const;
};


template<class o> class bstreeSearch_o  {
  private:
    const bstree_o<o>*      bstree;
    const bstreePouch_o<o>* listcurrent;

  public:
    bstreeSearch_o();
    bstreeSearch_o(const bstreeSearch_o<o>&);
    bstreeSearch_o(const bstree_o<o>*);
   ~bstreeSearch_o();
    bstreeSearch_o<o>& operator = (const bstreeSearch_o<o>&);

    const o*                    find(const string_o*)     const;
          int                   contains(const string_o*) const;
    const o*                    listhead();
    const o*                    listnext();
          unsigned int          cardinality()             const;
};


/******************************************************************************/


template<class o> bstreePouch_o<o>::bstreePouch_o()  {
    object  = NULL;
    right   = NULL;
    left    = NULL;
    parent  = NULL;
    next    = NULL;
    color   = 0;
}

template<class o> bstreePouch_o<o>::bstreePouch_o(const string_o& k,o* obj)  {
    key     = k;
    object  = obj;
    right   = NULL;
    left    = NULL;
    parent  = NULL;
    next    = NULL;
    color   = 0;
}

template<class o> bstreePouch_o<o>::~bstreePouch_o()  {
    delete object;
}

template<class o> inline const o* bstreePouch_o<o>::Object() const  {
    return object;
}

template<class o> inline int bstreePouch_o<o>::leaf() const  {
    if(right == NULL && left == NULL)  return 1;
    return 0;
}

template<class o> bstree_o<o>::bstree_o()  {
    root     = NULL;
    listhead = NULL;
    listtail = NULL;
    cardinal = 0;
}

template<class o> bstree_o<o>::~bstree_o()  {
    clear();
}

template<class o> int bstree_o<o>::insert(const string_o& key,o* obj)  {
    bstreePouch_o<o>*  bstC = new bstreePouch_o<o>(key,obj);
    if(!listhead)  listhead = listtail = bstC;
    else  {
        listtail->next = bstC;
        listtail = bstC;
    }
    return insert(bstC);
}

template<class o> int bstree_o<o>::insert(bstreePouch_o<o>* bstC)  {
    bstreePouch_o<o>*  current;
    bstreePouch_o<o>*  previous;
    if(!root)  root = bstC;
    else  {
        current = root;
        while(current)  {
            if(current->key == bstC->key)  return -1;
            previous = current;
            if(current->key > bstC->key)  current = current->left;
            else  current = current->right;
        }
        if(previous->key > bstC->key)  previous->left = bstC;
        else  previous->right = bstC;
        bstC->parent = previous;
    }
    balance(bstC);
    cardinal++;
    return cardinal;
}

template<class o> void bstree_o<o>::rotateLeft(bstreePouch_o<o>* place)  {
    bstreePouch_o<o>* temp = place->right;
    place->right = place->right->left;
    if(temp->left != NULL)  temp->left->parent = place;
    temp->parent = place->parent;
    if(place->parent == NULL)  root = temp;
    else  {
        if(place == place->parent->left)  place->parent->left = temp;
        else  place->parent->right = temp;
    }
    temp->left = place;
    place->parent = temp;
}

template<class o> void bstree_o<o>::rotateRight(bstreePouch_o<o>* place)  {
    bstreePouch_o<o>* temp = place->left;
    place->left = place->left->right;
    if(temp->right != NULL)  temp->right->parent = place;
    temp->parent = place->parent;
    if(place->parent == NULL)  root = temp;
    else  {
        if(place == place->parent->right)  place->parent->right = temp;
        else  place->parent->left = temp;
    }
    temp->right = place;
    place->parent = temp;
}

template<class o> void bstree_o<o>::balance(bstreePouch_o<o>* place)  {
    bstreePouch_o<o>* temp;
    place->color = 1;
    while(place != root && place->parent->color == 1)  {
        if(place->parent == place->parent->parent->left)  {
            temp = place->parent->parent->right;
            if(temp && temp->color == 1)  {
                place->parent->color = 0;
                temp->color = 0;
                place->parent->parent->color = 1;
                place = place->parent->parent;
            }
            else  {
                if(place == place->parent->right)  {
                    place = place->parent;
                    rotateLeft(place);
                }
                place->parent->color = 0;
                place->parent->parent->color = 1;
                rotateRight(place->parent->parent);
            }
        }
        else  {
            temp = place->parent->parent->left;
            if(temp && temp->color == 1)  {
                place->parent->color = 0;
                temp->color = 0;
                place->parent->parent->color = 1;
                place = place->parent->parent;
            }
            else  {
                if(place == place->parent->left)  {
                    place = place->parent;
                    rotateRight(place);
                }
                place->parent->color = 0;
                place->parent->parent->color = 1;
                rotateLeft(place->parent->parent);
            }
        }
    }
    root->color = 0;
}

template<class o> void bstree_o<o>::clear()  {
    clear(root);
    root        = NULL;
    listhead    = NULL;
    listtail    = NULL;
    cardinal    = 0;
}

template<class o> void bstree_o<o>::clear(bstreePouch_o<o>* place)  {
    if(place)  {
        if(place->left)   clear(place->left);
        if(place->right)  clear(place->right);
        delete place;
    }
}

template<class o> inline unsigned int bstree_o<o>::cardinality() const  {
    return cardinal;
}

template<class o> inline const bstreePouch_o<o>* bstree_o<o>::getroot() const  {
    return root;
}

template<class o> inline const bstreePouch_o<o>* bstree_o<o>::list() const  {
    return listhead;
}

template<class o> bstreeSearch_o<o>::bstreeSearch_o()  {
    bstree      = NULL;
    listcurrent = NULL;
}

template<class o> bstreeSearch_o<o>::bstreeSearch_o(const bstree_o<o>* bstreeIn)  {
    bstree      = bstreeIn;
    listcurrent = NULL;
}

template<class o> bstreeSearch_o<o>::~bstreeSearch_o()  {}

template<class o> const o* bstreeSearch_o<o>::find(const string_o* key) const  {
    const bstreePouch_o<o>* place;
    const o*                    obj;

    if(!bstree || !bstree->getroot())  return NULL;
    place = bstree->getroot();
    while(place)  {
        if(place->key == *key)  break;
        if(place->key  > *key)  place = place->left;
        else  place = place->right;
    }

    if(place)  obj = place->Object();
    else       obj = NULL;
    return obj;
}

template<class o> int bstreeSearch_o<o>::contains(const string_o* key) const  {
    const bstreePouch_o<o>* place;
    if(!bstree || !bstree->getroot())  return 0;
    place = bstree->getroot();
    while(place)  {
        if(place->key == *key)  return 1;
        if(place->key  > *key)  place = place->left;
        else  place = place->right;
    }
    return 0;
}

template<class o> inline const o* bstreeSearch_o<o>::listhead()  {
    listcurrent = bstree->list();
    return listcurrent->Object();
}

template<class o> inline const o* bstreeSearch_o<o>::listnext()  {
    if(listcurrent)  listcurrent = listcurrent->next;
    if(listcurrent)  return listcurrent->Object();
    return NULL;
}

template<class o> inline unsigned int bstreeSearch_o<o>::cardinality() const  {
    return bstree->cardinality();
}


#endif

/******************************************************************************/
