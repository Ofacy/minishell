/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:26:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/10 19:15:08 by lcottet          ###   ########.fr       */
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

int	vector_add(t_vector *vector, void *value)
{
	if (vector->len == vector->alloc)
		if (vector_realloc(vector) < 0)
			return (-1);
	ft_memcpy(vector->tab + vector->len * vector->value_size, value,
		vector->value_size);
	vector->len++;
	return (0);
}
