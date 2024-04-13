/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 14:51:23 by nseropia          #+#    #+#             */
/*   Updated: 2023/04/21 21:29:46 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0
# define WRITE_END 1

# include "libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

char	*get_long_path(char **envp);
char	**get_path_array(char *long_path);
char	*get_cmd_path(char **argv, char **envp, int arg_i);
char	**get_cmd_array(char **argv, int arg_i);
int		pipex(int fd_infile, int fd_outfile, char **argv, char **envp);
void	first_child(int *fd, int fd_infile, char **argv, char **envp);
void	second_child(int *fd, int fd_infile, char **argv, char **envp);
void	ft_free(char **arr);
void	handle_dup2_error(void);
void	handle_fork_error(void);

#endif