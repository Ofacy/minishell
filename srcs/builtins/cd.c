/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 22:35:17 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	cd_change_env(t_mshell *sh)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*new_pwd;

	pwd = env_get(sh, "PWD", false);
	if (pwd)
	{
		oldpwd = env_get(sh, "OLDPWD", true);
		if (oldpwd && env_set(sh, "OLDPWD", pwd->value) != 0)
		{
			custom_error("cd", "couldn't change OLDPWD");
			return (1);
		}
		new_pwd = getcwd(NULL, 0);
		if (new_pwd && env_set(sh, "PWD", new_pwd) != 0)
		{
			custom_error("cd", "couldn't change PWD");
			if (new_pwd)
				free(new_pwd);
			return (1);
		}
		free(new_pwd);
	}
	return (0);
}

int	cd_home(t_mshell *sh)
{
	t_env	*home;

	home = env_get(sh, "HOME", false);
	if (!home)
	{
		custom_error("cd", "HOME not set");
		return (1);
	}
	if (chdir(home->value) == -1)
	{
		error("cd");
		return (1);
	}
	return (cd_change_env(sh));
}

int	cd(t_mshell *sh, t_execute *exec)
{
	char	**args;

	(void)sh;
	args = exec->args.tab;
	if (args[1] == NULL)
		return (cd_home(sh));
	else if (args[2] != NULL)
	{
		custom_error("cd", "too many arguments");
		return (1);
	}
	else if (chdir(args[1]) == -1)
	{
		error("cd");
		return (1);
	}
	return (cd_change_env(sh));
}
