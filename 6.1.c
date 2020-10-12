//Write a program  that will receive (at the intrance) a string. Its characters will be copied in reverse order and will be saved in another string. 
//The reverse operation will be made in another thread. The result will be obtained with pthread_join function.

#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
void *f(void *b)
{
	char *v = b;
	char* a = (char*)malloc((strlen(v))*sizeof(char));
	int j = 0;
	for(int i = strlen(v)-1; i >= 0; --i)
	{
		a[j] = v[i];
		j++;
	}
	a[j] = "\0";
	return a;
}
int main(int argc, char* argv[])
{
	pthread_t thread;
	char* c = argv[1];
	if(pthread_create(&thread, NULL, f , c))
	{
		perror(NULL);
		return errno;
	}
	char* result;
	if(pthread_join(thread, (void**) &result))
	{
		perror(NULL);
		return errno;
	}
	printf("%s\n", result);
	return 0;
}