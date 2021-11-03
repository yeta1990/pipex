/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/03 01:13:16 by albgarci         ###   ########.fr       */
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
	ft_dup_output(argv[argc - 1]);
	return (ft_exec_last(argv, fds, envp));
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
		exit(errno);
	}
	else if (child == 0)
	{	
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		cmdargs = create_args(argv[2], &cmd, envp);
		execve(cmd, &cmdargs[0], envp);
		perror("pipex");
		exit(errno);
	}
	waitpid(child, &child_status, WNOHANG);
	close(fds[1]);
}

int	ft_exec_last(char **argv, int fds[2], char *envp[])
{
	int		child_status;
	pid_t	child;
	char	*cmd;
	char	**cmdargs;

	child = fork();
	if (child == -1)
	{
		perror("pipex");
		exit(errno);
	}
	if (child == 0)
	{
		dup2(fds[0], 0);
		close(fds[0]);
		cmdargs = create_args(argv[3], &cmd, envp);
		execve(cmd, &cmdargs[0], envp);
		perror("pipex");
		exit(errno);
	}
	waitpid(child, &child_status, 0);
	close(fds[0]);
	return (WEXITSTATUS(child_status));
}
