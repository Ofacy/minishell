/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:25:19 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/16 15:24:00 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long long addr)
{
	char	*base;
	int		count;
	int		result;

	base = "0123456789abcdef";
	count = 0;
	if (!addr)
		return (ft_putstr("(nil)"));
	if (addr >= 16)
	{
		result = ft_putptr(addr / 16);
		if (result < 0)
			return (result);
		count += result;
	}
	else
	{
		count = ft_putstr("0x");
		if (count < 0)
			return (count);
	}
	result = ft_putchar(base[addr % 16]);
	if (result < 0)
		return (result);
	return (++count);
}
