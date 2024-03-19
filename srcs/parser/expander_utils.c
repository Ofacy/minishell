/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:26:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/19 15:45:08 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

int	replace_env_var(char *token_str, char *exp_str, t_mshell *sh)
{
	t_env	*env_var;

	env_var = env_get(sh, token_str);
	if (!env_var)
		return (0);
	ft_strlcpy(exp_str, env_var->value, env_var->value_size + 1);
	return (env_var->value_size);
}

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
	t1->txt_size = str_len + str2_len + 1;
	t1->is_separated = t2->is_separated;
	free_token(t1);
	free_token(t2);
	t1->is_txt_heap = true;
	return (str);
}

int	expend_file_ambi(t_token *token, t_mshell *sh)
{
	size_t	char_i;
	t_env	*env_var;

	char_i = 0;
	while (char_i < token->txt_size)
	{
		if (token->txt[char_i] == '$' && token->type != SINGLE_QUOTED)
		{
			env_var = env_get(sh, token->txt + char_i + 1);
			if (!env_var)
			{
				char_i++;
				continue ;
			}
			else if (ft_strchr(env_var->value, ' ') != NULL)
			{
				custom_error(env_var->key, "ambiguous redirect");
				return (1);
			}
			char_i += env_var->key_size + 1;
		}
		char_i++;
	}
	return (0);
}

int	expend_file(t_mshell *sh, size_t i)
{
	size_t	i_cp;

	i_cp = i;
	i++;
	while (i < sh->tokens.len && ((t_token *)sh->tokens.tab)[i].is_file == 1)
	{
		if (expend_file_ambi(&((t_token *)sh->tokens.tab)[i], sh) != 0)
			return (1);
		i++;
	}
	if (expander(sh, i_cp + 1,
			expander_skip_arrow(&sh->tokens, i_cp, sh->tokens.len) + 1) < 0)
		return (1);
	return (0);
}
