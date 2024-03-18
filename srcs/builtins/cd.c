/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/18 11:30:27 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int	cd_change_env(t_mshell *sh)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*new_pwd;

	pwd = env_get(sh, "PWD");
	if (pwd)
	{
		oldpwd = env_get(sh, "OLDPWD");
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

	home = env_get(sh, "HOME");
	if (!home->value)
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
	else if (chdir(args[1]) == -1)
	{
		error("cd");
		return (1);
	}
	return (cd_change_env(sh));
}
