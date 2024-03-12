/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:44:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/12 15:16:25 by lcottet          ###   ########.fr       */
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
	NEWLINE = '\n',
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
	t_tokentype	old_type;
	char		*txt;
	size_t		txt_size;
	bool		is_separated;
	bool		is_txt_heap;
	bool		is_file;
}	t_token;

int	lexer(t_vector *lex, char *cmd);

#endif
