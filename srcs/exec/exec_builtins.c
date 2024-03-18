/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:12:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/18 16:22:00 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit_builtins(char *err, t_fd fds[2])
{
	error(err);
	close_fd(&fds[0]);
	close_fd(&fds[1]);
	return (1);
}

int	exec_prepare_builtins(t_execute *exec, t_fd og[2])
{
	og[1] = -1;
	og[0] = dup(STDIN_FILENO);
	if (og[0] < 0)
		return (exec_exit_builtins("dup", og));
	og[1] = dup(STDOUT_FILENO);
	if (og[1] < 0)
		return (exec_exit_builtins("dup", og));
	if (dup2(exec->in, STDIN_FILENO) < 0)
		return (exec_exit_builtins("dup2", og));
	if (dup2(exec->out, STDOUT_FILENO) < 0)
		return (exec_exit_builtins("dup2", og));
	return (0);
}

int	exec_builtins(t_execute *exec, t_mshell *sh)
{
	int		ret;
	t_fd	og[2];

	exec_prepare_builtins(exec, og);
	ret = exec->builtin->func(sh, exec);
	if (set_env_return(sh, ret) != 0)
		return (exec_exit_builtins("set_env_return", og));
	if (dup2(og[0], STDIN_FILENO) < 0)
		return (exec_exit_builtins("dup2", og));
	if (dup2(og[1], STDOUT_FILENO) < 0)
		return (exec_exit_builtins("dup2", og));
	close_fd(&og[0]);
	close_fd(&og[1]);
	return (0);
}