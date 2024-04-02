/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:12:55 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/02 19:26:34 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_token	prompt(t_mshell *sh)
{
	t_token	prompt;
	t_env	*env_prompt;

	env_prompt = env_get(sh, "PROMPT", false);
	if (!env_prompt)
		prompt.txt = PROMPT_DEFAULT;
	else
		prompt.txt = env_prompt->value;
	prompt.txt_size = ft_strlen(prompt.txt);
	prompt.is_txt_heap = false;
	prompt.type = UNQUOTED;
	if (token_expand(&prompt, sh, expanded_len(sh, &prompt)) != 0)
		free_token(&prompt);
	return (prompt);
}

char	*get_user_input(t_mshell *sh)
{
	t_token	c_prompt;
	char	*input;

	c_prompt.txt = NULL;
	c_prompt.type = UNQUOTED;
	c_prompt.is_txt_heap = false;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		c_prompt = prompt(sh);
	if (c_prompt.type == UNSET)
		return (NULL);
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		input = readline(c_prompt.txt);
	else
		input = get_next_line(STDIN_FILENO);
	free_token(&c_prompt);
	return (input);
}
