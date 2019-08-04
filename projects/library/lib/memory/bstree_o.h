/**  bstree_o.h  ***************************************************************

    12.31.1999  Performance Server Library v2.000



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




                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#ifndef BSTreeTEMPLATE_API
#define BSTreeTEMPLATE_API

#ifndef NULL
#define NULL 0
#endif


#include "string_o.h"
#include "stack_o.h"

template<class o> class bstree_o;
template<class o> class bstreeSearch_o;

template<class o> class bstreeLeaf_o  {
  friend class bstree_o<o>;
  friend class bstreeSearch_o<o>;
  private:
    o*                  object;
    string_o            key;
    short               color;
    bstreeLeaf_o<o>*    left;
    bstreeLeaf_o<o>*    right;
    bstreeLeaf_o<o>*    parent;
    bstreeLeaf_o<o>*    next;

  public:
    bstreeLeaf_o();
    bstreeLeaf_o(const bstreeLeaf_o<o>&);
    bstreeLeaf_o(const string_o&,o*);
   ~bstreeLeaf_o();
    bstreeLeaf_o<o>& operator = (const bstreeLeaf_o<o>&);

    int       leaf()    const;
    const o*  Object()  const;
};


template<class o> class bstree_o  {
  private:
    bstreeLeaf_o<o>*   root;
    bstreeLeaf_o<o>*   listhead;
    bstreeLeaf_o<o>*   listtail;
    unsigned int       cardinal;

    int   insert(bstreeLeaf_o<o>*);
    void  rotateRight(bstreeLeaf_o<o>*);
    void  rotateLeft(bstreeLeaf_o<o>*);
    void  balance(bstreeLeaf_o<o>*);
    void  clear(bstreeLeaf_o<o>*);

  public:   
    bstree_o();
    bstree_o(const bstree_o<o>&);
    virtual     ~bstree_o();
    bstree_o<o>& operator = (const bstree_o<o>&);

          void                  clear();

          int                   insert(const string_o&, o*);
                                          // The string is copied, the object
                                          // is placed in the tree as is,
                                          // (Don't delete or use it after
                                          // placing it into the tree!)
            
          unsigned int          cardinality()             const;
    const bstreeLeaf_o<o>*      getRoot()                 const;
    const bstreeLeaf_o<o>*      list()                    const;
};


template<class o> class bstreeSearch_o  {
  private:
    const bstree_o<o>*          bstree;
    const bstreeLeaf_o<o>*      listCurrent;

    stack_o<const bstreeLeaf_o<o> >   sortStack;
    void sort(const bstreeLeaf_o<o>*);
          o*                    sortedListNext();


  public:
    bstreeSearch_o();
    bstreeSearch_o(const bstreeSearch_o<o>&);
    bstreeSearch_o(const bstree_o<o>*);
   ~bstreeSearch_o();
    bstreeSearch_o<o>& operator = (const bstreeSearch_o<o>&);

    const o*                    find(const string_o*)     const;
          int                   contains(const string_o*) const;
          o*                    listHead();
          o*                    listNext();
          o*                    sortedList();
          unsigned int          cardinality()             const;

          o*                    operator++(int);
          o*                    operator++(void);
};


/******************************************************************************/


template<class o> bstreeLeaf_o<o>::bstreeLeaf_o()  {
    object  = NULL;
    right   = NULL;
    left    = NULL;
    parent  = NULL;
    next    = NULL;
    color   = 0;
}

template<class o> bstreeLeaf_o<o>::bstreeLeaf_o(const string_o& k,o* obj)  {
    key     = k;
    object  = obj;
    right   = NULL;
    left    = NULL;
    parent  = NULL;
    next    = NULL;
    color   = 0;
}

template<class o> bstreeLeaf_o<o>::~bstreeLeaf_o()  {
    delete  object;
}

template<class o> inline const o* bstreeLeaf_o<o>::Object() const  {
    return  object;
}

template<class o> inline int bstreeLeaf_o<o>::leaf() const  {
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
    bstreeLeaf_o<o>*  bstC = new bstreeLeaf_o<o>(key,obj);
    if(!listhead)  listhead = listtail = bstC;
    else  {
        listtail->next = bstC;
        listtail = bstC;
    }
    return insert(bstC);
}

