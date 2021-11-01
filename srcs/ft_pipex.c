/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/01 14:32:18 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv)
{
	int		fds[2];	
	int		last;

	input_error_checker(argc, argv);
	last = last_cmd(argc, argv);
	ft_dup_infile(argv[1]);
	if (pipe(fds) < 0)
	{
		perror("pipex");
		exit(1);
	}
	ft_exec_first(argv, fds);
	ft_dup_output(argv[argc - 1]);
	ft_exec_last(argv, fds, last);
	return (0);
}

void	ft_exec_first(char **argv, int fds[2])
{
	int		child_status;
	pid_t	child;
	char	*cmd;
	char	**cmdargs;

	child = fork();
	if (child == -1)
	{
		perror("pipex");
		exit(1);
	}
	else if (child == 0)
	{	
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		cmdargs = create_args(argv, 2, 0);
		is_cmd(argv[2], &cmd);
		execve(cmd, &cmdargs[0], NULL);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, 0);
	close(fds[1]);
}

void	ft_exec_last(char **argv, int fds[2], int last)
{
	int		child_status;
	pid_t	child;
	char	*cmd;
	char	**cmdargs;

	child = fork();
	if (child == -1)
	{
		perror("pipex");
		exit(1);
	}
	if (child == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		cmdargs = create_args(argv, last, 1);
		is_cmd(argv[last], &cmd);
		execve(cmd, &cmdargs[0], NULL);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, 0);
	close(fds[0]);
}
