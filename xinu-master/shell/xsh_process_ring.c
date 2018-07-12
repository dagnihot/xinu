#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <process_ring.h>


volatile int32 inbox[64];
volatile int ring[64];
volatile int round;
volatile int parentid;
volatile int begin;

int numProcesses;
int numRounds;
int counter;
int choice;

shellcmd xsh_process_ring(int nargs, char *args[]) {
    uint32 start, stop;
    parentid = getpid();
    gettime(&start);
    
    numProcesses = 2;
    numProcesses = 3;
    choice = 3;
    round = 0;
    begin = 1;
    end = 0;
    int i = 0;
    
    if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
        printf("Usage: %s\n\n", args[0]);
        printf("Description: We shall see a countdown of numbers\n");
        printf("\tDisplays hello world to the user\n");
        return 0;
    }
    
    if (nargs == 1) {
        counter = (numProcesses * numRounds) - 1;
        inbox[0] = counter;
        
        for(i = 0; i < numProcesses; i++){
            ring[i] = create(process_ring, 1024, 20, "process_ring", 3, i, numProcesses, choice);
        }
        
        resume (ring[0]);
        suspend(parentid);
        
        for (i = 0; i < numProcesses; i++){
            kill(ring[i]);
        }
        
        gettime(&stop);
        kprintf("Elapsed Seconds: %d\n", stop - start);
        return 0;
    }
    
    
    if (nargs > 7){
        fprintf(stderr, "%s excessive number of arguments bruhhh");
    }
    
    if (nargs < 1){
        fprintf(stderr, "%s insufficient number of arguments bruhhh");
    }
    
    for (i = 1; i < nargs; i +=2){
        if (strncmp(args[i], "-p", 2) == 0){
            kprintf("Argument -p detected!\n");
            numProcesses = atoi(args[i + 1]);
            
            if (numProcesses > 64 || numProcesses < 0){
                kprintf("Invalid number of processes");
                numProcesses = 2;
            }
            
            printf("Number of processes: %d\n", numProcesses);
            
            if (numProcesses == 0){
                goto end;
            }
        } else if (strncmp(args[i], "-r", 2) == 0){
            kprintf("Argument -r detected!\n");
            numRounds = atoi(args[i + 1]);
            
            if (numRounds > 64 || numRounds < 0){
                kprintf("Invalid number of rounds");
                numRounds = 3;
            }
            
            printf("Number of rounds: %d\n", numRounds);
            
            if (numRounds == 0){
                goto end;
            }
        }
        else if (strncmp(args[i], "-i", 2) == 0) {
            kprintf("Argument -i detected!\n");
            if (strncmp(args[i + 1], "poll", 5) == 0){
                choice = 0;
            } else if (strncmp(args[i + 1], "sync", 5) == 0){
                choice = 1;
            } else {
                kprintf("Invalid implimentation\n");
                choice = 0;
            }
        } else if (i == 1 || i == 2){
            if (i == 1) {
                numProcesses = atoi(args[i]);
                i--;
                /*
                if (numRounds > 64 || numRounds < 0){
                    kprintf("Invalid number of rounds");
                    numRounds = 3;
                }
                printf("Number of rounds: %d\n", numRounds);
                
                if (numRounds == 0){
                    goto end;
                }
                 */
                if (numProcesses > 64 || numProcesses < 0){
                    kprintf("Invalid number of processes");
                    numRounds = 3;
                }
                
                printf("Number of processes: %d\n", numProcesses);
                
                if (numProcesses == 0){
                    goto end;
                }
            } else if (i == 2) {
                numRounds = atoi(args[i]);
                i--;
                if (numRounds > 64 || numRounds < 0){
                    kprintf("Invalid number of rounds");
                    numRounds = 3;
                }
                
                printf("Number of rounds: %d\n", numRounds);
                
                if (numRounds == 0){
                    goto end;
                }
            }
        }
    }
    
    
    
    counter = (numProcesses * numRounds) - 1;
    inbox[0] = counter;
    
    for (i = 0; i < numProcesses; i++) {
        ring[i] = create(process_ring, 1024, 20, "process_ring", 3, i, numProcesses, choice);
    }
    
    resume(ring[0]);
    suspend(parentid);
    
    for (i = 0; i < numProcesses; i++){
        kill(ring[i]);
    }
    
end:
    gettime(&stop);
    kprintf("Elapsed Seconds: %d\n", start - stop);
    return 0;
}
