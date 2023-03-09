/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:57:02 by iecharak          #+#    #+#             */
/*   Updated: 2023/03/02 12:18:23 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_add_to_str(str, fd);
	if (!str)
		return (NULL);
	line = ft_str_to_line(str);
	str = ft_clean_str(str);
	return (line);
}

char	*ft_read_add_to_str(char *str, int fd)
{
	int		readed;
	char	*buffer;

	readed = 1;
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (ftg_strchr(str, '\n') == 0 && readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (free(str), free(buffer), NULL);
		if (readed == 0)
			break ;
		buffer[readed] = '\0';
		str = add_to_str(str, buffer, readed);
	}
	free(buffer);
	return (str);
}

char	*add_to_str(char *str, char *buffer, int readed)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = malloc(sizeof(char) * (ftg_strlen(str) + readed + 1));
	if (!s)
		return (NULL);
	while (str && str[j])
	{
		s[j] = str[j];
		j++;
	}
	while (buffer[i])
	{
		s[j] = buffer[i];
		i++;
		j++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

char	*ft_str_to_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_clean_str(char *str)
{
	char	*current;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	current = malloc(ftg_strlen(str) - i + 1);
	if (!current)
	{
		free(str);
		return (NULL);
	}
	current = ft_memcpy(current, str, i);
	free(str);
	return (current);
}
