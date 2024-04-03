/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:04 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/03 14:23:26 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>

int	exec_set_heredoc(t_execute *exec, t_mshell *sh, size_t i);

int	exec_set_pipe(t_execute *exec)
{
	t_fd	fd[2];

	exec->has_pipe = true;
	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd) == -1)
	{
		error("pipe");
		return (1);
	}
	close_fd(&exec->nextin);
	if (!exec->has_redirect)
	{
		close_fd(&exec->out);
		exec->out = fd[1];
	}
	else
		close(fd[1]);
	exec->nextin = fd[0];
	return (0);
}

int	exec_set_output(t_execute *exec, t_mshell *sh, size_t i)
{
	exec->has_redirect = true;
	close_fd(&exec->out);
	if (expand_file(sh, i))
		return (1);
	exec->out = open(((t_token *)sh->tokens.tab)[i + 1].txt,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->out == -1)
	{
		error(((t_token *)sh->tokens.tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_set_input(t_execute *exec, t_mshell *sh, size_t i)
{
	close_fd(&exec->in);
	if (expand_file(sh, i))
		return (1);
	exec->in = open(((t_token *)sh->tokens.tab)[i + 1].txt, O_RDONLY);
	if (exec->in == -1)
	{
		error(((t_token *)sh->tokens.tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_set_append(t_execute *exec, t_mshell *sh, size_t i)
{
	exec->has_redirect = true;
	close_fd(&exec->out);
	if (expand_file(sh, i))
		return (1);
	exec->out = open(((t_token *)sh->tokens.tab)[i + 1].txt,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->out == -1)
	{
		error(((t_token *)sh->tokens.tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_fd(t_execute *exec, t_mshell *sh, size_t i)
{
	if (((t_token *)sh->tokens.tab)[i].type == PIPE)
		return (exec_set_pipe(exec));
	else if (((t_token *)sh->tokens.tab)[i].type == REDIRECT_INPUT)
		return (exec_set_input(exec, sh, i));
	else if (((t_token *)sh->tokens.tab)[i].type == REDIRECT_OUTPUT)
		return (exec_set_output(exec, sh, i));
	else if (((t_token *)sh->tokens.tab)[i].type == HEREDOC)
		return (exec_set_heredoc(exec, sh, i));
	else if (((t_token *)sh->tokens.tab)[i].type == REDIRECT_APPEND)
		return (exec_set_append(exec, sh, i));
	return (0);
}
