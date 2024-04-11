/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:40:18 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/13 12:59:46 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_get_length(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
		i++;
	while (n > 9 || n < -9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_get_length(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	if (n < 0)
		str[0] = '-';
	str[i] = '\0';
	i--;
	while (n != 0)
	{
		if (n < 0)
			str[i] = -(n % 10) + 48;
		else
			str[i] = (n % 10) + 48;
		n /= 10;
		if (n < 0)
			n *= -1;
		i--;
	}
	return (str);
}
