/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/24 19:56:30 by albgarci         ###   ########.fr       */
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

#include <stdio.h>

int main()
{
	char *env[] = {NULL};
	char *comm_args[] = {"/bin/ls", "-la"};
	pid_t	child;
	int		child_status;
	int fds[2]; 

	if (pipe(fds) < 0)
		ft_putstr_fd("Error creating pipe", 2);
	child = fork();

	if (child == 0)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		close(fds[1]);
		execve("/bin/ls", &comm_args[0], env);
		perror("pipex");
	}
	waitpid(child, &child_status, 0); //no sé si es necesario para el pipe...
	dup2(fds[0], 0);
	close(fds[0]);
	close(fds[1]);
	char *comm_args2[] = {"/usr/bin/grep", "srcs", NULL};
	execve(comm_args2[0], &comm_args2[0], NULL);
	perror("grep");
}

