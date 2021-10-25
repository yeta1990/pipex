/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/25 18:14:25 by albgarci         ###   ########.fr       */
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
	char *env[] = {NULL};
	char *comm_args[] = {"/usr/libexec/path_helper", "-la"};
	pid_t	child;
	int		child_status;
	int fds[2]; 
	int	i;
	int	j;
	char *cmd;
	char **paths;
	
	paths = get_paths();
	i = 2;
	j = 0;
	cmd = 0;

	ft_check_input_file(argv[1]);
	while (i < argc)
	{
		j = 0;
		while (paths[j])
		{
			cmd = ft_strjoin(paths[j], argv[i]);
			if (access(cmd, X_OK) != -1)
			{
				child = fork();
				if (child == 0)
				{
					execve(cmd, &argv[i], NULL);
					perror("pipex");
				}
				waitpid(child, &child_status, 0);
			//	i++; // este i++ hace que el siguiente argumento entre como parámetro del comando ejecutdo, tengo que investigar
				j = 0;
				break ;
			}
			free(cmd);
			j++;
		}
		// if cmd isn't found
		if (j == 6)
		{
			execve(argv[i], (char  *const *)argv[i], NULL);
		//	perror(argv[i]);
		//	ft_putstr_fd(ft_strjoin("pipex: command not found: ", argv[i]), 2);
			//ft_putstr_fd("\n", 2);
			ft_putstr_fd(strerror(errno), 2);
		//	perror("pipex");
		//	waitpid(child, &child_status, 0);
			exit(1);
		}
		i++;
	}

	if (pipe(fds) < 0)
		ft_putstr_fd("Error creating pipe", 2);
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
//	char *comm_args2[] = {"/usr/bin/grep", "srcs", NULL};
//	execve(comm_args2[0], &comm_args2[0], NULL);
//	perror("grep");
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
	paths[5] = ft_strdup("/usr/local/munki/");
	paths[7] = 0;
	return (paths);
}
