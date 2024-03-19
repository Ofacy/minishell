/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:53:51 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/19 18:53:58 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	env_to_envp_element(t_vector *env, char **envp, size_t i, size_t *envp_len)
{
	char	*tmp;

	if (!((t_env *)env->tab)[i].value)
		return (0);
	tmp = ft_strjoin(((t_env *)env->tab)[i].key, "=");
	if (!tmp)
	{
		ft_freesplit(envp);
		return (1);
	}
	envp[*envp_len] = ft_strjoin(tmp, ((t_env *)env->tab)[i].value);
	free(tmp);
	if (!envp[*envp_len])
	{
		ft_freesplit(envp);
		return (1);
	}
	(*envp_len)++;
	return (0);
}

char	**env_to_envp(t_vector *env)
{
	char	**envp;
	size_t	i;
	size_t	envp_len;

	i = 0;
	envp_len = 0;
	while (i < env->len)
	{
		if (((t_env *)env->tab)[i].value)
			envp_len++;
		i++;
	}
	envp = malloc(sizeof(char *) * (envp_len + 1));
	if (!envp)
		return (NULL);
	envp_len = 0;
	i = 0;
	while (i < env->len)
	{
		if (env_to_envp_element(env, envp, i, &envp_len) != 0)
			return (NULL);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	set_env_return(t_mshell *sh, int value)
{
	free(sh->last_return.value);
	sh->last_return.value = ft_itoa(value);
	if (!sh->last_return.value)
		return (1);
	sh->last_return.value_size = ft_strlen(sh->last_return.value);
	return (0);
}

void	sort_env(t_mshell *sh, t_env *env)
{
	size_t	i;
	size_t	j;
	t_env	tmp;

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
}
