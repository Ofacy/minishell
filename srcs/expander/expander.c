/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:13:27 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/26 17:00:38 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>

static bool	need_expand(t_token token)
{
	return (token.type == UNQUOTED || token.type == DOUBLE_QUOTED);
}

int	expander(t_mshell *sh, size_t start, size_t end)
{
	size_t	i;
	t_token	token;
	int		ret;

	i = start;
	printf("start = %lu, end = %lu\n", start, end);
	while (i < end)
	{
		token = ((t_token *)sh->tokens.tab)[i];
		printf("tokens_len = %lu, token_type = %u, i = %lu\n",sh->tokens.len, token.type, i);
		if (need_expand(token))
		{
			ret = tokens_expand(sh, i);
			if (ret < 0)
				return (1);
			i += ret;
		}
		else
			i++;
	}
	printf("\n\n=========================================\n\n");
	i = 0;
	while (i < sh->tokens.len)
	{
		printf("i = %-5lu; old_type = %d, type = %d, sparated = %d, heap = %d", i, ((t_token *)sh->tokens.tab)[i].old_type, ((t_token *)sh->tokens.tab)[i].type, ((t_token *)sh->tokens.tab)[i].is_separated, ((t_token *)sh->tokens.tab)[i].is_txt_heap);
		if (((t_token *)sh->tokens.tab)[i].txt != NULL)
			printf(" is_file = %d txt = '%s', size = %lu", ((t_token *)sh->tokens.tab)[i].is_file, ((t_token *)sh->tokens.tab)[i].txt, ((t_token *)sh->tokens.tab)[i].txt_size);
		printf("\n\n");
		i++;
	}
	return (0);
}
