/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:15:43 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:02:13 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_length;
	size_t	dst_length;
	size_t	i;

	dst_length = 0;
	while (dst[dst_length] && dst_length < size)
		dst_length++;
	src_length = 0;
	while (src[src_length])
		src_length++;
	if (size - dst_length == 0)
		return (dst_length + src_length);
	i = 0;
	while (src[i] && size - dst_length - i != 1)
	{
		dst[dst_length + i] = src[i];
		i++;
	}
	dst[dst_length + i] = '\0';
	return (dst_length + src_length);
}
