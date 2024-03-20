/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:41:37 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/20 16:28:14 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int	here_doc_line(int file, char *line)
{
	if (write(file, line, ft_strlen(line)) == -1)
		return (free(line), 1);
	if (write(file, "\n", 1) == -1)
		return (free(line), 1);
	free(line);
	return (0);
}

char	*here_doc_signal(t_token *line, t_mshell *sh, int *err)
{
	if (g_signal == SIGINT)
	{
		*err = 2;
		free(line->txt);
		if (dup2(sh->stdin, STDIN_FILENO) == -1)
			*err = 1;
		return (NULL);
	}
	return (line->txt);
}

char	*here_doc_getline(t_mshell *sh, size_t i, t_fd fd, int *err)
{
	t_token	line;
	char	*tmp;

	line.txt = readline(PROMPT_HEREDOC);
	if (g_signal != -1)
		return (here_doc_signal(&line, sh, err));
	else if (!line.txt)
	{
		custom_error("warning", "unexpected EOF in here-document");
		return (NULL);
	}
	tmp = ft_strdup(line.txt);
	line.txt_size = ft_strlen(line.txt);
	line.is_txt_heap = true;
	line.type = ((t_token *)sh->tokens.tab)[i].old_type;
	if (((t_token *)sh->tokens.tab)[i].old_type == UNQUOTED)
	{
		if (get_expended_str(&line, sh) < 0)
		{
			free_token(&line);
			return (NULL);
		}
	}
	*err = here_doc_line(fd, line.txt);
	return (tmp);
}

int	get_final_heredoc_fd(t_execute *exec, t_fd old, int err)
{
	close_fd(&old);
	if (err)
	{
		unlink(".heredoc");
		exec->in = -1;
		return (err);
	}
	exec->in = open(".heredoc", O_RDONLY);
	if (exec->in == -1)
		error(".heredoc");
	return (unlink(".heredoc"));
}

int	exec_set_heredoc(t_execute *exec, t_mshell *sh, size_t i)
{
	t_fd	file;
	char	*line;
	int		err;

	close_fd(&exec->in);
	err = 0;
	file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		exec->in = -1;
		error(".heredoc");
		return (1);
	}
	reset_signal();
	signal(SIGINT, signal_heredoc);
	line = here_doc_getline(sh, i + 1, file, &err);
	while (line && ft_strncmp(line, ((t_token *)sh->tokens.tab)[i + 1].txt,
		((t_token *)sh->tokens.tab)[i + 1].txt_size) && g_signal != SIGINT)
	{
		free(line);
		line = here_doc_getline(sh, i + 1, file, &err);
	}
	free(line);
	return (get_final_heredoc_fd(exec, file, err));
}
