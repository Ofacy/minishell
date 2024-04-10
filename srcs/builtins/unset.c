/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:38 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/09 23:24:44 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	env_remove(t_vector *env, t_env *var)
{
	if (!var)
		return ;
	env_free(var);
	vector_remove(env, var - (t_env *)env->tab);
}

int	unset(t_mshell *sh, t_execute *exec)
{
	t_env	*env;
	size_t	i;
	char	**args;

	args = exec->args.tab;
	if (!args[0])
	{
		custom_error("unset", "not enough arguments");
		return (1);
	}
	i = 0;
	while (args[i])
	{
		env = env_get(sh, args[i], false);
		env_remove(&sh->env, env);
		i++;
	}
	return (0);
}
