/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:06:49 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:03:35 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	dst_length;

	src_length = 0;
	dst_length = 0;
	while (src[src_length])
	{
		if (dst_length < size - 1 && size > 0)
		{
			dst[dst_length] = src[dst_length];
			dst_length++;
		}
		src_length++;
	}
	if (size != 0)
	{
		dst[dst_length] = '\0';
	}
	return (src_length);
}
