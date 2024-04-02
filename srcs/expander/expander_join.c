/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 18:51:26 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/02 19:17:30 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"
#include <stdlib.h>

size_t	expander_skip_arrow(t_vector *lex, size_t i, size_t n)
{
	if (i < n && is_type_arrow(((t_token *)lex->tab)[i].type))
	{
		((t_token *)lex->tab)[i + 1].is_file = true;
		i ++;
		while (i < n && !((t_token *)lex->tab)[i].is_separated
			&& !is_special(((t_token *)lex->tab)[i].type))
		{
			((t_token *)lex->tab)[i].is_file = true;
			i++;
		}
		if (i < n)
			((t_token *)lex->tab)[i].is_file = true;
	}
	return (i);
}

char	*expander_join(t_token *t1, t_token *t2)
{
	char	*str;
	size_t	str_len;
	size_t	str2_len;

	str_len = t1->txt_size;
	str2_len = t2->txt_size;
	str = malloc((str_len + str2_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, t1->txt, str_len + 1);
	ft_strlcat(str, t2->txt, str_len + str2_len + 1);
	free_token(t1);
	t1->txt_size = str_len + str2_len;
	t1->is_separated = t2->is_separated;
	free_token(t2);
	t1->is_txt_heap = true;
	return (str);
}

int	expander_unseparated(t_vector *lex, size_t i, size_t n)
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
