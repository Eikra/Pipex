/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:18:47 by iecharak          #+#    #+#             */
/*   Updated: 2023/02/27 18:21:23 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*c;

	if (!s1 || !s2)
		return (NULL);
	c = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!c)
		return (NULL);
	j = 0;
	while (s1[j])
	{
		c[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i])
	{
		c[j] = s2[i];
		j++;
		i++;
	}
	c[j] = '\0';
	return (c);
}
