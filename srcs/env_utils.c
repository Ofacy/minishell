/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:53:51 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/13 17:37:16 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	**env_to_envp(t_vector *env)
{
	char	**envp;
	char	*tmp;
	size_t	i;

	envp = malloc(sizeof(char *) * (env->len + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < env->len)
	{
		tmp = ft_strjoin(((t_env *)env->tab)[i].key, "=");
		if (!tmp)
		{
			ft_freesplit(envp);
			return (NULL);
		}
		envp[i] = ft_strjoin(tmp, ((t_env *)env->tab)[i].value);
		free(tmp);
		if (!envp[i])
			return (ft_freesplit(envp), NULL);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int	set_env_return(t_mshell *sh ,int value)
{
	sh->last_return.value = ft_itoa(value);
	if (!sh->last_return.value)
		return (1);
	sh->last_return.value_size = ft_strlen(sh->last_return.value);
	return (0);
}