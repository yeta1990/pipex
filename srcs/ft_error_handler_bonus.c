/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 12:52:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/01 19:31:44 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	input_error_checker(int argc)
{
	if (argc == 1)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmdn...] outfile\n", 2);
		exit(1);
	}
}
