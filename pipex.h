/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 20:28:04 by iecharak          #+#    #+#             */
/*   Updated: 2023/03/09 19:43:19 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 1

typedef struct int_strcuct
{
	int	i;
	int	j;
}		t_int;

int		ft_printf(const char *s, ...);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ftg_strlen(const char *s);
char	*ftg_strchr(const char *s, int c);
char	*ft_memcpy(char *dst, char *src, int index);
char	*get_next_line(int fd);
char	*ft_read_add_to_str(char *str, int fd);
char	*add_to_str(char *str, char *buffer, int readed);
char	*ft_str_to_line(char *str);
char	*ft_clean_str(char *str);
void	pipex_bonus(int *fd, int ac, char **av, char **env);
void	pipex_herdoc(int fd, int ac, char **av, char **env);
char	*get_path(char **env, char **cmd);
void	second_cmds(int fd, char **cmnds, char **env, int end[2]);
void	first_cmds(int fd, char **cmnds, char **env, int end[2]);

#endif