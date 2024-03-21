/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:40:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 20:37:01 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

bool	is_white_end(char c)
{
	return (ft_isspace(c) && c == '\0');
}

bool	is_quoted(t_token *token)
{
	return (token->type == DOUBLE_QUOTED || token->type == SINGLE_QUOTED);
}

bool	need_expend(t_mshell *sh, size_t token_i, size_t str_i)
{
	t_token	*token;

	token = &sh->tokens.tab[token_i];
	if (token->txt[str_i] == '$' && )
	{
		if ()
		{
			
		}
	}
	else if (token->txt[str_i] == '$')
	{

	}
	else
		return (false);
}

t_env	*expand_size(char *str, size_t i)
{
	t_expand_size	size;
	t_env			*env_var;

}

size_t	expanded_len(t_mshell *sh, size_t token_i)
{
	t_token	*token;
	size_t	expanded_len;
	size_t	str_i;
	size_t	ret;

	token = &sh->tokens.tab[token_i];
	expanded_len = 0;
	str_i = 0;
	while (str_i < token->txt_size)
	{
		if (token->txt[str_i] == '$')
		{
			ret = 
		}
		else
			expanded_len++;
		str_i++;
	}
	
}
