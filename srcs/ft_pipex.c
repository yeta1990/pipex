/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 13:08:44 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/30 00:50:49 by albgarci         ###   ########.fr       */
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
// https://stackoverflow.com/questions/5225810/is-it-possible-to-have-pipe-between-two-child-processes-created-by-same-parent
//

#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
	pid_t	child;

	int		child_status;
	int		cmds;
	char	**cmdargs;
	int		fds[2];	
	int		fds2[2];
	char	*cmd;
	cmds = count_cmds(argv);	
	argc = argc * 1;
	if (argc == 1 || cmds != 2)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (0);
	}

	if (pipe(fds) < 0)
		ft_putstr_fd("Error creating pipe", 2);
	child = fork();
	if (child == 0)
	{		
		close(fds[0]);
		dup2(fds[1], 1);
		close(fds[1]);
		int	buff;
		buff = 0;
		int fd3;

		fd3 = open(argv[1], O_RDONLY);
		if (fd3 <= 0)
		{
			perror("pipex");
			exit(1);
		}
		while (read(fd3, &buff, 1))
			write(1, &buff, 1);
	}
	waitpid(child, &child_status, 0);
	close(fds[1]);
	pipe(fds2);
	child = fork();
	if (child == 0)
	{
		close(fds2[0]);
		dup2(fds[0], 0);
		close(fds[0]);
		dup2(fds2[1], 1);
		close(fds2[1]);
		cmdargs = create_args(argv, 2);
		is_cmd(argv[2], &cmd);
		execve(cmd, &cmdargs[0], NULL);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, 0);
	close(fds[0]);
	close(fds2[1]);

	child = fork();
	if (child == 0)
	{
		dup2(fds2[0], 0);
		close(fds2[0]);
		cmdargs = create_args(argv, 4);
		is_cmd(argv[4], &cmd);
		execve(cmd, &cmdargs[0], NULL);
		perror("pipex");
		exit(1);
	}
	waitpid(child, &child_status, 0);
	close(fds2[0]);

	return (0);
}

char	**get_paths(void)
{
	int		fds[2]; 
	char **env;
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
