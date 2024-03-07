/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:15:13 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 23:18:23 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

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
	free(((t_env *)env)->name);
	free(((t_env *)env)->value);
}

int	env_set(t_vector *env, char *name, char *value)
{
	t_env	*env_var;
	t_env	env_tmp;

	env_var = env_get(env, name);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(value);
		if (!env_var->value)
			return (1);
	}
	else
	{
		env_tmp.name = ft_strdup(name);
		env_tmp.value = ft_strdup(value);
		if (!env_tmp.name || !env_tmp.value)
			return (1);
		if (vector_add(env, &env_tmp) != 0)
			return (1);
	}
	return (0);
}

char	*env_get(t_vector *env, char *name, size_t size)
{
	size_t	i;
	t_env	*env_var;

	i = 0;
	while (i < env->len)
	{
		env_var = (t_env *)env->tab + i;
		if (ft_strncmp(env_var->name, name, size) == 0)
			return (env_var->value);
		i++;
	}
	return ("");
}

int	create_env(t_vector *vector, char **env)
{
	t_env		env_tmp;
	size_t		i;

	i = 0;
	vector_init(vector, sizeof(t_env));
	while (env[i])
	{
		env_tmp.name = ft_strcdup(env[i], '=');
		env_tmp.value = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (!env_tmp.name || !env_tmp.value)
			return (1);
		if (vector_add(vector, &env_tmp) != 0)
			return (1);
		i++;
	}
	return (0);
}
