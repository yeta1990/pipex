/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:18:57 by albgarci          #+#    #+#             */
/*   Updated: 2021/10/27 23:56:11 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

#include <unistd.h>
#include "ft_printf.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	**get_paths(void);
int		ft_input_or_cmd(char *file);
int		is_cmd(char *file, char **cmd_ok);
char	**create_args(char **argv, int start);
void	free_paths(char **paths);
char	*ft_strtrim(char const *s1, char const *set);
//char	**get_emergency_paths(void);
char	**ft_split_mod(char const *str, char c);
char	**path_surgery(char **path_to_cut);
void	one_cmd_no_outfile(char **argv, int pos);
void	parse_and_execute(int argc, char **argv, int cmdargs);

#endif
