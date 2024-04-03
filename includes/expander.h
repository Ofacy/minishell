/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:30:58 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/03 14:21:20 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include <stddef.h>

typedef struct s_expand_size
{
	size_t	exp_size;
	size_t	str_size;
	int		error;
}	t_expand_size;

int		tokens_expand(t_mshell *sh, size_t token_i);
bool	need_expand_str(t_token *token, size_t str_i);
size_t	expanded_len(t_mshell *sh, t_token *token);
size_t	skip_envname(char *str);
size_t	expander_split(t_mshell *sh, size_t token_i);
int		expander_unseparated(t_vector *lex, size_t i, size_t n);
int		token_expand(t_token *token, t_mshell *sh, size_t exp_len);
size_t	expander_skip_file(t_vector *lex, size_t i, size_t n);

#endif
