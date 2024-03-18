/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:18:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/18 10:53:03 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	exec_init(t_execute *exec, t_mshell *sh)
{
	vector_init(&exec->args, sizeof(char *));
	exec->cmd = NULL;
	exec->has_pipe = false;
	exec->builtin = NULL;
	exec->in = exec->nextin;
	exec->nextin = dup(STDIN_FILENO);
	exec->out = dup(sh->stdout);
}

int	exec_set_cmd(t_execute *exec, t_mshell *sh)
{
	exec->builtin = get_builtin(sh, ((char **)exec->args.tab)[0]);
	if (exec->builtin)
		return (0);
	exec->cmd = get_openable_path(((char **)exec->args.tab)[0], X_OK, sh);
	if (!exec->cmd)
	{
		if (errno == ENOENT)
			custom_error(((char **)exec->args.tab)[0], "command not found");
		else
			error(((char **)exec->args.tab)[0]);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_execute *exec, t_mshell *sh, char **envp)
{
	close_fd(&sh->stdout);
	if (dup2(exec->out, STDOUT_FILENO) < 0)
	{
		error("dup2 out");
		close_exec(exec);
	}
	if (exec->out != STDOUT_FILENO)
		close_fd(&exec->out);
	if (dup2(exec->in, STDIN_FILENO) < 0)
	{
		error("dup2 in");
		close_exec(exec);
	}
	if (exec->in != STDIN_FILENO)
		close_fd(&exec->in);
	if (exec->nextin != STDIN_FILENO)
		close_fd(&exec->nextin);
	choose_fork_exec(sh, exec, envp);
}

pid_t	exec_txt(t_execute *exec, t_mshell *sh)
{
	char		*null;
	pid_t		pid;

	if (exec->args.len == 0)
		return (-4);
	null = NULL;
	if (vector_add(&exec->args, &null) != 0)
		return (-1);
	if (exec_set_cmd(exec, sh))
		return (-1);
	if (exec->builtin && !exec->has_pipe)
	{
		if (set_env_return(sh, exec->builtin->func(sh, exec)) != 0)
		{
			error("set_env_return");
			return (-2);
		}
		return (-4);
	}
	pid = exec_fork(exec, sh);
	free(exec->cmd);
	return (pid);
}

pid_t	exec(t_mshell *sh)
{
	size_t		i;
	pid_t		pid;
	t_execute	exec;

	pid = -1;
	exec.nextin = dup(STDIN_FILENO);
	exec_init(&exec, sh);
	i = 0;
	while (i < sh->tokens.len)
	{
		if (exec_prepare(sh, &exec, &i) != 0)
			return (close_exec(&exec), vector_free(&exec.args), -1);
		if (exec.in > 0 && exec.out > 0)
		{
			pid = exec_txt(&exec, sh);
			if (pid < 0)
				return (close_exec(&exec), vector_free(&exec.args), -1);
		}
		else
			pid = -2;
		vector_free(&exec.args);
		close_fd(&exec.in);
		close_fd(&exec.out);
		exec_init(&exec, sh);
		i++;
	}
	close_exec(&exec);
	return (pid);
}
