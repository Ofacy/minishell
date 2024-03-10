/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:29:04 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 21:30:20 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>

int	exec_set_heredoc(t_execute *exec, t_mshell *sh, size_t i);

int	exec_set_pipe(t_execute *exec)
{
	t_fd	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd) == -1)
	{
		error("pipe");
		return (1);
	}
	exec->out = fd[1];
	exec->nextin = fd[0];
	return (0);
}

int	exec_set_output(t_execute *exec, t_vector *tokens, size_t i)
{
	exec->out = open(((t_token *)tokens->tab)[i + 1].txt,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec->out == -1)
	{
		error(((t_token *)tokens->tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_set_input(t_execute *exec, t_vector *tokens, size_t i)
{
	exec->in = open(((t_token *)tokens->tab)[i + 1].txt, O_RDONLY);
	if (exec->in == -1)
	{
		error(((t_token *)tokens->tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_set_append(t_execute *exec, t_vector *tokens, size_t i)
{
	exec->out = open(((t_token *)tokens->tab)[i + 1].txt,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec->out == -1)
	{
		error(((t_token *)tokens->tab)[i + 1].txt);
		return (1);
	}
	return (0);
}

int	exec_fd(t_execute *exec, t_mshell sh, size_t i)
{
	if (((t_token *)sh.tokens.tab)[i].type == PIPE)
		return (exec_set_pipe(exec));
	else if (((t_token *)sh.tokens.tab)[i].type == REDIRECT_INPUT)
		return (exec_set_input(exec, &sh.tokens, i));
	else if (((t_token *)sh.tokens.tab)[i].type == REDIRECT_OUTPUT)
		return (exec_set_output(exec, &sh.tokens, i));
	else if (((t_token *)sh.tokens.tab)[i].type == HEREDOC)
		return (exec_set_heredoc(exec, &sh, i));
	else if (((t_token *)sh.tokens.tab)[i].type == REDIRECT_APPEND)
		return (exec_set_append(exec, &sh.tokens, i));
	return (0);
}
