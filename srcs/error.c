/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:37:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/21 12:45:45 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"
#include <errno.h>
#include <string.h>

void	error(char *str)
{
	ft_printf("%s: %s: %s\n", SHELL_NAME, str, strerror(errno));
}

void	custom_error(char *str, char *error_msg)
{
	ft_printf("%s: %s: %s\n", SHELL_NAME, str, error_msg);
}

void	builtin_error(char *str, char *error_msg)
{
	ft_printf("%s: %s\n", str, error_msg);
}
