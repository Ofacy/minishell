/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:44:47 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 19:11:39 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include <stddef.h>
# include "vector.h"

# define SPECIAL_CHAR "<>|'\""

typedef enum e_tokentype
{
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
}	t_token;

int	lexer(t_vector *lex, char *cmd);

#endif
