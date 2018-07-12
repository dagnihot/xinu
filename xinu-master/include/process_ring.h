extern volatile int32 inbox[64];
extern volatile int ring[64];
extern volatile int round; 
extern volatile int parentid;
extern volatile int begin;

process process_ring(int process_index, int processes, int choice);
