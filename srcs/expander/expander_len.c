/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:40:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 18:14:05 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <stdio.h>

bool	is_quoted(t_token *token)
{
	return (token->type == DOUBLE_QUOTED || token->type == SINGLE_QUOTED);
}

static bool	need_expand(t_token *token)
{
	return (token->type == UNQUOTED || token->type == DOUBLE_QUOTED);
}

bool	need_expand_str(t_token *token, size_t str_i)
{
	if (token->txt[str_i] == '$' && need_expand(token))
	{
		if (str_i + 1 < token->txt_size)
		{
			if (ft_strchr(ENV_NAME_CHAR, token->txt[str_i + 1]))
				return (true);
		}
		else if (!token->is_separated && token->type == UNQUOTED)
			return (true);
	}
	return (false);
}

size_t	expanded_len(t_mshell *sh, t_token *token)
{
	size_t	expanded_len;
	size_t	str_i;
	t_env	*env_var;

	expanded_len = 0;
	str_i = 0;
	while (str_i < token->txt_size)
	{
		if (need_expand_str(token, str_i))
		{
			env_var = env_get(sh, token->txt + str_i + 1, false);
			if (env_var)
				expanded_len += env_var->value_size;
			str_i += skip_envname(token->txt + str_i + 1);
		}
		else
			expanded_len++;
		str_i++;
	}
	return (expanded_len);
}
