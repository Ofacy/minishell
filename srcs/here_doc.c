/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:41:37 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 21:20:13 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int	here_doc_line(t_mshell *sh, int file, char *line)
{
	write(file, line, ft_strlen(line));
	write(file, "\n", 1);
	if (vector_addstr(&sh->history_entry, line) != 0)
		return (free(line), 2);
	free(line);
	return (0);
}

int	exec_set_heredoc(t_execute *exec, t_mshell *sh, size_t i)
{
	t_fd	file;
	char	*line;

	file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		exec->in = -1;
		error(".heredoc");
		return (1);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, ((t_token *)sh->tokens.tab)[i + 1].txt,
		ft_strlen(((t_token *)sh->tokens.tab)[i + 1].txt)))
	{
		if (here_doc_line(sh, file, line))
			return (2);
		line = readline("> ");
	}
	close_fd(&file);
	exec->in = open(".heredoc", O_RDONLY);
	if (exec->in == -1)
		error(".heredoc");
	unlink(".heredoc");
	return (0);
}
