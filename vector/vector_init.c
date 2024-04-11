/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:20:07 by bwisniew          #+#    #+#             */
/*   Updated: 2024/02/28 14:26:35 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	vector_init(t_vector *vector, size_t value_size)
{
	vector->alloc = 0;
	vector->len = 0;
	vector->tab = NULL;
	vector->value_size = value_size;
}
