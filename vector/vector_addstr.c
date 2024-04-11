/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_addstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:11:30 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/11 15:50:36 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

static size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	vector_addstr(t_vector *vector, char *str)
{
	size_t	i;
	size_t	str_size;

	str_size = ft_strlen(str) + 1;
	if (vector->len + str_size > vector->alloc)
	{
		if (vector->alloc == 0)
			vector->alloc = VECT_SIZE;
		while (vector->alloc * 2 < vector->len + str_size)
			vector->alloc *= 2;
		if (vector_realloc(vector) < 0)
			return (-1);
	}
	i = 0;
	while (str[i])
	{
		((char *)vector->tab)[vector->len] = str[i];
		vector->len++;
		i++;
	}
	((char *)vector->tab)[vector->len] = str[i];
	return (0);
}
