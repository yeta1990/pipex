/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 23:16:31 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/01 18:39:07 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (ft_putstr_fd("(null)", 1));
	while (s[i])
	{
		if (s[i] == '\0')
			i += ft_putstr_fd("(null)", 1);
		else
			ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
