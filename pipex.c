/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:19:36 by nseropia          #+#    #+#             */
/*   Updated: 2023/04/28 18:45:08 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_dup2_error(void)
{
	perror("dup2:");
	exit(1);
}

void	handle_fork_error(void)
{
	perror("fork:");
	exit(1);
}

void	first_child(int *fd, int fd_infile, char **argv, char **envp)
{
	char	*cmd_path;
	char	**cmd_array;

	cmd_path = get_cmd_path(argv, envp, 2);
	cmd_array = get_cmd_array(argv, 2);
	if (dup2(fd_infile, STDIN_FILENO) == -1
		|| dup2(fd[WRITE_END], STDOUT_FILENO) == -1)
		handle_dup2_error();
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	if (!cmd_path || !cmd_array)
	{
		free(cmd_path);
		ft_free(cmd_array);
		exit (1);
	}
	if (execve(cmd_path, cmd_array, envp) == -1)
	{
		free(cmd_path);
		ft_free(cmd_array);
		exit (1);
	}
}

void	second_child(int *fd, int fd_outfile, char **argv, char **envp)
{
	char	*cmd_path;
	char	**cmd_array;

	cmd_path = get_cmd_path(argv, envp, 3);
	cmd_array = get_cmd_array(argv, 3);
	if (dup2(fd[READ_END], STDIN_FILENO) == -1
		|| dup2(fd_outfile, STDOUT_FILENO) == -1)
		handle_dup2_error();
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	if (!cmd_path || !cmd_array)
	{
		free(cmd_path);
		ft_free(cmd_array);
		exit (1);
	}
	if (access(argv[3], X_OK) == 0)
		execve(argv[3], ft_split(argv[3], ' '), NULL);
	if (execve(cmd_path, cmd_array, envp) == -1)
	{
		free(cmd_path);
		ft_free(cmd_array);
		exit (1);
	}
}

int	pipex(int fd_infile, int fd_outfile, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
	{
		perror("pipe:");
		exit (1);
	}
	pid1 = fork();
	if (pid1 < 0)
		handle_fork_error();
	if (pid1 == 0)
		first_child(fd, fd_infile, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		handle_fork_error();
	if (pid2 == 0)
		second_child(fd, fd_outfile, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
