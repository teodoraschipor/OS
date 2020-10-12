//Write a program that tests the Collatz Conjecture for more numbers given.
//Starting from a single parent process, it is created a child that deals with a single number. The parent will wait every child to finish its execution.
//Use getpid(2) and getppid(2).

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void collatz (int n)
{
	printf("%d: ", n);
	while (n != 1)
	{
		printf("%d ", n);
		if(n % 2 == 0)
			n = n / 2;
		else
			n = 3 * n + 1;
	}
	printf("%d \n", n);
}


int main(int argc, char const *argv[])
{
	if(argc == 0)
	{
		printf("Insufficient number of arguments.\n");
		return -1;
	}
	printf("Starting Parent %d\n", getpid());
	for (int i = 1; i <= argc; ++i)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			return errno;
		}
		else
			if(pid == 0)
			{
			
				int n = atoi(argv[i]);
				collatz(n);
				printf("Done Parent %d Me %d\n",  getppid(), getpid());
				exit(1);
			}
	}
	for(int i = 1; i <= argc; ++i)
		wait();
	printf("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}