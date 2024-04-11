/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:18:20 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 13:01:05 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*mem_dest;

	if (dest == src)
		return (dest);
	mem_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		mem_dest[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
