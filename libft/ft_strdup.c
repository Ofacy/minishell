/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:19:30 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:05:01 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*strdup;

	length = ft_strlen(s);
	if (length == SIZE_MAX)
		return (0);
	strdup = malloc(length + 1);
	if (!strdup)
		return (0);
	ft_strlcpy(strdup, s, length + 1);
	return (strdup);
}
