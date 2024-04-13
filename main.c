/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:15:24 by nseropia          #+#    #+#             */
/*   Updated: 2023/04/28 18:39:44 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int	fd_infile;
	int	fd_outfile;

	if (argc == 5)
	{
		fd_infile = open(argv[1], O_RDONLY);
		fd_outfile = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd_infile < 0 || fd_outfile < 0)
		{
			ft_putstr_fd("pipex: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (EXIT_FAILURE);
		}
		pipex(fd_infile, fd_outfile, argv, envp);
		close(fd_infile);
		close(fd_outfile);
		return (0);
	}
	ft_putstr_fd("pipex: program needs to be executed as follows: \
./pipex file1 cmd1 cmd2 file2\n", 2);
	return (EXIT_FAILURE);
}
