/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_files.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:59:56 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/30 13:14:16 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_dup_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("pipex");
		exit(1);
	}
	dup2(fd, 0);
	close(fd);
}

void	ft_dup_output(char *file)
{
	int	fdout;

	fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fdout < 0)
	{
		perror("pipex");
		exit(1);
	}
	close(1);
	dup(fdout);
}
