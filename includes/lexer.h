/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:44:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 22:25:56 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stddef.h>
# include "vector.h"

# define SPECIAL_CHAR "<>|'\""
# define SPECIAL_NO_QUOTE "<>|"

typedef enum e_tokentype
{
	UNSET,
	UNQUOTED,
	DOUBLE_QUOTED = '"',
	SINGLE_QUOTED = '\'',
	PIPE = '|',
	REDIRECT_INPUT = '<',
	REDIRECT_OUTPUT = '>',
	HEREDOC,
	REDIRECT_APPEND
}	t_tokentype;

typedef struct s_token
{
	t_tokentype	type;
	char		*txt;
	size_t		txt_size;
	bool		is_separated;
}	t_token;

int	lexer(t_vector *lex, char *cmd);

#endif
