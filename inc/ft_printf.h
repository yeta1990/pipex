/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:29:52 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/27 12:48:10 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
int		ft_putchar_fd(char c, int fd);
int		ft_putnbr_fd(int n, int fd);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlen(const char *str);
int		ft_putstr_fd(char *s, int fd);
size_t	ft_putnbr_base(size_t nbr, char *base);
size_t	ft_num_len(int n);
size_t	ft_putnbr_base_long(unsigned long long nbr, char *base);
int		count_cmds(char **argv);

#endif
