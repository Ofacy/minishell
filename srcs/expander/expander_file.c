/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:50:42 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 19:17:15 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander.h"
#include "libft.h"

size_t	expander_skip_file(t_vector *lex, size_t i, size_t n)
{
	if (i < n && is_type_arrow(((t_token *)lex->tab)[i].type))
	{
		((t_token *)lex->tab)[i + 1].is_file = true;
		i += 2;
		while (i < n && !((t_token *)lex->tab)[i - 1].is_separated
			&& !is_special(((t_token *)lex->tab)[i - 1].type))
		{
			((t_token *)lex->tab)[i].is_file = true;
			i++;
		}
		if (i < n)
			((t_token *)lex->tab)[i].is_file = true;
	}
	return (i);
}

size_t	expand_ambi_file(t_token *token, t_mshell *sh)
{
	size_t	txt_i;
	t_env	*env_var;

	txt_i = 0;
	while (txt_i < token->txt_size)
	{
		if (need_expand_str(token, txt_i))
		{
			env_var = env_get(sh, token->txt + txt_i + 1, false);
			if (env_var && token->type == UNQUOTED
				&& ft_strchr(env_var->value, ' ') != NULL)
			{
				custom_error(env_var->key, "ambiguous redirect");
				return (1);
			}
			txt_i += skip_envname(token->txt + txt_i + 1) + 1;
		}
		else
			txt_i++;
	}
	return (0);
}

int	expand_file(t_mshell *sh, size_t token_i)
{
	size_t	i_cp;

	i_cp = token_i;
	token_i++;
	while (token_i < sh->tokens.len
		&& ((t_token *)sh->tokens.tab)[token_i].is_file == 1)
	{
		if (expand_ambi_file(&((t_token *)sh->tokens.tab)[token_i], sh) != 0)
			return (1);
		token_i++;
	}
	if (expander(sh, i_cp + 1, expander_skip_file(&sh->tokens,
				i_cp, sh->tokens.len)) < 0)
		return (1);
	return (0);
}
