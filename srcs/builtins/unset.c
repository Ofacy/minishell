/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:38 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/14 18:21:01 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		env = env_get(sh, args[i]);
		if (env)
			vector_remove(&sh->env, env - (t_env *)sh->env.tab);
		i++;
	}
	return (0);
}
