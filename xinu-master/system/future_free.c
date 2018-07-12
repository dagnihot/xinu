#include <xinu.h>

syscall future_free(future * f) {
    intmask mask = disable();
    
    if (f == NULL || isbadpid(f->pid)) {
        restore(mask);
        return SYSERR;
    }
    
    syscall result_of_free_value = freemem((char *) f->value, sizeof(int));
    syscall result_of_free_struct = freemem((char *) f, sizeof(future));
    
    syscall res = SYSERR;
    
    if (result_of_free_struct == OK && result_of_free_value == OK) {
        res = OK;
    }
    
    restore(mask);
    return res;
}
