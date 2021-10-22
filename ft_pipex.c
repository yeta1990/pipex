/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/22 14:45:06 by albgarci         ###   ########.fr       */
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
//


int main()
//int main(int argc, char **argv)
{
	char *env[] = {NULL};
	//char *comm_args[] = {"-la"};
	char *comm_args[] = {"-la", "/"};
//	printf("hola");
//	execve("/bin/ls", &comm_args[0], env); 
	if (execve("/bin/ls", &comm_args[0], env) == -1)
	{
		ft_printf("pipex: cmmand not found: %s\n", "ls");
	}
}


