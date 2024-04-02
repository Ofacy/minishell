/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:13:27 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/02 19:16:58 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>

int	expander(t_mshell *sh, size_t start, size_t end)
{
	size_t	i;
	size_t	token_i;
	int		ret;

	i = start;
	token_i = start;
	while (i < end)
	{
		if (((t_token *)sh->tokens.tab)[token_i].is_file == 0)
		{
			ret = tokens_expand(sh, token_i);
			if (ret < 0)
				return (1);
			token_i += ret;
		}
		else
			token_i++;
		i++;
	}
	return (expander_unseparated(&sh->tokens, start, end));
}
