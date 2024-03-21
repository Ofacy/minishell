/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:23:22 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/21 18:55:39 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

bool	is_type_arrow(t_tokentype type)
{
	return (type == HEREDOC || type == REDIRECT_APPEND
		|| type == REDIRECT_INPUT || type == REDIRECT_OUTPUT);
}

bool	is_unclosed_quotes(t_token *token)
{
	return (token->txt == NULL && (token->type == DOUBLE_QUOTED
			|| token->type == SINGLE_QUOTED));
}

bool	is_special(t_tokentype type)
{
	return (is_type_arrow(type) || type == PIPE);
}

char	*get_token_str(t_tokentype type)
{
	if (type == REDIRECT_APPEND)
		return (">>");
	else if (type == REDIRECT_OUTPUT)
		return (">");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == REDIRECT_INPUT)
		return ("<");
	else if (type == DOUBLE_QUOTED)
		return ("\"");
	else if (type == SINGLE_QUOTED)
		return ("'");
	else if (type == NEWLINE)
		return ("newline");
	return ("UNKNOWN");
}

void	free_token(t_token *token)
{
	if (token->is_txt_heap)
		free(token->txt);
	token->type = UNSET;
	token->txt = NULL;
}
