/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_addi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 19:03:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/19 17:07:54 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
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

static void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*mem_dest;

	mem_dest = (unsigned char *)dest;
	if (dest == src || n == 0)
		return (dest);
	else if (dest > src && dest <= src + n)
		while (n--)
			mem_dest[n] = ((unsigned char *)src)[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}

int	vector_addi(t_vector *vector, void *value, size_t index)
{
	if (vector->len == vector->alloc)
		if (vector_realloc(vector) < 0)
			return (-1);
	if (index > vector->len)
		index = vector->len;
	ft_memmove(vector->tab + vector->value_size * (index + 1),
		vector->tab + vector->value_size * (index),
		vector->value_size * (vector->len - index));
	ft_memcpy(vector->tab + vector->value_size * index, value,
		vector->value_size);
	vector->len++;
	return (0);
}
