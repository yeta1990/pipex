/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:59:56 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/04 16:57:33 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_dup_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		write(2, file, ft_strlen(file));
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	//	exit(0);
	//	close(fd);
		//close(fd);
	//	return (0);
	}
	if (dup2(fd, 0) < 0)
	{
		exit(EXIT_FAILURE);
		exit(1);
		return (-1);
	}
	else
	{
		dup(0);
		close(0);
	}
	close(fd);
	return (1);
}

void	ft_dup_output(char *file)
{
	int	fdout;

	fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fdout < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		write(2, file, ft_strlen(file));
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(errno);
	}
	close(1);
	dup(fdout);
}
