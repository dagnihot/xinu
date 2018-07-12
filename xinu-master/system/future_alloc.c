#include <xinu.h>

future* future_alloc(int future_flags) {
    intmask mask = disable();
    
    future * mem = (future *) getmem(sizeof(future));
    
    if ((char *) mem == (char *) SYSERR) {
        restore(mask);
        return NULL;
    }
    
    mem->value = NULL;
    mem->state = FUTURE_EMPTY;
    mem->flag = future_flags;
    mem->pid = NULLPROC;
    
    restore(mask);
    return mem;
}

