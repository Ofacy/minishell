/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:26:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/19 19:27:19 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static size_t	add_env_len(t_token *token, t_mshell *sh, size_t i)
{
	t_env	*env_var;

	env_var = env_get(sh, token->txt + i + 1, false);
	if (env_var)
		return (env_var->value_size);
	return (0);
}

size_t	expended_len(t_token *token, t_mshell *sh)
{
	size_t	exp_size;
	size_t	i;
	size_t	v_size;

	i = 0;
	exp_size = 0;
	while (i < token->txt_size)
	{
		if (token->txt[i] == '$' && token->type != SINGLE_QUOTED)
		{
			exp_size += add_env_len(token, sh, i);
			v_size = skip_env_name(token->txt + i + 1);
			if (token->txt[i + v_size + 1] == '?')
				i++;
			else if (v_size == 0)
				exp_size++;
			i += v_size;
		}
		else
			exp_size++;
		i++;
	}
	return (exp_size);
}

int	get_expended_tokens(t_vector *tokens, size_t *i, t_mshell *sh)
{
	t_token		*token;

	token = ((t_token *)tokens->tab) + (*i);
	if (get_expended_str(token, sh) != 0)
		return (1);
	if (token->old_type == UNQUOTED && token->txt != NULL)
	{
		if (expender_token_split(tokens, i) != 0)
			return (1);
	}
	return (0);
}

int	join_unseparated(t_vector *lex, size_t i, size_t n)
{
	t_token	*token;
	char	*tmp;

	while (i < n)
	{
		token = ((t_token *)lex->tab) + i;
		while (!token->is_separated)
		{
			tmp = expander_join(token,
					((t_token *)lex->tab) + i + 1);
			if (!tmp)
				return (1);
			token->txt = tmp;
			vector_remove(lex, i + 1);
		}
		if (((t_token *)lex->tab)[i].type == SINGLE_QUOTED)
			((t_token *)lex->tab)[i].type = UNQUOTED;
		i = expander_skip_arrow(lex, i, n);
		i++;
	}
	return (0);
}

int	expander(t_mshell *sh, size_t start, size_t end)
{
	size_t		i_cp;
	size_t		start_len;
	size_t		begin_end;
	t_vector	*lex;

	i_cp = start;
	lex = &sh->tokens;
	begin_end = end;
	start_len = sh->tokens.len;
	while (start < end)
	{
		if (((t_token *)lex->tab)[start].txt != NULL
			&& !is_special(((t_token *)lex->tab)[start].type))
			if (get_expended_tokens(&sh->tokens, &start, sh) != 0)
				return (1);
		start = expander_skip_arrow(lex, start, end);
		end = begin_end + sh->tokens.len - start_len;
		start++;
	}
	return (join_unseparated(lex, i_cp, end));
}
