#include <xinu.h>

syscall future_get(future* f, int* value) {
    intmask mask = disable();
    
    if (f == NULL || isbadpid(f->pid) || f->state == FUTURE_WAITING) {
        restore(mask);
        return SYSERR;
    }
    
    f->state = FUTURE_WAITING;
    f->pid = getpid();
    
    suspend(getpid());
    
    *value = *(f->value);
    // *value = f->value;
    f->state = FUTURE_EMPTY;
    f->pid = NULLPROC;
    
    restore(mask);
    return OK;
}
