/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:38 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/20 19:37:02 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	is_key_valid(char *str)
{
	size_t	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
	{
		custom_error(str, "not a valid identifier");
		return (1);
	}
	i++;
	while (str[i])
	{
		if (ft_strchr(ENV_NAME_CHAR, str[i]) == NULL)
		{
			custom_error(str, "not a valid identifier");
			return (1);
		}
		(i)++;
	}
	return (0);
}


int	unset(t_mshell *sh, t_execute *exec)
{
	t_env	*env;
	size_t	i;
	int		has_err;
	char	**args;

	args = exec->args.tab;
	if (!args[0])
	{
		custom_error("unset", "not enough arguments");
		return (1);
	}
	i = 0;
	has_err = 0;
	while (args[i])
	{
		if (is_key_valid(args[i]) != 0)
			has_err = 1;
		env = env_get(sh, args[i], false);
		if (env)
			vector_remove(&sh->env, env - (t_env *)sh->env.tab);
		i++;
	}
	return (has_err);
}
