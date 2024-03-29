/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:28:50 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/26 16:19:33 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

size_t	skip_envname(char *str)
{
	size_t	i;

	i = 0;
	while (ft_strchr(ENV_NAME_CHAR, str[i]))
		i++;
	return (i);
}

int	token_expand(t_token *token, t_mshell *sh, size_t exp_len)
{
	size_t	exp_i;
	size_t	txt_i;
	t_env	*env_var;
	char	*exp_txt;

	exp_txt = malloc(sizeof(char) * (exp_len + 1));
	if (!exp_txt)
		return (1);
	exp_i = 0;
	txt_i = 0;
	while (txt_i < token->txt_size)
	{
		if (need_expand_str(token, txt_i))
		{
			env_var = env_get(sh, token->txt + txt_i, false);
			if (env_var)
			{
				ft_strlcpy(token->txt + txt_i,
					env_var->value, env_var->value_size);
				exp_i += env_var->value_size;
				txt_i += env_var->key_size + 1;
			}
			else
				txt_i += skip_envname(token->txt + txt_i + 1) + 1;
		}
		else
			exp_txt[exp_i++] = token->txt[txt_i++];
	}
	exp_txt[exp_i] = '\0';
	if (token->is_txt_heap)
		free(token->txt);
	token->txt = exp_txt;
	token->txt_size = ft_strlen(exp_txt);
	token->is_txt_heap = true;
	return (0);
}

int	tokens_expand(t_mshell *sh, size_t token_i)
{
	// t_token	*token;
	// size_t	exp_size;

	// token = &sh->tokens.tab[token_i];
	// exp_size = expanded_len(sh, token_i);

	printf("expanded len = %lu\n", expanded_len(sh, token_i));
	return (1);
}
