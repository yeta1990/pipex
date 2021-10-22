/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 23:16:31 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/05 16:32:30 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
