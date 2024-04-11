/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:24:23 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/19 16:56:18 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_no_flag(char c)
{
	if (ft_putchar('%') < 0)
		return (-1);
	if (ft_putchar(c) < 0)
		return (-1);
	return (2);
}

int	ft_convert(va_list args, char *str)
{
	int	count;

	if (*str == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (*str == '%')
		count = ft_putchar('%');
	else if (*str == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (*str == 'd' || *str == 'i')
		count = ft_putnbr_base(va_arg(args, int), "0123456789");
	else if (*str == 'u')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789");
	else if (*str == 'x')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (*str == 'X')
		count = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (*str == 'p')
		count = ft_putptr(va_arg(args, unsigned long long));
	else if (*str == '\0')
		return (-1);
	else
		count = ft_no_flag(*str);
	return (count);
}
