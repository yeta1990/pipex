/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/27 14:18:13 by albgarci         ###   ########.fr       */
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
	int		fds[2]; 
	char	*cmd;
	int		cmds;
	int		has_output_file;
	has_output_file = 0;
	cmds = count_cmds(argv);
	child = 0;
	cmd = 0;
	int fd;
	fd = ft_input_or_cmd(argv[1], &cmd);
	// if it starts or ends whith a command directly, without standard input
	if (cmds == 1 && argc == 2)
	{
		one_cmd_no_outfile(argv, 1);

	}
	// if there is only an input file, without any other command nor file 
	else if (argc == 2)
	{
		child = fork();
		if (child == 0)
		{
			char *comm_args3[] = {"cat", argv[1], NULL};
			execve("/bin/cat", &comm_args3[0], NULL);
		//	execve("/bin/cat", &argv[1], NULL);
		}
		waitpid(child, &child_status, 0);
		return (0);
	}	
	//if there is file and command (standard case), read std input with cat.
	else
	{
		if (pipe(fds) < 0)
			ft_putstr_fd("Error creating pipe", 2);
		child = fork();
		if (child == 0)
		{
			dup2(fds[1], 1);
			close(fds[0]);
			close(fds[1]);
			char *comm_args3[] = {"cat", argv[1], NULL};
			execve("/bin/cat", &comm_args3[0], NULL);
		}
	}
	waitpid(child, &child_status, 0);
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);

//ft_printf("pringao");
/*

	child = fork();

	if (child == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve("/usr/libexec/path_helper", &comm_args[0], env);
		perror("pipex");
	}
	waitpid(child, &child_status, 0); //no sé si es necesario para el pipe...
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);

*/
//	char *comm_args2[] = {"/usr/bin/grep", "srcs", NULL};
//	execve(comm_args2[0], &comm_args2[0], NULL);
//	perror("grep");
//	free(paths);
	free(cmd);
}

char	**get_paths(void)
{
	int		fds[2]; 
	char **env;
	char buffer[1024];
//	char *buffer;
//	buffer = malloc(51);
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
