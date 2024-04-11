/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:37 by bwisniew          #+#    #+#             */
/*   Updated: 2024/01/18 16:32:55 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "get_next_line.h"

size_t	gnl_buffer_size(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i])
		i++;
	return (i);
}

long long	gnl_get_n(char	*buffer)
{
	size_t	n;

	n = 0;
	while (n < BUFFER_SIZE && (buffer[n] != '\n' && buffer[n] != '\0'))
		n++;
	if (n < BUFFER_SIZE && buffer[n] == '\n')
		return (n + 1);
	if (n < BUFFER_SIZE && buffer[n] == '\0')
		return (n);
	else
		return (-1);
}

char	*gnl_reset_buffer(char *buffer)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
	return (buffer);
}
