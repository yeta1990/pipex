/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 13:57:52 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/06 22:23:31 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_handler(va_list v, size_t *k, char c);

int	ft_printf(const char *str, ...)
{
	va_list		v;
	char		*str2;
	size_t		i;
	size_t		k;

	i = 0;
	k = 0;
	str2 = (char *)str;
	va_start(v, str);
	while (str2 && i < ft_strlen(str))
	{
		if (*str2 != '%')
			k += ft_putchar_fd(*str2, 1);
		else if (*str2 == '%')
		{
			str2++;
			ft_printf_handler(v, &k, *str2);
			i++;
		}
		str2++;
		i++;
	}
	va_end(v);
	return (k);
}

void	ft_printf_handler(va_list v, size_t *k, char c)
{
	if (c == 'c')
		*k += ft_putchar_fd(va_arg(v, int), 1);
	else if (c == 's')
		*k += ft_putstr_fd(va_arg(v, char *), 1);
	else if (c == 'i' || c == 'd')
		*k += ft_putnbr_fd(va_arg(v, int), 1);
	else if (c == 'x')
		*k += ft_putnbr_base(va_arg(v, int), "0123456789abcdef");
	else if (c == 'p')
	{
		*k += ft_putstr_fd("0x", 1);
		*k += ft_putnbr_base_long(va_arg(v, unsigned long), "0123456789abcdef");
	}
	else if (c == 'u')
		*k += ft_putnbr_base_long(va_arg(v, unsigned int), "0123456789");
	else if (c == 'X')
		*k += ft_putnbr_base(va_arg(v, int), "0123456789ABCDEF");
	else if (c == '%')
		*k += ft_putchar_fd('%', 1);
}
