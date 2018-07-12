#include <xinu.h>
#include <process_ring.h>

process process_ring(int process_index, int processes, int choice){
    int32 x  = -1;
    
    while (inbox[process_index] >= 0){
        if (choice == 0 && x != inbox[process_index]){
            x = inbox[process_index];
            
            if (begin == 1){
                begin = 0;
            } else {
                int process_suspend;
                
                if (process_index == 0) {
                    process_suspend = processes - 1;
                    round += 1;
                } else {
                    process_suspend = process_index - 1;
                }
                
                suspend(ring[process_suspend]);
            }
            
            int next = (process_index + 1) % processes;
            inbox[next] = inbox[process_index] - 1;
            
            kprintf("Ring element %d: Round %d : Value : %d\n", process_index, round, inbox[process_index]);
            resume(ring[next]);
        } else if (choice == 1){
            int next = (process_index + 1) % processes;
            
            if (begin == 1){
                begin = 0;
            } else {
                x = receive();
                
                if (x == 0) {
                    inbox[process_index] = x;
                    kprintf("Ring element %d: Round %d : Value : %d\n", process_index, round, inbox[process_index]);
                    goto end;
                }
                
                inbox[process_index] = x;
            }
            
            kprintf("Ring element %d: Round %d : Value : %d\n", process_index, round, inbox[process_index]);
            send(ring[next], inbox[process_index] - 1);
            resume(ring[next]);
        }
        
    }
    
end:
    resume(parentid);
    return 0;
}
