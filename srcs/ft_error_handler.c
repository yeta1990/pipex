/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:38:20 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/25 17:43:29 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_check_input_file(char *file)
{
	int r;
	r = open(file, O_RDONLY);
	if (r < 0)
	{
		ft_putstr_fd(ft_strjoin("pipex: ", file), 2);
		ft_putstr_fd(ft_strjoin(": ", strerror(errno)), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	return (1);
}
