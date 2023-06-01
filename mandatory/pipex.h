/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:06:43 by ataboada          #+#    #+#             */
/*   Updated: 2023/06/01 10:08:32 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>

int		ft_open_files(char *filename, int mode);
void	ft_pipex(int fd1, int fd2, char **argv, char **envp);
char	**ft_get_path(char **envp);
void	ft_execute(char *cmd, char **envp);
void	ft_child_process_1(int fd1, char *cmd1, int pipe_fd[2], char **envp);
void	ft_child_process_2(int fd2, char *cmd2, int pipe_fd[2], char **envp);

#endif
