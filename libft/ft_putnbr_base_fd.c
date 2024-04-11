/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:24:44 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/02 08:58:31 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base_fd(long nbr, char *base, int fd)
{
	long	base_len;
	int		count;
	int		result;

	count = 0;
	base_len = (long)ft_strlen(base);
	if (nbr < 0)
	{
		count = ft_putchar_fd('-', fd);
		if (count < 0)
			return (count);
	}
	if (nbr <= -base_len || nbr >= base_len)
	{
		result = ft_putnbr_base_fd(((nbr >= 0) * 2 - 1) * (nbr / base_len),
				base, fd);
		if (result < 0)
			return (-1);
		count += result;
	}
	result = ft_putchar_fd(base[((nbr >= 0) * 2 - 1) * (nbr % base_len)], fd);
	if (result < 0)
		return (result);
	count++;
	return (count);
}
