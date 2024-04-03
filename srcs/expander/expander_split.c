/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:17:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 18:10:33 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "libft.h"

static void	replace_white_space(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			*str = ' ';
		str++;
	}
}

static int	set_token(t_token *new_token, t_token *token, char *txt)
{
	new_token->txt = ft_strdup(txt);
	if (!new_token->txt)
		return (1);
	new_token->txt_size = ft_strlen(new_token->txt);
	new_token->type = token->type;
	new_token->is_separated = true;
	new_token->is_txt_heap = true;
	new_token->is_file = token->is_file;
	new_token->old_type = token->old_type;
	return (0);
}

size_t	expander_split_add(t_mshell *sh, size_t token_i, char **split)
{
	size_t	i;
	t_token	new_token;
	t_token	*token;

	i = 0;
	while (split[i])
	{
		token = &((t_token *)(sh->tokens.tab))[token_i + i];
		if (set_token(&new_token, token, split[i]))
			return (-1);
		if (vector_addi(&sh->tokens, (void *)&new_token, token_i + i) != 0)
			return (-1);
		i++;
	}
	token = &((t_token *)(sh->tokens.tab))[token_i + i];
	if (i != 0)
		((t_token *)(sh->tokens.tab))[token_i + i - 1].is_separated
		= token->is_separated;
	return (i);
}

size_t	expander_split(t_mshell *sh, size_t token_i)
{
	t_token	*token;
	size_t	i;
	char	**split;

	token = &((t_token *)(sh->tokens.tab))[token_i];
	replace_white_space(token->txt);
	split = ft_split(token->txt, ' ');
	if (!split)
		return (-1);
	i = expander_split_add(sh, token_i, split);
	ft_freesplit(split);
	free_token(&((t_token *)sh->tokens.tab)[token_i + i]);
	vector_remove(&sh->tokens, token_i + i);
	return (i);
}
