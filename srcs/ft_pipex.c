/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/28 00:45:05 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"
// leer argumentos
// leer fichero de entrada?
// leer comandos y sus flags?
// ejecutarlos y esperar a que terminen
// siguiente instrucción
//
//https://www.reddit.com/r/linuxquestions/comments/ail178/no_matter_how_much_i_try_i_cant_understand/
//
// para saber si un parámetro es un comando? https://www.codegrepper.com/code-examples/c/how+to+check+if+a+file+exists+in+c /bash
// https://www.geeksforgeeks.org/making-linux-shell-c/
// https://medium.com/swlh/tutorial-to-code-a-simple-shell-in-c-9405b2d3533e
//https://stackoverflow.com/questions/21248840/example-of-waitpid-in-use
//https://askubuntu.com/questions/428458/why-do-shells-call-fork
//http://alumni.cs.ucr.edu/~weesan/cs153/lab2_notes.html
//https://stackoverflow.com/questions/30149779/c-execve-parameters-spawn-a-shell-example
// /usr/libexec/path_helper -s  
// whereis ...
// https://stackoverflow.com/questions/2605130/redirecting-exec-output-to-a-buffer-or-file
// https://stackoverflow.com/questions/7292642/grabbing-output-from-exec

#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t	child;
	int		child_status;
	int		cmds;
	int		has_output_file;
	has_output_file = 0;
	cmds = count_cmds(argv);
	int fd;

	// if there is only an input file, without any other command nor file 
	if (argc == 1)
		return (0);
	fd = ft_input_or_cmd(argv[1]);
	if (cmds == 0 && argc == 2)
	{
		child = fork();
		if (child == 0)
		{
			char *comm_args3[] = {"cat", argv[1], NULL};
			execve("/bin/cat", &comm_args3[0], NULL);
		}
		waitpid(child, &child_status, 0);
		return (0);
	}
	else if (cmds == 1 && argc == 2)
	{
		one_cmd_no_outfile(argv, 1);
		return (0);
	}
	parse_and_execute(argc, argv, cmds);
}

void	parse_and_execute(int argc, char **argv, int cmds)
{
	int	i;
	pid_t	child;
	int	fds[2];
	int	child_status;
	
	argc = argc * 1;
	i = 0;
	child = 0;
	while (i < cmds)
	{
	//if there is file and command (standard case), read std input with cat.
		if (pipe(fds) < 0)
			ft_putstr_fd("Error creating pipe", 2);
		child = fork();
		if (child == 0 && i == 0)
		{
			dup2(fds[1], 1);
			close(fds[0]);
			close(fds[1]);
			char *comm_args3[] = {"cat", argv[1], NULL};
			execve("/bin/cat", &comm_args3[0], NULL);
		}
		else
		{
			char	**cmdargs;
			char 	*cmdcmd;
			cmdargs = create_args(argv, i);
		
		//	ft_printf("arg: %s\n", cmdargs[1]);	
			waitpid(child, &child_status, 0);
			dup2(fds[0], 0);
			close(fds[1]);
			is_cmd(argv[i], &cmdcmd);
			child = fork();
			if (child == 0)
			{	
				execve(cmdcmd, &cmdargs[0], NULL);
				perror("pipex");
			}
			waitpid(child, &child_status, 0);
			if (*cmdargs)
				free_paths(cmdargs);
		}
		i++;
	}
}

char	**get_paths(void)
{
	int		fds[2]; 
	char **env;
//	char buffer[1024];
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

void free_paths(char **paths)
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
