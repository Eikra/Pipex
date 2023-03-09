/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:09:00 by iecharak          #+#    #+#             */
/*   Updated: 2023/02/27 18:21:51 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr_ft(char *substr, char const *s, unsigned int start,
		size_t sub_len)
{
	unsigned int	i;

	i = 0;
	while (i < sub_len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*substr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		substr = malloc(sizeof(char) * 1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > (ft_strlen(s) - start))
		sub_len = ft_strlen(s) - start;
	if (len <= (ft_strlen(s) - start))
		sub_len = len;
	substr = (char *)malloc(sub_len + 1);
	if (!substr)
		return (NULL);
	return (ft_substr_ft(substr, s, start, sub_len));
}
