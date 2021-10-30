/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 23:33:39 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/30 23:34:00 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

char	**get_paths(void)
{
	int		fds[2];
	char	**env;
	char	*buffer;

	buffer = malloc(sizeof(char) * 1024);
	pipe(fds);
	env = malloc(sizeof(char *) * 2);
	if (fork() == 0)
	{
		dup2(fds[1], 1);
		dup2(fds[1], 2);
		close(fds[0]);
		close(fds[1]);
		execve("/usr/libexec/path_helper", NULL, NULL);
		perror("path error");
	}
	else
	{
		close(fds[1]);
		read(fds[0], buffer, sizeof(buffer));
		env[0] = ft_strdup(buffer);
		env[1] = NULL;
	}
	free(buffer);
	return (path_surgery(env));
}

char	**path_surgery(char **path_to_cut)
{
	char	*e1;
	char	*e2;
	char	**env;

	e1 = ft_strtrim(*path_to_cut, "PATH=\"");
	e2 = ft_strtrim(e1, "\"; export PATH;\n");
	free(e1);
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
