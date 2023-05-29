/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:52:27 by ataboada          #+#    #+#             */
/*   Updated: 2023/05/29 13:17:23 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "pipex_bonus.h"

char	**ft_get_path(char **envp)
{
	int		i;
	char	**paths_possible;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths_possible = ft_split(envp[i] + 5, ':');
		i++;
	}
	return (paths_possible);
}

void	ft_execute(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	*cmd_path;
	char	**paths_possible;
	char	**cmd_args;

	paths_possible = ft_get_path(envp);
	cmd_args = ft_split(cmd, ' ');
	i = 0;
	while (paths_possible[i++])
	{
		tmp = ft_strjoin(paths_possible[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_args[0]);
		free(tmp);
		if (!cmd_path || !tmp)
			exit(1);
		if (access(cmd_path, F_OK | X_OK) == 0)
			if (execve(cmd_path, cmd_args, envp) == -1)
				ft_printf("Error: command failed to execute\n");
		free (cmd_path);
	}
	perror("Error");
	exit(2);
}
