/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:28:50 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/11 17:52:59 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

size_t	skip_envname(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] && ft_strchr(ENV_NAME_CHAR, str[i]))
		i++;
	return (i);
}

size_t	expand_str(t_token *token, char *exp_txt, t_mshell *sh)
{
	size_t	exp_i;
	size_t	txt_i;
	t_env	*env_var;

	exp_i = 0;
	txt_i = 0;
	while (txt_i < token->txt_size)
	{
		if (need_expand_str(token, txt_i))
		{
			env_var = env_get(sh, token->txt + txt_i + 1, false);
			if (env_var)
			{
				ft_strlcpy(exp_txt + exp_i,
					env_var->value, env_var->value_size + 1);
				exp_i += env_var->value_size;
			}
			txt_i += skip_envname(token->txt + txt_i + 1);
		}
		else
			exp_txt[exp_i++] = token->txt[txt_i];
		txt_i++;
	}
	exp_txt[exp_i] = '\0';
	return (exp_i);
}

int	token_expand(t_token *token, t_mshell *sh, size_t exp_len)
{
	char	*exp_txt;

	exp_txt = malloc(sizeof(char) * (exp_len + 1));
	if (!exp_txt)
		return (1);
	expand_str(token, exp_txt, sh);
	if (token->is_txt_heap)
		free(token->txt);
	token->txt = exp_txt;
	token->txt_size = ft_strlen(exp_txt);
	token->is_txt_heap = true;
	return (0);
}

int	tokens_expand(t_mshell *sh, size_t token_i)
{
	t_token	*token;
	int		nb_exp;

	token = &((t_token *)(sh->tokens.tab))[token_i];
	nb_exp = 1;
	token_expand(token, sh,
		expanded_len(sh, &((t_token *)sh->tokens.tab)[token_i]));
	if (token->type == UNQUOTED)
	{
		nb_exp = expander_split(sh, token_i);
		if (nb_exp < 0)
			return (-1);
	}
	return (nb_exp);
}
