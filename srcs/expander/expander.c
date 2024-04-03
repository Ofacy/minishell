/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:13:27 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 18:11:59 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>

int	expander(t_mshell *sh, size_t start, size_t end)
{
	size_t	token_i;
	int		ret;

	token_i = expander_skip_file(&sh->tokens, start, end);
	while (token_i < end)
	{
		if (!is_special(((t_token *)sh->tokens.tab)[token_i].type))
		{
			ret = tokens_expand(sh, token_i);
			if (ret < 0)
				return (1);
			token_i += ret;
			end += ret - 1;
		}
		else
			token_i++;
		token_i = expander_skip_file(&sh->tokens, token_i, end);
	}
	return (expander_unseparated(&sh->tokens, start, token_i));
}
