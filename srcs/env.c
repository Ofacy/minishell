/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:15:13 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/03 22:53:11 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

char	*ft_strcdup(const char *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	env_free(void *env)
{
	free(((t_env *)env)->key);
	free(((t_env *)env)->value);
}

int	env_set(t_mshell *sh, char *name, char *value)
{
	t_env	*env_var;
	t_env	env_tmp;

	env_var = env_get(sh, name, true);
	if (!env_var)
	{
		env_tmp.value = NULL;
		env_tmp.value_size = 0;
		env_tmp.key = ft_strdup(name);
		if (!env_tmp.key)
			return (1);
		env_tmp.key_size = ft_strlen(env_tmp.key);
		if (vector_add(&sh->env, &env_tmp) != 0)
			return (1);
		env_var = (t_env *)sh->env.tab + sh->env.len - 1;
	}
	if (!value)
		return (0);
	if (env_var->value)
		free(env_var->value);
	env_var->value = ft_strdup(value);
	if (!env_var->value)
		return (1);
	env_var->value_size = ft_strlen(value);
	return (0);
}

t_env	*env_get(t_mshell *sh, char *key, bool nullvalue)
{
	size_t		i;
	size_t		key_size;
	t_env		*env_var;
	t_vector	*env;

	if (key[0] == '?')
		return (&sh->last_return);
	env = &sh->env;
	key_size = 0;
	while (ft_strchr(ENV_NAME_CHAR, key[key_size]) != NULL && key[key_size])
		key_size++;
	i = 0;
	while (i < env->len)
	{
		env_var = (t_env *)env->tab + i;
		if (env_var->key_size == key_size
			&& ft_strncmp(env_var->key, key, key_size) == 0)
		{
			if (!nullvalue && !env_var->value)
				return (NULL);
			return (env_var);
		}
		i++;
	}
	return (NULL);
}

int	create_env(t_mshell *sh, char **env)
{
	char	*value;
	char	*key;
	size_t	i;

	i = 0;
	vector_init(&sh->env, sizeof(t_env));
	if (env_set(sh, "OLDPWD", NULL) != 0)
		return (1);
	if (env_set(sh, "PWD", NULL) != 0)
		return (1);
	if (env_set(sh, "SHLVL", "1") != 0)
		return (1);
	while (env[i])
	{
		key = ft_strcdup(env[i], '=');
		if (!key)
			return (1);
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!value)
			return (free(key), 1);
		if (env_set(sh, key, value) != 0)
			return (1);
		i++;
	}
	return (0);
}
