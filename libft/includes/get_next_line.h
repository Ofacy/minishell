/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:02:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/01/18 16:33:22 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stddef.h>
# include "libft.h"

char		*get_next_line(int fd);
char		*gnl_trim_buffer(char	*buffer);
char		*gnl_reset_buffer(char *buffer);
char		*gnl_join_buffer(char *str, char *buffer, long long n);
long long	gnl_get_n(char	*buffer);
size_t		gnl_buffer_size(char *buffer);
void		*gnl_free_str(char *str, char *buffer);

#endif