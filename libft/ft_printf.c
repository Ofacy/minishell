/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:47:09 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 19:17:04 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>

int	ft_printf(const char *s, ...)
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
			result = ft_convert(args, ++str);
		else
			result = ft_putchar(*str);
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
