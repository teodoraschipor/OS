//Create a new process using fork(2) and display the files from the current directory using execve(2).
//Display from the initial process: the current pid and the child's pid.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	pid_t myproc = fork();
	pid_t myprocc = getpid();
	pid_t myproccc = getppid();
	if(myproc == 0)
	{
		char* argv[] = { "ls", NULL };
		execve("/bin/ls",argv,NULL);
	}
	else if(myproc > 0)
		printf("%d - CHILD | %d - PARENT \n", myprocc, myproccc);

	return 0;
}