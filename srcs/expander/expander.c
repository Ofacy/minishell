/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:13:27 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 19:48:02 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static bool	need_expand(t_token *token)
{
	return (token->type == UNQUOTED || token->type == DOUBLE_QUOTED);
}

int	expander(t_mshell *sh, size_t start, size_t end)
{
	int		i;
	t_token	*token;
	int		ret;

	i = start;
	while (i < end)
	{
		token = &sh->tokens.tab[i];
		if (need_expand(token))
		{
			ret = tokens_expand(sh, i);
			if (ret <= 0)
				return (1);
			i += ret;
		}
		else
			i++;
	}
	return (0);
}
