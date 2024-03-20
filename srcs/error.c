/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:37:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/20 17:56:14 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

void	error(char *str)
{
	printf("%s: %s: %s\n", SHELL_NAME, str, strerror(errno));
}

void	custom_error(char *str, char *error_msg)
{
	printf("%s: %s: %s\n", SHELL_NAME, str, error_msg);
}

void	builtin_error(char *str, char *error_msg)
{
	printf("%s: %s\n", str, error_msg);
}
