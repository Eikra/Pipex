/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iecharak <iecharak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 10:48:17 by iecharak          #+#    #+#             */
/*   Updated: 2023/02/27 18:21:08 by iecharak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	count_word(char const *s, int c)
{
	size_t	i;
	size_t	count;
	int		done_null;

	count = 0;
	i = 0;
	done_null = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && s[i] && done_null > 0)
		{
			count++;
			done_null = -1;
		}
		if ((s[i] == c || !s[i]) && done_null < 0)
		{
			done_null = 1;
		}
		i++;
	}
	return (count);
}

char	*word_split(char const *s, int start, int end)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (end - start + 2));
	if (!word)
		return (NULL);
	while (start <= end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_free(char **s, int i)
{
	i--;
	while (s[i])
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**ft_spliter(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	j = 0;
	i = -1;
	while (++i < ft_strlen(s))
	{
		start = i;
		while (s[i] != c && s[i])
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			{
				tab[j] = word_split(s, start, i);
				if (tab[j] == NULL)
					return (ft_free(tab, j));
				j++;
			}
			i++;
		}
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!tab)
		return (NULL);
	tab = ft_spliter(tab, s, c);
	return (tab);
}
