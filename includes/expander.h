/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:30:58 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/26 16:18:25 by bwisniew         ###   ########.fr       */
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
size_t	expanded_len(t_mshell *sh, size_t token_i);
bool	need_expand_str(t_token *token, size_t str_i);
size_t	skip_envname(char *str);

#endif
