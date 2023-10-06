#include <stdio.h>  //perror and printf
#include <string.h> //strerror
#include <unistd.h> //close
#include <fcntl.h>  //open
#include <errno.h>  //errno

// This will test the functions PERROR, STRERROR, ACCESS, DUP and DUP2

int	main(void)
{
	printf("Testing PERROR, STRERROR and ACCESS\n");
	int	ac = access("c.txt", F_OK); //we use ACCESS to check if the file exists
	if (ac == -1)
	{
		perror("Error"); //PERROR prints the error message
		printf("ERROR: %s\n", strerror(errno)); //STRERROR does the same
	}

	printf("\nTesting DUP\n");
	int fd1 = open("a.txt", O_RDONLY);
	if (fd1 == -1)
		perror("Error opening file");
	printf("    fd1: %d\n", fd1);

	int dup_fd1 = dup(fd1); //we use DUP to create a copy of the file descriptor
	if (dup_fd1 == -1)
		perror("Error duplicating file descriptor");
	printf("dup_fd1: %d\n", dup_fd1);

	printf("\nTesting DUP2\n");
	int fd2 = open("b.txt", O_WRONLY);
	if (fd2 == -1)
		perror("Error opening file");
	printf("     fd2: %d\n", fd2);

	int dup2_fd2 = dup2(fd2, STDOUT_FILENO); // the output will be placed in fd2
	if (dup2_fd2 == -1)
		perror("Error duplicating file descriptor");
	printf("dup2_fd2: %i\n", dup2_fd2); // the output will be placed in b.txt
	close(fd1);
	close(dup_fd1);
	close(fd2);
}
