/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expender_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:03:33 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/19 16:42:11 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

int	expender_token_addi(t_vector *tokens, t_token *token,
	char **split, size_t *i)
{
	size_t	j;
	t_token	new_token;

	j = 0;
	while (split[j])
	{
		if (set_token(&new_token, token, split[j]) != 0)
			return (1);
		if (vector_addi(tokens, (void *)&new_token, *i + j) != 0)
			return (1);
		j++;
	}
	if (j != 0)
		*i += j - 1;
	((t_token *)tokens->tab)[*i].is_separated = token->is_separated;
	return (0);
}

int	expender_token_split(t_vector *tokens, size_t *i)
{
	t_token	token;
	char	**split_str;

	token = ((t_token *)tokens->tab)[*i];
	vector_remove(tokens, *i);
	if (*i != 0 && token.txt[0] == ' ')
		((t_token *)tokens->tab)[*i - 1].is_separated = true;
	replace_white_space(token.txt);
	split_str = ft_split(token.txt, ' ');
	if (!split_str || expender_token_addi(tokens, &token, split_str, i) != 0)
	{
		ft_freesplit(split_str);
		free_token(&token);
		return (1);
	}
	((t_token *)tokens->tab)[*i].is_separated = token.is_separated;
	ft_freesplit(split_str);
	free_token(&token);
	return (0);
}


