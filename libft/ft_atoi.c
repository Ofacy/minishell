/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 08:40:55 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/19 16:42:11 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_getnb(const char *nptr, char sign, size_t i)
{
	long	nb;

	nb = 0;
	while (ft_isdigit(nptr[i]))
	{
		if (nb != (nb * 10 + nptr[i] - 48) / 10)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *nptr)
{
	size_t	i;
	char	sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = ft_getnb(nptr, sign, i);
	return ((int)(nb * sign));
}