template<class o> int bstree_o<o>::insert(bstreeLeaf_o<o>* bstC)  {
    bstreeLeaf_o<o>*  current;
    bstreeLeaf_o<o>*  previous;
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
  //balance(bstC);
    cardinal++;
    return cardinal;
}

template<class o> void bstree_o<o>::rotateLeft(bstreeLeaf_o<o>* place)  {
    bstreeLeaf_o<o>* temp = place->right;
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

template<class o> void bstree_o<o>::rotateRight(bstreeLeaf_o<o>* place)  {
    bstreeLeaf_o<o>* temp = place->left;
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

template<class o> void bstree_o<o>::balance(bstreeLeaf_o<o>* place)  {
    bstreeLeaf_o<o>* temp;
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

template<class o> void bstree_o<o>::clear(bstreeLeaf_o<o>* place)  {
    while(place)  {
        root = place->next;
        delete place;
        place = root;
   }
}

template<class o> inline unsigned int bstree_o<o>::cardinality() const  {
    return cardinal;
}

template<class o> inline const bstreeLeaf_o<o>* bstree_o<o>::getRoot() const  {
    return root;
}

template<class o> inline const bstreeLeaf_o<o>* bstree_o<o>::list() const  {
    return listhead;
}

template<class o> bstreeSearch_o<o>::bstreeSearch_o()  {
    bstree      = NULL;
    listCurrent = NULL;
}

template<class o> bstreeSearch_o<o>::bstreeSearch_o(const bstree_o<o>* bstreeIn)  {
    bstree      = bstreeIn;
    listCurrent = NULL;
}

template<class o> bstreeSearch_o<o>::~bstreeSearch_o()  {}

template<class o> const o* bstreeSearch_o<o>::find(const string_o* key) const  {
    const bstreeLeaf_o<o>*  place;
    const o*                obj;

    if(!bstree || !bstree->getRoot())  return NULL;
    place = bstree->getRoot();
    while(place)  {
        if(place->key == *key)  break;
        if(place->key  > *key)  place = place->left;
        else  place = place->right;
    }

    if(place)  obj = place->Object();
    else       obj = NULL;
    return  obj;
}

template<class o> int bstreeSearch_o<o>::contains(const string_o* key) const  {
    const bstreeLeaf_o<o>* place;
    if(!bstree || !bstree->getRoot())  return 0;
    place = bstree->getRoot();
    while(place)  {
        if(place->key == *key)  return 1;
        if(place->key  > *key)  place = place->left;
        else  place = place->right;
    }
    return  0;
}

template<class o> inline o* bstreeSearch_o<o>::listHead()  {
    listCurrent = bstree->list();
    return  listCurrent->Object();
}

template<class o> inline o* bstreeSearch_o<o>::listNext()  {
    if(listCurrent)  listCurrent = listCurrent->next;
    if(listCurrent)  return  listCurrent->Object();
    return  NULL;
}

template<class o> inline void bstreeSearch_o<o>::sort(const bstreeLeaf_o<o>* node)  {
    if(node)  {
        if(node->right)  sort(node->right);
        sortStack.push(node);
        if(node->left)  sort(node->left);
    }
}

template<class o> inline o* bstreeSearch_o<o>::sortedList()  {
    const bstreeLeaf_o<o>* place;
    sort(bstree->getRoot());
    place = sortStack.pop();
    if(place)  return  place->object;
    return  NULL;
}

template<class o> inline o* bstreeSearch_o<o>::sortedListNext()  {
    const bstreeLeaf_o<o>* place;
    place = sortStack.pop();
    if(place)  return  place->object;
    return  NULL;
}

template<class o> inline o* bstreeSearch_o<o>::operator++(int)  {
    return  sortedListNext();
}

template<class o> inline o* bstreeSearch_o<o>::operator++(void)  {
    return  sortedListNext();
}

template<class o> inline unsigned int bstreeSearch_o<o>::cardinality() const  {
    return bstree->cardinality();
}


#endif


/******************************************************************************/
