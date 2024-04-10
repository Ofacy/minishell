/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:18:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/10 01:24:50 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	exec_init(t_execute *exec, t_mshell *sh, bool next)
{
	if (next)
	{
		vector_foreach(&exec->args, (void (*)(void *))free_arg);
		vector_free(&exec->args);
		close_fd(&exec->in);
		close_fd(&exec->out);
	}
	vector_init(&exec->args, sizeof(char *));
	exec->has_redirect = false;
	exec->cmd = NULL;
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
		{
			custom_error(((char **)exec->args.tab)[0], "command not found");
			set_env_return(sh, 127);
		}
		else
		{
			error(((char **)exec->args.tab)[0]);
			set_env_return(sh, 126);
		}
		return (1);
	}
	return (0);
}

void	exec_cmd(t_execute *exec, t_mshell *sh, char **envp)
{
	close_fd(&sh->stdout);
	close_fd(&sh->stdin);
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
	char	*null;
	pid_t	pid;
	int		filetype;

	if (exec->args.len == 0)
		return (-4);
	null = NULL;
	if (vector_add(&exec->args, &null) != 0)
		return (-1);
	if (exec_set_cmd(exec, sh))
		return (-4);
	if (exec->builtin && !exec->has_pipe)
	{
		if (exec_builtins(exec, sh) != 0)
			return (-3);
		return (-4);
	}
	filetype = regular_file_check(sh, exec->cmd);
	if (filetype == -1)
		return (free(exec->cmd), -1);
	else if (!filetype)
		return (free(exec->cmd), set_env_return(sh, 126), -4);
	pid = exec_fork(exec, sh);
	free(exec->cmd);
	return (pid);
}

pid_t	exec(t_mshell *sh)
{
	size_t		i;
	pid_t		pid;
	t_execute	exec;

	pid = -4;
	exec.nextin = dup(sh->stdin);
	exec.has_pipe = false;
	exec_init(&exec, sh, false);
	i = 0;
	while (i < sh->tokens.len)
	{
		if (exec_prepare(sh, &exec, &i) != 0)
			return (close_exec(&exec), vector_free(&exec.args), -1);
		pid = -2;
		if (exec.in > 0 && exec.out > 0)
		{
			pid = exec_txt(&exec, sh);
			if (pid < 0 && pid == -1)
				return (close_exec(&exec), vector_free(&exec.args), pid);
		}
		exec_init(&exec, sh, true);
		i++;
	}
	close_exec(&exec);
	return (pid);
}
