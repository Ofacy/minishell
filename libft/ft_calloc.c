/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:05:16 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 12:58:58 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptn;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (0);
	ptn = malloc(nmemb * size);
	if (!ptn)
		return (0);
	ft_bzero(ptn, size * nmemb);
	return (ptn);
}
