/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/26 17:58:15 by albgarci         ###   ########.fr       */
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


#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t	child;
	int		child_status;
	int		fds[2]; 
	int		i;
	int		j;
	char	*cmd;
	char	**cmdargs;
	
	i = 2;
	j = 0;
	cmd = 0;
	child = 0;

	int fd;
//	char *comm_args[] = {"ls", "-l", "-s", NULL};
	fd = ft_input_or_cmd(argv[1], &cmd);
	// if it starts whith a command directly, without standard input
	if (fd == 0)
	{
		cmdargs = create_args(argv, 1);
		child = fork();
		if (child == 0)
		{
			//execve(cmd, &comm_args[0], NULL);
			execve(cmd, &cmdargs[0], NULL);
			perror("pipex1");
		}
		return (0);
	}
	// if there is only an input file, without any other command nor file 
	else if (argc == 2)
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
	//if there is file and command (standard case), read std input with cat.
	else
	{
		if (pipe(fds) < 0)
			ft_putstr_fd("Error creating pipe", 2);

		child = fork();
			if (child == 0)
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

ft_printf("pringao");
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
//	system("leaks pipex");
}

char	**get_paths(void)
{
	char **paths;

	paths = malloc(sizeof(char *) * 8);
	paths[0] = ft_strdup("/usr/local/bin/");
	paths[1] = ft_strdup("/usr/bin/");
	paths[2] = ft_strdup("/bin/");
	paths[3] = ft_strdup("/usr/sbin/");
	paths[4] = ft_strdup("/sbin/");
	paths[5] = ft_strdup("/Library/Frameworks/Python.framework/Versions/3.9/bin/");
	paths[6] = ft_strdup("/usr/local/munki/");
	paths[7] = 0;
	return (paths);
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
