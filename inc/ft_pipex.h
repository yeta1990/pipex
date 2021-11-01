/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albgarci <albgarci@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:18:57 by albgarci          #+#    #+#             */
/*   Updated: 2021/11/01 18:37:53 by albgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlen(const char *s);
char	**get_paths(void);
int		is_cmd(char *file, char **cmd_ok);
char	**create_args(char *raw_cmd, char **cmd);
void	free_paths(char **paths);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split_mod(char const *str, char c);
char	**path_surgery(char **path_to_cut);
void	parse_and_execute(int argc, char **argv, int cmdargs);
void	input_error_checker(int argc);
void	ft_dup_infile(char *file);
void	ft_dup_output(char *file);
int		last_cmd(int argc, char **argv);
void	ft_exec_last(char **argv, int fds[2]);
void	ft_exec_first(char **argv, int fds[2]);
void	ft_exec_middle(char **argv, int fds[2], int last);
void	ft_exec_middle_ops(char **argv, int fds[2], int fds2[2], int i);
char	**ft_split(char const *str, char c);
int		ft_putstr_fd(char *s, int fd);
int		ft_putchar_fd(char c, int fd);

#endif
