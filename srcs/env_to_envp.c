/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:53:51 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 22:02:11 by lcottet          ###   ########.fr       */
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
