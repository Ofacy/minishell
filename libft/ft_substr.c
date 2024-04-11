/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:41:18 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:04:42 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	total_length;
	char	*substr;

	if (start > ft_strlen(s))
	{
		substr = malloc(1);
		if (!substr)
			return (0);
		*substr = '\0';
		return (substr);
	}
	if (ft_strlen(s + start) < len)
		total_length = ft_strlen(s + start);
	else
		total_length = len;
	substr = malloc(total_length + 1);
	if (!substr)
		return (0);
	ft_strlcpy(substr, s + start, total_length + 1);
	return (substr);
}
