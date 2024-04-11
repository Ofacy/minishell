/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:49:09 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 19:15:41 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(long nbr, char *base)
{
	long	base_len;
	int		count;
	int		result;

	count = 0;
	base_len = (long)ft_strlen(base);
	if (nbr < 0)
	{
		count = ft_putchar('-');
		if (count < 0)
			return (count);
	}
	if (nbr <= -base_len || nbr >= base_len)
	{
		result = ft_putnbr_base(((nbr >= 0) * 2 - 1) * (nbr / base_len), base);
		if (result < 0)
			return (-1);
		count += result;
	}
	result = ft_putchar(base[((nbr >= 0) * 2 - 1) * (nbr % base_len)]);
	if (result < 0)
		return (result);
	count++;
	return (count);
}
