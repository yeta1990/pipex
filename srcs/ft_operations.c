/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:09:13 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/28 00:09:14 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	one_cmd_no_outfile(char **argv, int pos)
{
	char	**cmdargs;
	pid_t	child;
	int		child_status;
	char	*cmd_path;

	cmdargs = create_args(argv, pos);
	child = fork();
	if (is_cmd(argv[pos], &cmd_path) && child == 0)
	{
		execve(cmd_path, &cmdargs[0], NULL);
		perror("pipex");
	}
//	else
//	{
		waitpid(child, &child_status, 0);
		free(cmd_path);
		free_paths(cmdargs);
//	}
}

