/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:44:00 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/14 09:39:39 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	recurs(unsigned int nbr, char *base, int base_len, size_t *len);

size_t	ft_putnbr_base(size_t nbr, char *base)
{
	int				base_len;
	unsigned int	number;
	size_t			len;

	len = 0;
	base_len = 0;
	number = 0;
	while (base[base_len])
	{
		if (base[base_len] == 43 || base[base_len] == 45)
			return (len);
		base_len++;
	}
	if (nbr == 0)
	{
		write(1, &base[nbr % base_len], 1);
		return (1);
	}
	if (nbr < 0)
		return (ft_putnbr_base(nbr * - 1, base));
	else
		number = nbr;
	recurs(number, base, base_len, &len);
	return (len);
}

void	recurs(unsigned int nbr, char *base, int base_len, size_t *len)
{
	if (nbr > 0)
	{
		(*len)++;
		recurs(nbr / base_len, base, base_len, len);
		write(1, &base[nbr % base_len], 1);
	}
}
