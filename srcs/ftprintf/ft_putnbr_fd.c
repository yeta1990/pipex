/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 21:04:01 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/06 21:52:37 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	recursive_printer(int n, int fd);

int	ft_putnbr_fd(int n, int fd)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	else
		recursive_printer(n, fd);
	if (n < 0)
		len++;
	len += ft_num_len(n);
	return (len);
}

static void	recursive_printer(int n, int fd)
{
	char			c;
	unsigned int	number;

	number = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		recursive_printer(number * -1 / 10, fd);
		c = (number * -1 % 10) + 48;
		ft_putchar_fd(c, fd);
	}
	if (n > 0)
	{
		recursive_printer(number / 10, fd);
		c = (number % 10) + 48;
		ft_putchar_fd(c, fd);
	}
}
