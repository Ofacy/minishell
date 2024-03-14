/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:31:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/14 19:31:34 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	exec_fail(t_execute *exec, t_mshell *sh, char **envp)
{
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	ft_freesplit(envp);
	free(exec->cmd);
	vector_free(&exec->args);
	free_mshell(sh);
}

int	exec_prepare(t_mshell *sh, t_execute *exec, size_t *i)
{
	while ((*i) < sh->tokens.len)
	{
		if (is_special(((t_token *)sh->tokens.tab)[*i].type))
		{
			if (exec->in > 0 && exec->out > 0)
				exec_fd(exec, sh, *i);
			if (((t_token *)sh->tokens.tab)[*i].type != PIPE)
				(*i)++;
			else
				break ;
		}
		else if (vector_add(&exec->args,
				&((t_token *)sh->tokens.tab)[*i].txt) != 0)
			return (1);
		(*i)++;
	}
	return (0);
}

void	choose_fork_exec(t_mshell *sh, t_execute *exec, char **envp)
{
	int	ret;

	if (exec->builtin)
	{
		ret = exec->builtin->func(sh, exec);
		exec_fail(exec, sh, envp);
		exit(ret);
	}
	if (execve(exec->cmd, (char **)exec->args.tab, envp) == -1)
	{
		exec_fail(exec, sh, envp);
		error(exec->cmd);
		exit(127);
	}
}
