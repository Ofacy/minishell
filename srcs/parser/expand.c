/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 17:17:35 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 18:25:15 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

bool	should_hide_dollar(t_token *token, size_t i)
{
	return (ft_strchr("'\"", token->txt[i + 1]) != NULL
		&& token->type == UNQUOTED);
}

int	skip_env_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_strchr(ENV_NAME_CHAR, str[i]) != NULL)
		i++;
	return (i);
}

void	expend_str(t_token *token, t_mshell *sh, size_t exp_len, char *exp_str)
{
	size_t	i;
	size_t	exp_i;
	size_t	v_size;

	exp_i = 0;
	i = 0;
	while (exp_i < exp_len)
	{
		if (token->txt[i] == '$' && token->type != SINGLE_QUOTED)
		{
			exp_i += replace_env_var(token->txt + i + 1, exp_str + exp_i, sh);
			v_size = skip_env_name(token->txt + i + 1);
			if (token->txt[i + v_size + 1] == '?')
				i++;
			else if (v_size == 0)
				exp_str[exp_i++] = '$';
			i += v_size;
		}
		else
			exp_str[exp_i++] = token->txt[i];
		i++;
	}
	exp_str[exp_i] = '\0';
}

int	get_expended_str(t_token *token, t_mshell *sh)
{
	char	*exp_str;
	size_t	exp_len;

	exp_len = expended_len(token, sh);
	exp_str = malloc(sizeof(char) * (exp_len + 1));
	if (!exp_str)
		return (1);
	expend_str(token, sh, exp_len, exp_str);
	free_token(token);
	token->txt = exp_str;
	token->txt_size = ft_strlen(exp_str);
	token->is_txt_heap = true;
	token->type = UNQUOTED;
	return (0);
}
