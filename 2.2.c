//Write a program mycp that will receive (at intrance): first argument - a source file that it will copy in another file with the name received in the second argument. 
//Call example: ./mycp foo bar

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int fd1, fd2;

	fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1)
	{
		printf("Error when open the first file, found: %s \n", argv[1]);
		return -1;
	}

	fd2 = open(argv[2], O_WRONLY);
	if(fd2 == -1)
	{
		printf("Error when open the second file, found: %s \n", argv[2]);
		return -1;
	}

	char* buff;
	buff = malloc(1024 * sizeof(char));

	while (read(fd1, buff, 1024 * sizeof(char)) == 1024)
	{
		size_t w = write(fd2, buff, 1024 * sizeof(char));
		if (w == -1)
		{
			printf("Error when write in file.");
			return -1;
		}
	}	


	if (read(fd1, buff, 1024 * sizeof(char)) == -1)
	{
		printf("Error when read in the first file");
		return - 1;
	}
	
	size_t w =  write(fd2, buff, 1024 * sizeof(char));
	if(w == -1)
	{
		printf("Error when write in file.(Last part)");
		return -1;
	}

	close(fd1);
	close(fd2);
	
	return 0;
}