/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataboada <ataboada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:52:24 by ataboada          #+#    #+#             */
/*   Updated: 2023/10/06 11:56:39 by ataboada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// ---------------------------------- INCLUDES ---------------------------------

# include "libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/wait.h>

// --------------------------------- PROTOTYPES --------------------------------

int		ft_open_files(char *filename, int file);
void	ft_here_doc(char *limiter);
void	ft_execute_pipes(char *cmd, char **envp);
char	**ft_get_path(char **envp);
void	ft_execute(char *cmd, char **envp);

#endif
