/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:34:59 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 19:32:17 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *str, ...)__attribute__((format(printf, 1, 2)));
int		ft_dprintf(int fd, const char *str, ...);
int		ft_convert(va_list args, char *str);
int		ft_convert_fd(int fd, va_list args, char *str);

#endif
