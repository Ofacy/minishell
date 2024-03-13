/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:00:53 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/12 15:18:02 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "vector.h"
#include "libft.h"
#include <stdio.h>

static size_t	lexer_txt_space(t_token *token, char *cmd)
{
	size_t	i;

	i = 0;
	token->type = UNQUOTED;
	while (cmd[i] && cmd[i] != ' ' && ft_strchr(SPECIAL_CHAR, cmd[i]) == NULL)
		i++;
	token->txt = cmd;
	token->txt_size = i;
	token->is_separated = (cmd[i] == ' '
			|| ft_strchr(SPECIAL_NO_QUOTE, cmd[i]) != NULL);
	return (i);
}

static size_t	lexer_txt(t_token *token, char *cmd, char quote)
{
	size_t	i;

	i = 0;
	token->type = quote;
	while (cmd[i] && cmd[i] != quote)
		i++;
	if (cmd[i] == quote)
	{
		token->txt = cmd;
		token->txt_size = i;
		token->is_separated = cmd[i + 1] == ' '
			|| ft_strchr(SPECIAL_NO_QUOTE, cmd[i + 1]) != NULL;
		return (i + 1);
	}
	return (i);
}

static size_t	lexer_special(t_token *token, char *cmd)
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

static size_t	lexer_char(t_token *token, char *cmd)
{
	if (ft_strchr(SPECIAL_CHAR, cmd[0]) != NULL)
	{
		return (lexer_special(token, cmd));
	}
	else if (cmd[0] == ' ')
		return (1);
	return (lexer_txt_space(token, cmd));
}

int	lexer(t_vector *lex, char *cmd)
{
	t_token	current;

	if (!cmd)
		return (1);
	vector_init(lex, sizeof(t_token));
	while (*cmd)
	{
		current.type = UNSET;
		current.is_file = false;
		current.txt = NULL;
		current.txt_size = 0;
		current.is_separated = true;
		current.is_txt_heap = false;
		cmd += lexer_char(&current, cmd);
		current.old_type = current.type;
		if (current.type == UNSET)
			continue ;
		if (vector_add(lex, &current) != 0)
		{
			vector_free(lex);
			return (1);
		}
	}
	return (0);
}
