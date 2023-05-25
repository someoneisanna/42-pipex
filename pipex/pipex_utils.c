/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:06:55 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/25 20:57:05 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	**paths_possible;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths_possible = ft_split(envp[i] + 5, ':');
		}
		i++;
	}
	return (paths_possible);
}

void	ft_child_process_1(int fd1, char *cmd1, int pipe_fd[2], char **envp)
{
	int		i;
	char	*tmp;
	char	*cmd_path;
	char	**paths_possible;
	char	**cmd_args;

	dup2(fd1, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(fd1);
	paths_possible = ft_get_path(envp);
	cmd_args = ft_split(cmd1, ' ');
	i = 0;
	while (paths_possible[i++])
	{
		tmp = ft_strjoin(paths_possible[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!cmd_path || !tmp)
			exit(1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			execve(cmd_path, cmd_args, envp);
	}
	perror("Error - child_1");
	exit(2);
}

void	ft_child_process_2(int fd2, char *cmd2, int pipe_fd[2], char **envp)
{
	int		i;
	char	*tmp;
	char	*cmd_path;
	char	**paths_possible;
	char	**cmd_args;

	dup2(fd2, STDOUT_FILENO);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(fd2);
	paths_possible = ft_get_path(envp);
	cmd_args = ft_split(cmd2, ' ');
	i = 0;
	while (paths_possible[i++])
	{
		tmp = ft_strjoin(paths_possible[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!cmd_path || !tmp)
			exit(1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			execve(cmd_path, cmd_args, envp);
	}
	perror("Error - child_2");
	exit(2);
}
