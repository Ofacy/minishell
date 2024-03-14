/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:34 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/14 18:36:30 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int	pwd(t_mshell *sh, t_execute	*exec)
{
	char	*pwd;

	(void)exec;
	(void)sh;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
