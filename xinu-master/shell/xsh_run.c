#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

shellcmd xsh_run(int nargs, char *args[]) {
    int i = 0;
    
    if (nargs == 2 && strncmp(args[1], "--help", 6) == 0) {
        kprintf("Usage: %s\n\n", args[0]);
        kprintf("Description:\n");
        kprintf("\tRuns test programs\n");
        kprintf("\tArguments taken from the command line --help and name of test program.\n");
        kprintf("\nOptions (one per invocation):\n");
        kprintf("\t--help\tdisplay this help message and exit\n");
        kprintf("\tfuture_test -r\tRuns the future test program with argument -r\n");
        return SHELL_OK;
    }
    
    /*
     * Prints if there no arguments are provided
     */
    if (nargs == 1) {
        kprintf("No test function provided as an argument!\n");
        return SHELL_OK;
    }
    
    /*
     * Prints if there more than 3 arguments
     */
    if (nargs > 3) {
        fprintf(stderr, "%s: too many arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
        return SHELL_ERROR;
    }
    
    /*
     * Prints if there are less than or equal to one arguments
     */
    if (nargs <= 1) {
        fprintf(stderr, "%s: too few arguments\n", args[0]);
        fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
        return SHELL_ERROR;
    }
    
    /*
     * Argument processes
     */
    for(i = 1; i < nargs; i += 2){
        if (strncmp(args[i], "future_test", 2) == 0) {
            if (nargs > 3) {
                kprintf("future_test can't take more than 2 arguments!\n");
                return SHELL_ERROR;
            }
            
            args++;
            future_test(2, args);
        } else {
            kprintf("Invalid Argument Detected! Terminating process!\n");
            return SHELL_ERROR;
        }
    }
    
    return SHELL_OK;
}
