/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:18:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 22:31:42 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "libft.h"

int	exec_fd(t_execute *exec, t_mshell sh, size_t i);

void	exec_init(t_execute *exec, t_mshell *sh)
{
	exec->args = NULL;
	exec->cmd = NULL;
	if (exec->in != STDIN_FILENO)
		close_fd(&exec->in);
	exec->in = exec->nextin;
	if (exec->nextin != STDIN_FILENO)
		close_fd(&exec->nextin);
	exec->nextin = STDIN_FILENO;
	if (exec->out != STDOUT_FILENO && exec->out != sh->stdout)
		close_fd(&exec->out);
	exec->out = sh->stdout;
}

int	exec_set_cmd(t_execute *exec, char **args, t_mshell *sh)
{
	if (!args)
		return (1);
	exec->args = args;
	exec->cmd = get_openable_path(args[0], X_OK, &sh->env);
	if (!exec->cmd)
	{
		error(args[0]);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_execute *exec, t_mshell *sh, char **envp)
{
	if (dup2(exec->out, STDOUT_FILENO) < 0)
	{
		error("dup2 out");
		close_fd(&sh->stdout);
		close_exec(exec);
	}
	if (exec->out != STDOUT_FILENO)
		close_fd(&exec->out);
	if (dup2(exec->in, STDIN_FILENO) < 0)
	{
		error("dup2 in");
		close_fd(&sh->stdout);
		close_exec(exec);
	}
	if (exec->in != STDIN_FILENO)
		close_fd(&exec->in);
	if (exec->nextin != STDIN_FILENO)
		close_fd(&exec->nextin);
	if (execve(exec->cmd, exec->args, envp) == -1)
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		error(exec->cmd);
		ft_freesplit(envp);
		free(exec->cmd);
		free(exec->args);
		free_mshell(sh);
		exit(127);
	}
}

pid_t	exec_txt(t_execute *exec, t_mshell *sh, size_t i)
{
	t_vector	args;
	size_t		argsi;
	char		*null;
	pid_t		pid;

	vector_init(&args, sizeof(char *));
	argsi = 0;
	while (i + argsi < sh->tokens.len
		&& !is_special(((t_token *)sh->tokens.tab)[i + argsi].type))
	{
		if (vector_add(&args, &((t_token *)sh->tokens.tab)[i + argsi].txt)
			!= 0)
			return (-1);
		argsi++;
	}
	null = NULL;
	if (vector_add(&args, &null) != 0)
		return (-1);
	if (exec_set_cmd(exec, (char **)args.tab, sh))
		return (vector_free(&args), -1);
	pid = exec_fork(exec, sh);
	free(exec->cmd);
	vector_free(&args);
	return (pid);
}

int	exec(t_mshell *sh)
{
	size_t		i;
	pid_t		pid;
	t_execute	exec;

	i = 0;
	exec.in = STDIN_FILENO;
	exec.nextin = STDIN_FILENO;
	exec.out = sh->stdout;
	pid = 0;
	exec_init(&exec, sh);
	while (i < sh->tokens.len)
	{
		if (is_special(((t_token *)sh->tokens.tab)[i].type))
		{
			exec_fd(&exec, *sh, i);
			if (((t_token *)sh->tokens.tab)[i].type != PIPE)
				i++;
		}
		else
		{
			pid = exec_txt(&exec, sh, i);
			if (pid < 0)
				return (1);
			exec_init(&exec, sh);
		}
		i++;
	}
	return (pid);
}
