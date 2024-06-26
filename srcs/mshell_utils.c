/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:09:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/09 23:32:52 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>

void	init_mshell(t_mshell *sh)
{
	builtin_init(sh);
	sh->last_return.key = "?";
	sh->last_return.key_size = 1;
	sh->last_return.value = ft_itoa(0);
	sh->last_return.value_size = 1;
	sh->exit = -1;
}

void	free_mshell(t_mshell *sh)
{
	if (!sh)
		return ;
	free(sh->input);
	free(sh->last_return.value);
	vector_foreach(&sh->tokens, (void (*)(void *))free_token);
	vector_free(&sh->tokens);
	rl_clear_history();
	vector_foreach(&sh->env, (void (*)(void *))env_free);
	vector_free(&sh->env);
}
