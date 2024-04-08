/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:34 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/08 15:49:06 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	pwd(t_mshell *sh, t_execute	*exec)
{
	char	*pwd;
	t_env	*env;

	(void)exec;
	env = env_get(sh, "PWD", false);
	if (env)
	{
		printf("%s\n", env->value);
		return (0);
	}
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
