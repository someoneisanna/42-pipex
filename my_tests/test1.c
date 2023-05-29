#include <stdio.h> //perror and printf
#include <string.h> //strerror
#include <unistd.h> //close
#include <fcntl.h> //open
#include <errno.h> //errno

//This will test the functions PERROR, STRERROR, ACCESS, DUP and DUP2

int	main(void)
{
	int	ac = access("d.txt", F_OK); //we use ACCESS to check if the file exists
	if (ac == -1)
	{
		perror("Error opening file"); //PERROR prints the error message
		printf("ERROR: %s\n", strerror(errno)); //STRERROR prints the error message
	}
	close(ac);

	int fd = open("a.txt", O_RDONLY);
	if (fd == -1)
		perror("Error opening file");
	printf("fd: %d\n", fd);
	int dup_fd = dup(fd); //we use DUP to duplicate the file descriptor
	if (dup_fd == -1)
		perror("Error duplicating file descriptor");
	printf("dup_fd: %d\n", dup_fd);
	close(fd);

	int fd2 = open("b.txt", O_RDONLY);
	if (fd2 == -1)
		perror("Error opening file");
	printf("fd2: %d\n", fd2);
	int dup2_fd = dup2(fd2, 7); //we use DUP2 to duplicate the file descriptor and change the file descriptor number
	if (dup2_fd == -1)
		perror("Error duplicating file descriptor");
	printf("dup2_fd: %d\n", dup2_fd);
	close(fd2);
}
