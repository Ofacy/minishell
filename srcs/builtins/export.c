/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:39 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/18 15:25:29 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

t_env	*export_sort(t_mshell *sh)
{
	t_env	*env;
	t_env	tmp;
	size_t	i;
	size_t	j;

	env = malloc((sh->env.len + 1) * sizeof(t_env));
	if (!env)
		return (NULL);
	ft_memcpy(env, sh->env.tab, sh->env.len * sizeof(t_env));
	i = 0;
	while (i < sh->env.len)
	{
		j = i;
		while (j < sh->env.len)
		{
			if (ft_strcmp(env[j].key, env[i].key) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

int	export_print(t_mshell *sh)
{
	size_t	i;
	t_env	*env;

	i = 0;
	env = export_sort(sh);
	if (!env)
		return (1);
	while (i < sh->env.len)
	{
		if (printf("%s=%s\n", env[i].key, env[i].value) == -1)
			return (0);
		i++;
	}
	free(env);
	return (0);
}

int	try_export(t_mshell *sh, char *str)
{
	size_t	i;
	int		ret;
	char	*name;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_strchr(ENV_NAME_CHAR, str[i]) == NULL)
		{
			custom_error(str, "not a valid identifier");
			return (1);
		}
		i++;
	}
	if (i == 0)
	{
		custom_error(str, "not a valid identifier");
		return (1);
	}
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (1);
	ft_strlcpy(name, str, i + 1);
	value = str + i + 1;
	if (str[i] != '=')
		value = "";
	ret = env_set(sh, name, value);
	free(name);
	return (ret);
}

int	export(t_mshell *sh, t_execute *exec)
{
	size_t	i;
	int		ret;
	char	**args;

	args = exec->args.tab;
	ret = 0;
	i = 1;
	while (args[i])
	{
		if (try_export(sh, args[i]) != 0)
			ret = 1;
		i++;
	}
	if (i == 1)
	{
		return (export_print(sh));
	}
	return (ret);
}