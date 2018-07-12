//Dhruv Agnihotri
//dagnihot
//assignment_1

#include <stdio.h>
//#include <xinu.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int fd[2];
	pipe(fd);
	pid_t pid; 
	pid = fork();
	char x[100];
 
	if (pid < 0) { 
		printf("Fork Failed");  
	}
 
	else if (pid > 0) { 
		printf("Parent PID = %d, \n", getpid());
		close(fd[0]);
		strcpy(x, argv[1]);
		write(fd[1], &x, sizeof(x));
		close(fd[1]);
		} 

	else {
		printf("Child PID = %d\n", getpid());
		close(fd[1]);
		read(fd[0], &x, sizeof(x));
		if(strncmp(argv[1], "/bin/echo", 9) == 0) {
		execlp(argv[1], argv[1], "Hello World!", NULL);
		}
		execlp(argv[1], argv[1], NULL);
		close(fd[0]);
	} 
}
