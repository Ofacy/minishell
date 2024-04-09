/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/09 15:37:39 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	cd_getcwd_err(t_mshell *sh, char *argv)
{
	char	*new_pwd;
	char	*pwd_slash;
	t_env	*pwd;

	custom_error("getcwd", "cannot access parent directories");
	if (argv)
	{
		pwd = env_get(sh, "PWD", false);
		if (!pwd)
			return (1);
		pwd_slash = ft_strjoin(pwd->value, "/");
		if (!pwd_slash)
			return (1);
		new_pwd = ft_strjoin(pwd_slash, argv);
		free(pwd_slash);
		if (!new_pwd)
			return (1);
		env_set(sh, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}

int	cd_change_env(t_mshell *sh, char *argv)
{
	t_env	*pwd;
	t_env	*oldpwd;
	char	*new_pwd;

	pwd = env_get(sh, "PWD", false);
	if (pwd)
	{
		oldpwd = env_get(sh, "OLDPWD", true);
		if (oldpwd && env_set(sh, "OLDPWD", pwd->value) != 0)
			return (custom_error("cd", "couldn't change OLDPWD"), 1);
		new_pwd = getcwd(NULL, 0);
		if (new_pwd && env_set(sh, "PWD", new_pwd) != 0)
		{
			custom_error("cd", "couldn't change PWD");
			if (new_pwd)
				free(new_pwd);
			return (1);
		}
		if (new_pwd)
			free(new_pwd);
		else
			cd_getcwd_err(sh, argv);
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
	return (cd_change_env(sh, NULL));
}

int	cd_oldpwd(t_mshell *sh)
{
	t_env	*oldpwd;

	oldpwd = env_get(sh, "OLDPWD", false);
	if (!oldpwd)
	{
		custom_error("cd", "OLDPWD not set");
		return (1);
	}
	if (chdir(oldpwd->value) == -1)
	{
		error("cd");
		return (1);
	}
	return (cd_change_env(sh, NULL));
}

int	cd(t_mshell *sh, t_execute *exec)
{
	char	**args;

	(void)sh;
	args = exec->args.tab;
	if (args[1] == NULL || (args[1] != NULL && args[1][0] == '~'))
		return (cd_home(sh));
	if (args[1] == NULL || (args[1] != NULL && args[1][0] == '-'))
		return (cd_oldpwd(sh));
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
	return (cd_change_env(sh, args[1]));
}
