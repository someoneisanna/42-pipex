#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

//This will test the functions EXECVE, FORK, PIPE, UNLINK and WAIT

int	main(void)
{
	int pipe_fd[2];
	if (pipe(pipe_fd) == -1) //we use PIPE to create a pipe
	{
		perror("Error creating pipe");
		return 1;
	}

	pid_t pid = fork(); //we use FORK to create a child process
	if (pid == -1)
	{
		perror("Error creating child process");
		return 1;
	}
	if (pid == 0)
	{
		//child process
		close (pipe_fd[0]); //we close the read end of the pipe
		dup2(pipe_fd[1], 1); //we use DUP2 to duplicate the write end of the pipe and change the file descriptor number
		close(pipe_fd[1]); //we close the write end of the pipe

		char *program_path = "/bin/ls";
		char *program_args[] = {"ls", "-l", NULL};
		char *envp[] = {NULL};
		int a = execve(program_path, program_args, envp); //we use EXECVE to execute a program
		if (a == -1)
		{
			perror("Error executing program");
			return 1;
		}
		perror("This will not be printed if execve is successful");
		return 1;
	}
	else
	{
		//parent process
		close(pipe_fd[1]); //we close the write end of the pipe
		char buffer[1024];
		int bytes_read = read(pipe_fd[0], buffer, 1024); //we read from the pipe
		close(pipe_fd[0]); //we close the read end of the pipe

		if (bytes_read > 0)
		{
			printf("Output from child process:\n%s\n", buffer);
		}
		else if (bytes_read == 0)
		{
			printf("No output from child process\n");
		}
		else
		{
			perror("Error reading from pipe");
		}

		int status;
		wait(&status); //we use WAIT to wait for the child process to finish

		if (WIFEXITED(status))
		{
			printf("Child process exited with status: %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			printf("Child process terminated due to signal: %d\n", WTERMSIG(status));
		}
		else
		{
			printf("Child process exited with unknown status\n");
		}

		if (unlink("b.txt") == -1) //we use UNLINK to delete a file
		{
			perror("Error unlinking pipe");
			return 1;
		}
	}
}
