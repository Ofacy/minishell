/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:21:31 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 15:24:31 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "ft_printf.h"

static t_tokentype	check_special(t_vector *tokens)
{
	size_t	i;

	i = 0;
	if (tokens->len == 0)
		return (0);
	if (((t_token *)tokens->tab)[i].type == PIPE)
		return (PIPE);
	while (i < tokens->len - 1)
	{
		if (is_type_arrow(((t_token *)tokens->tab)[i].type))
			if (is_type_arrow(((t_token *)tokens->tab)[i + 1].type))
				return (((t_token *)tokens->tab)[i + 1].type);
		i++;
	}
	if (is_special(((t_token *)tokens->tab)[i].type))
		return (NEWLINE);
	return (0);
}

static t_tokentype	check_unclosed_quotes(t_vector *tokens)
{
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		if (is_unclosed_quotes(((t_token *)tokens->tab) + i))
			return (((t_token *)tokens->tab)[i].type);
		i++;
	}
	return (0);
}

int	check_syntax(t_vector *tokens)
{
	t_tokentype	type;

	type = check_special(tokens);
	if (type)
	{
		ft_printf("minishell: syntax error near unexpected token `%s`\n",
			get_token_str(type));
		return (2);
	}
	type = check_unclosed_quotes(tokens);
	if (type)
	{
		ft_printf("minishell: syntax error unclosed quotes `%s`\n",
			get_token_str(type));
		return (2);
	}
	return (0);
}
