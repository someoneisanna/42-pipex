/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:06:53 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 12:42:58 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int		ft_open_files(char *filename, int mode);
void	ft_pipex(int fd1, int fd2, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		ft_printf("Error: Wrong number of arguments\n");
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (1);
	}
	fd1 = ft_open_files(argv[1], 1);
	fd2 = ft_open_files(argv[4], 2);
	if (fd1 == -1 || fd2 == -1)
		return (1);
	ft_pipex(fd1, fd2, argv, envp);
}

int	ft_open_files(char *filename, int file)
{
	int	fd;

	fd = -1;
	if (file == 1)
	{
		if (access(filename, F_OK) < 0)
		{
			perror("Error");
			return (-1);
		}
		fd = open(filename, O_RDONLY);
	}
	else if (file == 2)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) < 0)
		{
			perror("Error");
			return (-1);
		}
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	return (fd);
}

void	ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) == -1)
	{
		perror("Error");
		exit (1);
	}
	pid1 = fork();
	if (pid1 == -1)
		perror("Error");
	if (pid1 == 0)
		ft_child_process_1(fd1, argv[2], pipe_fd, envp);
	pid2 = fork();
	if (pid2 == -1)
		perror("Error");
	if (pid2 == 0)
		ft_child_process_2(fd2, argv[3], pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
