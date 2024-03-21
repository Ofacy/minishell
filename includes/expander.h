/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:30:58 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 19:51:15 by bwisniew         ###   ########.fr       */
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

int	tokens_expand(t_mshell *sh, size_t token_i);

#endif
