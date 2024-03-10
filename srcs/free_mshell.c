/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:09:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/10 21:19:00 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>

void	free_mshell(t_mshell *sh)
{
	free(sh->input);
	vector_foreach(&sh->tokens, (void (*)(void *))free_token);
	vector_free(&sh->tokens);
	vector_free(&sh->history_entry);
	rl_clear_history();
	vector_foreach(&sh->env, (void (*)(void *))env_free);
	vector_free(&sh->env);
}
