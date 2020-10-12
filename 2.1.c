//Display the message "Hello World!" only with system functions.


#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	const char *message = "Hello World! \n";
	write(1 , message, strlen(message));
	return 0;
}