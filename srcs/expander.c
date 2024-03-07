/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 22:26:27 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 23:20:48 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

size_t env_var_size(char *str, size_t size)
{
	size_t	var_size;
	char	*new_str;
	
	var_size = 0;
	while (var_size < size && ft_strchr(ENV_NAME_CHAR, str[var_size]) != NULL)
		var_size++;
	return (var_size);
}

size_t	expended_len(t_token *token, t_vector *env)
{
	size_t	i;
	size_t	str_len;
	size_t	var_len;

	i = 0;
	str_len = 0;
	while (i < token->txt_size)
	{
		if (token->txt[i] == '$')
		{
			var_len = env_var_size(token->txt[i + 1], token->txt_size - i);
			str_len += ft_strlen(env_get(env, token->txt[i + 1], var_len));
			i += var_len + 1;
		}
		else
			str_len++;
		i++;
	}
	return (str_len)
}

int

int	expander(t_vector *lex, t_vector *env)
{
	size_t	i;

	i = 0;
	while (i < lex->len)
	{
		if(((t_token *)lex->tab)[i].txt != NULL)
			env_var_replace(((t_token *)lex->tab)[i].txt, env);
	}
	if (((t_token *)lex->tab)[i].type == DOUBLE_QUOTED
		|| ((t_token *)lex->tab)[i].type == SINGLE_QUOTED
		&& !((t_token *)lex->tab)[i].txt)
	{
		dprintf(STDERR_FILENO, "Error: Unmatched quote\n");
	};
		
	return (0);
}