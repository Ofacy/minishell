/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:31:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/10 01:27:19 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	free_arg(char **arg)
{
	if (*arg)
		free(*arg);
}

void	exec_fail(t_execute *exec, t_mshell *sh, char **envp)
{
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	ft_freesplit(envp);
	free(exec->cmd);
	vector_foreach(&exec->args, (void (*)(void *))free_arg);
	vector_free(&exec->args);
	free_mshell(sh);
}

int	exec_prepare(t_mshell *sh, t_execute *exec, size_t *i)
{
	char	*dup;

	while ((*i) < sh->tokens.len)
	{
		if (is_special(((t_token *)sh->tokens.tab)[*i].type))
		{
			if (exec->in > 0 && exec->out > 0 && exec_fd(exec, sh, *i) == 2)
				return (2);
			if (((t_token *)sh->tokens.tab)[*i].type != PIPE)
				(*i)++;
			else
				break ;
		}
		else
		{
			dup = ft_strdup(((t_token *)sh->tokens.tab)[*i].txt);
			if (!dup)
				return (1);
			if (vector_add(&exec->args, &dup) != 0)
				return (1);
		}
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
	free_mshell(sh);
	if (execve(exec->cmd, (char **)exec->args.tab, envp) == -1)
	{
		error(exec->cmd);
		exec_fail(exec, sh, envp);
		exit(127);
	}
}
