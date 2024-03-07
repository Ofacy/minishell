/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:00:53 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 20:08:56 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "libft.h"
#include <stdio.h>

size_t	lexer_txt(t_token *token, char *cmd, char quote)
{
	size_t	i;

	i = 0;
	if (quote == ' ')
		token->type = UNQUOTED;
	token->type = quote;
	while (cmd[i] && cmd[i] != quote)
		i++;
	if (cmd[i] == quote)
	{
		token->txt = cmd;
		token->txt_size = i;
		return (i + 1);
	}
	return (i);
}

size_t	lexer_special(t_token *token, char *cmd)
{
	if (*(cmd + 1) == *cmd && *cmd == '<')
	{
		token->type = HEREDOC;
		return (2);
	}
	else if (*(cmd + 1) == *cmd && *cmd == '>')
	{
		token->type = REDIRECT_APPEND;
		return (2);
	}
	else if (*cmd == '"' || *cmd == '\'')
		return (lexer_txt(token, cmd + 1, *cmd) + 1);
	else
		token->type = *cmd;
	return (1);
}

size_t	lexer_char(t_token *token, char *cmd)
{
	if (ft_strchr(SPECIAL_CHAR, cmd[0]) != NULL)
	{
		return (lexer_special(token, cmd));
	}
	else if (cmd[0] == ' ')
		return (1);
	return (lexer_txt(token, cmd, ' '));
}

int	lexer(t_vector *lex, char *cmd)
{
	t_token	current;

	vector_init(lex, sizeof(t_token));
	while(*cmd)
	{
		current.txt = NULL;
		current.txt_size = 0;
		cmd += lexer_char(&current, cmd);
		if (vector_add(lex, &current) != 0)
		{
			vector_free(lex);
			return (1);
		}
	}
	return (0);
}
