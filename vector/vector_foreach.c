/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_foreach.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:55:18 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 23:04:40 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_foreach(t_vector *vector, void (*f)(void *))
{
	size_t	i;

	i = 0;
	while (i < vector->len)
	{
		f(((char *)vector->tab) + i * vector->value_size);
		i++;
	}
}
