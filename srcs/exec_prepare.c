/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prepare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:31:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/11 18:28:27 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_prepare(t_mshell *sh, t_execute *exec, size_t *i)
{
	while ((*i) < sh->tokens.len)
	{
		if (is_special(((t_token *)sh->tokens.tab)[*i].type))
		{
			exec_fd(exec, *sh, *i);
			if (((t_token *)sh->tokens.tab)[*i].type != PIPE)
				(*i)++;
			else
				break;
		}
		else if (vector_add(&exec->args,
			&((t_token *)sh->tokens.tab)[*i].txt) != 0)
			return (close_exec(exec), 1);
		(*i)++;
	}
	return (0);
}
