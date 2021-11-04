/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/04 13:40:15 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	main(int argc, char **argv, char *envp[])
{
	int		fds[2];	

	input_error_checker(argc);
	ft_dup_infile(argv[1]);
	if (pipe(fds) < 0)
	{
		perror("pipex");
		exit(1);
	}
	ft_exec_first(argv, fds, envp);
	ft_exec_middle(argv, argc, fds, envp);
	ft_dup_output(argv[argc - 1]);
	ft_exec_last_bonus(argv, argc, fds, envp);
	return (0);
}

void	ft_exec_first(char **argv, int fds[2], char *envp[])
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
		cmdargs = create_args(argv[2], &cmd, envp);
		execve(cmd, &cmdargs[0], envp);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, WNOHANG);
	close(fds[1]);
}

void	ft_exec_middle(char **argv, int argc, int fds[2], char *envp[])
{
	int		i;
	int		fds2[2];

	i = 3;
	while (i < argc - 2)
	{
		ft_exec_middle_ops(argv[i], fds, fds2, envp);
		i++;
		close(fds[0]);
		close(fds2[1]);
		fds[0] = fds2[0];
		fds[1] = fds2[1];
	}
}

void	ft_exec_middle_ops(char *raw_cmd, int fds[2], int fds2[2], char *envp[])
{
	int		child;
	int		child_status;
	char	*cmd;
	char	**cmdargs;

	pipe(fds2);
	child = fork();
	if (child == 0)
	{
		close(fds2[0]);
		dup2(fds[0], 0);
		close(fds[0]);
		dup2(fds2[1], 1);
		close(fds2[1]);
		cmdargs = create_args(raw_cmd, &cmd, envp);
		execve(cmd, &cmdargs[0], envp);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, 0);
}

void	ft_exec_last_bonus(char **argv, int argc, int fds[2], char *envp[])
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
		dup2(fds[0], 0);
		close(fds[0]);
		cmdargs = create_args(argv[argc - 2], &cmd, envp);
		execve(cmd, &cmdargs[0], envp);
		perror("pipex");
		exit(127);
	}
	waitpid(child, &child_status, WNOHANG);
	close(fds[0]);
}
