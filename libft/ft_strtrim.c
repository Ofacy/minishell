/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:05:16 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:04:38 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isset(char c, char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_start(char *s1, char *set)
{
	size_t	count;

	count = 0;
	while (s1[count] && ft_isset(s1[count], set) == 1)
		count++;
	return (count);
}

static int	ft_count_end(char *s1, char *set)
{
	size_t	count;
	size_t	size;

	count = 0;
	size = ft_strlen(s1) - 1;
	while (size > 0 && ft_isset(s1[size], set) == 1)
	{
		count++;
		size--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
	char	*str;

	len = ft_strlen(s1);
	start = ft_count_start((char *)s1, (char *)set);
	end = 0;
	if (len != start)
		end = ft_count_end((char *)s1, (char *)set);
	str = malloc(len - start - end + 1);
	if (!str)
		return (0);
	str[len - start - end] = '\0';
	ft_memcpy(str, s1 + start, len - start - end);
	return (str);
}
