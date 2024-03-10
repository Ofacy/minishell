/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:37:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 20:47:38 by lcottet          ###   ########.fr       */
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
