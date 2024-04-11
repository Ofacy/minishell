/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:12:42 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/07 20:06:01 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

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

int	vector_realloc(t_vector *vector)
{
	void	*new_tab;

	if (vector->alloc == 0)
		vector->alloc = VECT_SIZE;
	else
		vector->alloc *= 2;
	new_tab = malloc(vector->value_size * vector->alloc);
	if (!new_tab)
	{
		if (vector->tab)
			free(vector->tab);
		return (-1);
	}
	ft_memcpy(new_tab, vector->tab, vector->value_size * vector->len);
	if (vector->tab)
		free(vector->tab);
	vector->tab = new_tab;
	return (0);
}
