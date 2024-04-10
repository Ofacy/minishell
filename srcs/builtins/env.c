/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/10 19:46:23 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_printf.h"

void	print_env(t_env *env)
{
	if (env->value)
		ft_printf("%s=%s\n", env->key, env->value);
}

int	env(t_mshell *sh, t_execute *exec)
{
	(void)exec;
	vector_foreach(&sh->env, (void (*)(void *))print_env);
	return (0);
}
