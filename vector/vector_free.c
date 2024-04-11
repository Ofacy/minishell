/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:40:50 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/11 16:38:14 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <stdlib.h>

void	vector_free(t_vector *vector)
{
	if (vector->tab)
		free(vector->tab);
	vector_init(vector, vector->value_size);
}
