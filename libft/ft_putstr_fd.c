/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:30 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/02 08:58:00 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return (ft_putstr_fd("(null)", fd));
	if (write(fd, str, ft_strlen(str)) < 0)
		return (-1);
	return ((int)ft_strlen(str));
}
