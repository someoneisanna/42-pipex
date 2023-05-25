/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:06:53 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/25 20:11:57 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		ft_check_access(char *filename, int mode);
void	ft_pipex(int fd1, int fd2, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		ft_printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (ft_check_access(argv[1], 1) == 0)
		fd1 = open(argv[1], O_RDONLY);
	if (ft_check_access(argv[4], 2) == 0)
		fd2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error");
		return (1);
	}
	ft_pipex(fd1, fd2, argv, envp);
	close(fd1);
	close(fd2);
}

int	ft_check_access(char *filename, int file)
{
	if (file == 1)
	{
		if (access(filename, F_OK) < 0)
		{
			ft_printf("Error: file not found\n");
			return (1);
		}
	}
	else if (file == 2)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) < 0)
		{
			ft_printf("Error: file found, but permission to write denied\n");
			return (1);
		}
	}
	return (0);
}

void	ft_pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		status;
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
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}
