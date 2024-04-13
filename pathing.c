/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseropia <nseropia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:15:18 by nseropia          #+#    #+#             */
/*   Updated: 2023/04/21 17:36:13 by nseropia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_long_path(char **envp)
{
	char	*long_path;

	long_path = NULL;
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			long_path = (*envp + 5);
			break ;
		}
		envp++;
	}
	return (long_path);
}

char	**get_path_array(char *long_path)
{
	char	**path_array;

	path_array = ft_split(long_path, ':');
	return (path_array);
}

char	**get_cmd_array(char **argv, int arg_i)
{
	char	**cmd_array;

	if (argv[arg_i][0] == 0)
		return (NULL);
	cmd_array = ft_split(argv[arg_i], ' ');
	return (cmd_array);
}

char	*get_cmd_path(char **argv, char **envp, int arg_i)
{	
	char	*single_path;
	char	*temp_path;
	char	**path_array;
	char	**cmd_array;
	int		i;

	path_array = get_path_array(get_long_path(envp));
	cmd_array = get_cmd_array(argv, arg_i);
	if (!cmd_array)
		return (ft_putstr_fd("command not found\n", 2), ft_free(path_array),
			ft_free(cmd_array), NULL);
	i = 0;
	while (path_array[i] != NULL)
	{
		temp_path = ft_strjoin(path_array[i], "/");
		single_path = ft_strjoin(temp_path, *cmd_array);
		free(temp_path);
		if (access(single_path, F_OK | X_OK) == 0)
			return (ft_free(path_array), ft_free(cmd_array), (single_path));
		else
			free(single_path);
		i++;
	}
	return (ft_putstr_fd("command not found\n", 2), ft_free(path_array),
		ft_free(cmd_array), NULL);
}
