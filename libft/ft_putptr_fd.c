/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:27:00 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/21 19:27:53 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr_fd(unsigned long long addr, int fd)
{
	char	*base;
	int		count;
	int		result;

	base = "0123456789abcdef";
	count = 0;
	if (!addr)
		return (ft_putstr_fd("(nil)", fd));
	if (addr >= 16)
	{
		result = ft_putptr_fd(addr / 16, fd);
		if (result < 0)
			return (result);
		count += result;
	}
	else
	{
		count = ft_putstr_fd("0x", fd);
		if (count < 0)
			return (count);
	}
	result = ft_putchar_fd(base[addr % 16], fd);
	if (result < 0)
		return (result);
	return (++count);
}
