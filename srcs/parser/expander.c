/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:26:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/13 17:53:01 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

size_t	expended_len(t_token *token, t_mshell *sh)
{
	size_t	exp_size;
	t_env	*env_var;
	size_t	i;
	size_t	v_size;

	i = 0;
	exp_size = 0;
	while (i < token->txt_size)
	{
		if (token->txt[i] == '$' && token->type != SINGLE_QUOTED)
		{
			env_var = env_get(sh, token->txt + i + 1);
			if (env_var)
				exp_size += env_var->value_size;
			v_size = 0;
			while (ft_strchr(ENV_NAME_CHAR, token->txt[i + v_size + 1]) != NULL
				&& token->txt[i + v_size + 1])
				v_size++;
			if (v_size == 0)
				exp_size++;
			i += v_size;
		}
		else
			exp_size++;
		i++;
	}
	return (exp_size);
}

int	replace_env_var(char *token_str, char *exp_str, t_mshell *sh)
{
	t_env	*env_var;

	env_var = env_get(sh, token_str);
	if (!env_var)
		return (0);
	ft_strlcpy(exp_str, env_var->value, env_var->value_size + 1);
	return (env_var->value_size);
}

int	get_expended_str(t_token *token, t_mshell *sh)
{
	char	*exp_str;
	size_t	exp_len;
	size_t	i;
	size_t	exp_i;
	size_t	v_size;

	exp_len = expended_len(token, sh);
	exp_str = malloc(sizeof(char) * (exp_len + 1));
	if (!exp_str)
		return (1);
	exp_i = 0;
	i = 0;
	while (exp_i < exp_len)
	{
		if (token->txt[i] == '$' && token->type != SINGLE_QUOTED)
		{
			exp_i += replace_env_var(token->txt + i + 1, exp_str + exp_i, sh);
			v_size = 0;
			while (ft_strchr(ENV_NAME_CHAR, token->txt[i + v_size + 1]) != NULL
				&& token->txt[i + v_size + 1])
				v_size++;
			if (v_size == 0)
				exp_str[exp_i++] = '$';
			i += v_size;
		}
		else
			exp_str[exp_i++] = token->txt[i];
		i++;
	}
	free_token(token);
	exp_str[exp_i] = '\0';
	token->txt = exp_str;
	token->txt_size = exp_i;
	token->is_txt_heap = true;
	token->type = UNQUOTED;
	return (0);
}

int	join_unseparated(t_vector *lex, size_t i, size_t n)
{
	t_token	*token;
	char	*tmp;

	while (i < n)
	{
		token = ((t_token *)lex->tab) + i;
		if (!token->is_separated)
		{
			tmp = expander_join(token,
					((t_token *)lex->tab) + i + 1);
			if (!tmp)
				return (1);
			token->txt = tmp;
			token->is_separated = false;
			vector_remove(lex, i + 1);
		}
		if (((t_token *)lex->tab)[i].type == SINGLE_QUOTED)
			((t_token *)lex->tab)[i].type = UNQUOTED;
		i = expander_skip_arrow(lex, i, n);
		i++;
	}
	return (0);
}

int	expander(t_mshell *sh, size_t i, size_t n)
{
	size_t	i_cp;
	t_vector *lex;

	i_cp = i;
	lex = &sh->tokens;
	while (i < n)
	{
		if (((t_token *)lex->tab)[i].txt != NULL && !is_special(((t_token *)lex->tab)[i].type))
			if (get_expended_str(((t_token *)lex->tab) + i, sh) != 0)
				return (1);
		i = expander_skip_arrow(lex, i, n);
		i++;
	}
	return (join_unseparated(lex, i_cp, n));
}
