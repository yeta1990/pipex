/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 23:33:39 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/02 17:56:28 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**get_paths(char *envp[])
{
	int		i;
	char	**raw_path;

	i = 0;
	raw_path = malloc(sizeof(char *) * 2);
	while (envp && envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=/", 6) == 0)
		{
			raw_path[0] = ft_strdup(envp[i]);
			raw_path[1] = 0;
			break ;
		}
		i++;
	}
	return (path_surgery(raw_path));
}

char	**path_surgery(char **path_to_cut)
{
	char	*e1;
	char	*e2;
	char	**env;

	e2 = ft_strtrim(*path_to_cut, "PATH=");
	e1 = ft_strjoin(e2, ":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	free_paths(path_to_cut);
	env = ft_split_mod(e1, ':');
	free(e2);
	free(e1);
	return (env);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{	
		free(paths[i]);
		i++;
	}
	free(paths);
}
