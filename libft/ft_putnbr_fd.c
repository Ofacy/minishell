/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:51:25 by bwisniew          #+#    #+#             */
/*   Updated: 2023/11/09 13:02:11 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n > 9 || n < -9)
	{
		if (n < 0)
			ft_putnbr_fd(-(n / 10), fd);
		else
			ft_putnbr_fd(n / 10, fd);
	}
	if (n < 0)
		ft_putchar_fd(-(n % 10) + 48, fd);
	else
		ft_putchar_fd((n % 10) + 48, fd);
}
