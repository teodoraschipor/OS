//Write a program that uses fork(2) and tests Collatz Conjecture. It generates the sequence of a number that is given in the child process.

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
	pid_t pid = fork();
	if (pid < 0)
	{
		return errno;
	}
	else 
		if (pid == 0)
		{
			if (argv <= 1)	
			{
				printf("Insufficient number of arguments");
				perror(NULL);
			}
			int n = atoi(argv[1]);
			collatz(n);
		}
		else
		{
			wait();
			printf("Child %d finished\n",  getpid());
		}
	return 0;
}