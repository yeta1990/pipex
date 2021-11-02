/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:38:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/02 17:42:48 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	is_cmd(char *file, char **cmd_ok, char *envp[])
{
	int		j;
	char	*cmd_try;
	char	**paths;

	paths = get_paths(envp);
	j = 0;
	while (paths[j])
	{
		cmd_try = ft_strjoin(paths[j], file);
		if (access(cmd_try, X_OK) != -1)
		{
			if (cmd_ok)
				*cmd_ok = ft_strdup(cmd_try);
			free(cmd_try);
			free_paths(paths);
			return (1);
		}
		free(cmd_try);
		j++;
	}
	free_paths(paths);
	return (0);
}

char	**create_args(char *raw_cmd, char **cmd, char *envp[])
{
	char	**args;

	args = ft_split(raw_cmd, ' ');
	if (!args)
	{
		ft_putstr_fd("pipex: Wrong argument: it's empty", 2);
		exit(1);
	}
	if (!(is_cmd(args[0], cmd, envp)))
	{
		ft_putstr_fd("pipex: ", 2);
		if (args[0])
			write(2, args[0], ft_strlen(args[0]));
		ft_putstr_fd(": command not found\n", 2);
		exit(1);
	}
	return (args);
}
