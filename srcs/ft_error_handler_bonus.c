/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:52:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/01 00:02:27 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	input_error_checker(int argc, char **argv)
{
	int		cmds;

	cmds = count_cmds(argv);
	if (argc == 1 || cmds < 2)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmdn...] outfile\n", 2);
		exit(1);
	}
	if (is_cmd(argv[argc - 1], NULL))
	{
		ft_putstr_fd("Error: last parameter must be an output file.\n", 2);
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
}
