/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:29:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/06/23 11:53:46 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int		ft_open_files(char *filename, int file);
void	ft_here_doc(char *limiter);
void	ft_execute_pipes(char *cmd, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;
	int	index;

	if (argc > 1 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			return (ft_printf("Usage: ./pipex here_doc LIMITER cmd cmd1 file"));
		index = 3;
		fd2 = ft_open_files(argv[argc - 1], 3);
		ft_here_doc(argv[2]);
	}
	else
	{
		if (argc < 5)
			return (ft_printf("Usage: ./pipex file1 cmd1 ... cmdn file2"));
		index = 2;
		fd1 = ft_open_files(argv[1], 1);
		fd2 = ft_open_files(argv[argc - 1], 2);
		dup2(fd1, STDIN_FILENO);
	}
	while (index < argc - 2)
		ft_execute_pipes(argv[index++], envp);
	dup2(fd2, STDOUT_FILENO);
	ft_execute(argv[argc - 2], envp);
}

int	ft_open_files(char *filename, int file)
{
	int	fd;

	if (file == 1)
	{
		if (access(filename, F_OK) < 0)
			fd = -1;
		fd = open(filename, O_RDONLY);
	}
	if (file == 2 || file == 3)
	{
		if (access(filename, F_OK) == 0 && access(filename, W_OK) < 0)
			fd = -1;
		else
		{
			if (file == 2)
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (file == 3)
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
	}
	if (fd < 0)
		exit (ft_printf("Error: %s\n", strerror(errno)) && 1);
	return (fd);
}

void	ft_here_doc(char *limiter)
{
	int		pid;
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		return (perror("Error"));
	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (ft_strnstr(line, limiter, ft_strlen(limiter)))
				exit(-1);
			write(pipe_fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_execute_pipes(char *cmd, char **envp)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) < 0)
		return (perror("Error"));
	pid = fork();
	if (pid < 0)
		return (perror("Error"));
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_execute(cmd, envp);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
