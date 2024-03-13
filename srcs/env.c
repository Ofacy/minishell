/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:15:13 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/13 17:50:54 by bwisniew         ###   ########.fr       */
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

	env_var = env_get(sh, name);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
		if (!env_var->value)
			return (1);
	}
	else
	{
		env_tmp.key = ft_strdup(name);
		if (!env_tmp.key)
			return (1);
		env_tmp.value = ft_strdup(value);
		if (!env_tmp.value)
			return (free(env_tmp.key), 1);
		env_tmp.key_size = ft_strlen(env_tmp.key);
		env_tmp.value_size = ft_strlen(env_tmp.value);
		if (vector_add(&sh->env, &env_tmp) != 0)
			return (1);
	}
	return (0);
}

t_env	*env_get(t_mshell *sh, char *key)
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
		if (env_var->key_size != key_size)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(env_var->key, key, key_size) == 0)
			return (env_var);
		i++;
	}
	return (NULL);
}

int	create_env(t_vector *vector, char **env)
{
	t_env		env_tmp;
	size_t		i;

	i = 0;
	vector_init(vector, sizeof(t_env));
	while (env[i])
	{
		env_tmp.key = ft_strcdup(env[i], '=');
		if (!env_tmp.key)
			return (1);
		env_tmp.value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_tmp.value)
			return (free(env_tmp.key), 1);
		env_tmp.key_size = ft_strlen(env_tmp.key);
		env_tmp.value_size = ft_strlen(env_tmp.value);
		if (vector_add(vector, &env_tmp) != 0)
			return (1);
		i++;
	}
	return (0);
}
