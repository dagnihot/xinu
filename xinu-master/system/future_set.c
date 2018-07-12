#include <xinu.h>

syscall future_set(future *f, int *value) {
    intmask mask = disable();
    
    if (f == NULL || isbadpid(f->pid) || f->state == FUTURE_VALID) {
        restore(mask);
        return SYSERR;
    }
    
    if (f->state == FUTURE_EMPTY || f->state == FUTURE_WAITING) {
        f->value = (int*) getmem(sizeof(int));
        *(f->value) = *value;
        // f->value = *value;
        f->state = FUTURE_VALID;
        
        resume(f->pid);
        
        restore(mask);
        return OK;
    }
    
    restore(mask);
    return SYSERR;
}
