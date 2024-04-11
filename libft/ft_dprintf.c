/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:17:20 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/02 08:56:40 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list	args;
	int		count;
	int		result;
	char	*str;

	str = (char *)s;
	count = 0;
	va_start(args, s);
	while (*str)
	{
		if (*str == '%')
			result = ft_convert_fd(fd, args, ++str);
		else
			result = ft_putchar_fd(*str, fd);
		if (result < 0)
		{
			va_end(args);
			return (-1);
		}
		count += result;
		str++;
	}
	va_end(args);
	return (count);
}
