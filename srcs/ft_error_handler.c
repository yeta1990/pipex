/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:38:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/26 17:46:40 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_input_or_cmd(char *file, char **cmd_ok)
{
	int r;

	if (is_cmd(file, cmd_ok))
		return (0);
	r = open(file, O_RDONLY);
	if (r < 0)
	{
		ft_putstr_fd(ft_strjoin("pipex: ", file), 2);
		ft_putstr_fd(ft_strjoin(": ", strerror(errno)), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	return (r);
}

int is_cmd(char *file, char **cmd_ok)
{
	int		j;
	char	*cmd_try;
	char	**paths;

	paths = get_paths();
	j = 0;
	while (paths[j])
	{
		cmd_try = ft_strjoin(paths[j], file);
		if (access(cmd_try, X_OK) != -1)
		{
			*cmd_ok = ft_strdup(cmd_try);
			free_paths(paths);
			free(cmd_try);
			return (1);
		}
	//	free(paths);
		free(cmd_try);
		j++;
	}
	free_paths(paths);
	return (0);
}

char **create_args(char **argv, int start)
{
	int i;
	char *cmd;
	int j;
	char **args;

	cmd = 0;
	j = 0;
	i = start + 1;
	while (argv && argv[i] && !is_cmd(argv[i], &cmd))
		i++;
	args = malloc(sizeof(char *) * (i - start + 1));
	while (j < i - start)
	{
		args[j] = ft_strdup(argv[start + j]);
		j++;
	}
	args[j] = 0;
	return (args);
}
