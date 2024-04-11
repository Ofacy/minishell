/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:26:00 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:01:36 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
			size++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (size);
}

static char	**ft_free_tab(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != 0)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (0);
}

static char	*ft_create_word(char const *s, char c)
{
	char	*word;
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	word = malloc((sizeof(char) * i) + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, s, i);
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	i_strs;
	char	**strs;

	strs = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!strs)
		return (0);
	i = 0;
	i_strs = 0;
	strs[i_strs] = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			strs[i_strs] = ft_create_word(s + i, c);
			if (!strs[i_strs])
				return (ft_free_tab(strs));
			strs[++i_strs] = 0;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	return (strs);
}
