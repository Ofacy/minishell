/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:40:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/26 16:23:17 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

bool	is_white_end(char c)
{
	return (ft_isspace(c) || c == '\0');
}

bool	is_quoted(t_token *token)
{
	return (token->type == DOUBLE_QUOTED || token->type == SINGLE_QUOTED);
}

bool	need_expand_str(t_token *token, size_t str_i)
{
	if (token->txt[str_i] == '$'
		&& ft_strchr(ENV_NAME_CHAR, token->txt[str_i + 1]))
		return (true);
	if (token->txt[str_i] == '$' && is_white_end(str_i + 1))
		return (false);
	else if (token->txt[str_i] == '$'
		&& !is_white_end(str_i + 1) && token->type != DOUBLE_QUOTED)
		return (true);
	return (false);
}

size_t	expanded_len(t_mshell *sh, size_t token_i)
{
	t_token	*token;
	size_t	expanded_len;
	size_t	str_i;
	t_env	*env_var;

	token = &sh->tokens.tab[token_i];
	expanded_len = 0;
	str_i = 0;
	while (str_i < token->txt_size)
	{
		if (need_expand_str(token, str_i))
		{
			env_var = env_get(sh, token->txt + str_i + 1, false);
			if (env_var)
			{
				str_i += env_var->key_size;
				expanded_len += env_var->value_size;
			}
			else
				str_i += skip_envname(token->txt + str_i + 1) + 1;
		}
		else
			expanded_len++;
		str_i++;
	}
	return (expanded_len);
}
