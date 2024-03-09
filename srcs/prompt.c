/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:12:55 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/09 18:36:21 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


t_token	prompt(t_mshell *sh)
{
	t_token	prompt;
	t_env	*env_prompt;

	env_prompt = env_get(&sh->env, "PROMPT");
	if (!env_prompt)
		prompt.txt = PROMPT_DEFAULT;
	else
		prompt.txt = env_prompt->value;
	prompt.txt_size = ft_strlen(prompt.txt);
	prompt.is_txt_heap = false;
	prompt.type = UNQUOTED;
	if (get_expended_str(&prompt, &sh->env) != 0)
		free_token(&prompt);
	return (prompt);
}

char	*get_user_input(t_mshell *sh)
{
	t_token	c_prompt;
	char	*input;

	c_prompt = prompt(sh);
	if (c_prompt.type == UNSET)
		return (NULL);
	input = readline(c_prompt.txt);
	free_token(&c_prompt);
	return (input);
}
