//Write a program that tests Collatz Conjecture for more given numbers using shared memory.
//Starting from a single parent process, create a child that deals with a single number and writes the series somewhere in the shared memory.
//The parent will create the object of shared memory using shm_open(3) and ftruncate(2), and then it will upload in memory the whole space for reading the results with mmap(2).

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void collatz(int value,int v[]) {
	int it = 1;
	while(value != 1) {
		v[it++] = value;
		if(value % 2 == 0) {
		value = value / 2;
		}
		else {
		value = value * 3 + 1;
		}
	}
	v[it] = 1;
	v[0] = it;
}

void print_collatz(int v[]) {
	printf("%d: ", v[1]);
	for(int i = 1; i <= v[0]; ++i) {
		printf("%d ", v[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	int shm_fd;
	char shm_name[] = "collatz";
	shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if(shm_fd < 0) {
		perror(NULL);
		return errno;
	}
	size_t shm_size = 1024*argc;
	if(ftruncate(shm_fd, shm_size) == -1) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno;
	}
	printf("Starting Parent: %d\n", getpid());
	for(int i = 1; i < argc; ++i)
	{
		int x;
		x = atoi(argv[i]);
		pid_t pid = fork();
		if(pid < 0) {
			return errno;
		}
		else if(pid == 0) 
		{
			printf("Done Parent %d Me %d\n", getppid(), getpid());
			int * my_buffer;
			void * shm_ptr;
			shm_ptr = mmap(0, shm_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
			if(shm_ptr == MAP_FAILED) {
				perror(NULL);
				shm_unlink(shm_name);
				return errno;
			}
			my_buffer =(int*)((char*)shm_ptr + (i - 1) * 1024);
			collatz(x, my_buffer);

			return 0;
		}
	}
	for(int i = 1; i <= argc; ++i) 
		wait(NULL);

	void *adrr;
	adrr = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	for(int i = 1; i < argc; ++i)
		print_collatz((int*)adrr + (i - 1) * 1024 / 4);
	shm_unlink(shm_name);
	printf("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}
