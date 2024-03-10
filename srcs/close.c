/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:34:14 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/10 22:28:13 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include "libft.h"

int	close_fd(t_fd *fd)
{
	char *fd_str;

	if (*fd == -1)
		return (0);
	if (close(*fd) < 0)
	{
		fd_str = ft_itoa(*fd);
		if (!fd_str)
			return (error("close"), -1);
		error(fd_str);
		free(fd_str);
		return (-1);
	}
	*fd = -1;
	return (0);
}

int	close_exec(t_execute *exec)
{
	int	result;

	result = 0;
	if (close_fd(&(exec->in)) < 0)
		result = -1;
	if (close_fd(&(exec->out)) < 0)
		result = -1;
	if (close_fd(&(exec->nextin)) < 0)
		result = -1;
	return (result);
}
