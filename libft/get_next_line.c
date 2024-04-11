/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:07 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/27 17:42:58 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void	*gnl_free_str(char *str, char *buffer)
{
	if (str)
		free(str);
	gnl_reset_buffer(buffer);
	return (NULL);
}

char	*gnl_trim_buffer(char	*buffer)
{
	long long	n;
	size_t		i;

	n = gnl_get_n(buffer);
	if (n < 0)
		return (NULL);
	i = 0;
	while (n < BUFFER_SIZE)
	{
		buffer[i] = buffer[n];
		buffer[n] = '\0';
		n++;
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

char	*gnl_join_buffer(char *str, char *buffer, long long n)
{
	size_t		str_len;
	size_t		new_str_len;
	char		*new_str;

	if (n < 0)
		str_len = 0;
	if (!str)
		str_len = 0;
	else
		str_len = ft_strlen(str);
	new_str_len = str_len + n + 1;
	new_str = malloc(sizeof(char) * (new_str_len));
	if (!new_str)
		return (gnl_free_str(str, buffer));
	new_str[0] = '\0';
	if (str)
		ft_strlcat(new_str, str, new_str_len);
	ft_strlcat(new_str, buffer, new_str_len);
	if (str)
		free(str);
	if (n < BUFFER_SIZE)
		buffer = gnl_trim_buffer(buffer);
	else
		buffer = gnl_reset_buffer(buffer);
	return (new_str);
}

char	*gnl_read_buffer(ssize_t n, char *buffer, int fd)
{
	char	*str;
	size_t	size;

	str = NULL;
	while (n > 0)
	{
		n = gnl_get_n(buffer);
		size = gnl_buffer_size(buffer);
		if ((n < 0 && size > 0) || (size > 0 && !str && buffer[n - 1] != '\n'))
		{
			str = gnl_join_buffer(str, buffer, size);
			if (!str)
				return (gnl_free_str(str, buffer));
		}
		else if (size > 0)
			return (gnl_join_buffer(str, buffer, n));
		gnl_reset_buffer(buffer);
		n = read(fd, buffer, BUFFER_SIZE);
		if (n < 0)
			return (gnl_free_str(str, buffer));
		if (n < BUFFER_SIZE && n > 0)
			return (gnl_join_buffer(str, buffer, gnl_get_n(buffer)));
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		gnl_reset_buffer(buffer);
		return (NULL);
	}
	else
		return (gnl_read_buffer(1, buffer, fd));
}
