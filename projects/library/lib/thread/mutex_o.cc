/**  mutex_o.cc  ***************************************************************

    12.31.1999  Performance Server Library v2.000


    Mutal Exclusion Abstration Object.



changes log
Date      who     what
4.29.99   Dan     Creation.



                      Copyright 1999-2019  Daniel Huffman  All rights reserved.

*******************************************************************************/


#include <errno.h>
#include "mutex_o"


mutex_o::mutex_o()  {
    if(::pthread_mutex_init(&Mutex, NULL))  {
        ((error_o*)this)->thread(errno);
        return;
    }

    if(::pthread_cond_init(&ConditionVariable, NULL))  {
        ((error_o*)this)->thread(errno);
        return;
    }
}

mutex_o::mutex_o(const char* name)  {
    ObjectName = name;

    if(::pthread_mutex_init(&Mutex, NULL))  {
        ((error_o*)this)->thread(errno);
        return;
    }

    if(::pthread_cond_init(&ConditionVariable, NULL))  {
        ((error_o*)this)->thread(errno);
        return;
    }
}

mutex_o::~mutex_o()  {
    if(::pthread_mutex_destroy(&Mutex))  {
        ((error_o*)this)->thread(errno);
        return;
    }
    if(::pthread_cond_destroy(&ConditionVariable))  {
        ((error_o*)this)->thread(errno);
        return;
    }
}

int mutex_o::lock(const char* func)  {
    if(::pthread_mutex_lock(&Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::lock()  {
    if(::pthread_mutex_lock(&Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::unlock()  {
    if(::pthread_mutex_unlock(&Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::unlock(const char* func)  {
    if(::pthread_mutex_unlock(&Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::wait(const char* func)  {
    if(::pthread_cond_wait(&ConditionVariable, &Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::wait(mutex_o& mutex, const char* func)  {
    if(::pthread_cond_wait(&ConditionVariable, &mutex.Mutex))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}

int mutex_o::broadcast(const char* func)  {
    if(::pthread_cond_broadcast(&ConditionVariable))  {
        ((error_o*)this)->thread(errno);
    }
    return  error();
}


/******************************************************************************/
