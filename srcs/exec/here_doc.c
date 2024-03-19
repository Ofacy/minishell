/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:41:37 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/19 19:34:09 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	here_doc_line(int file, char *line)
{
	if (write(file, line, ft_strlen(line)) == -1)
		return (free(line), 1);
	if (write(file, "\n", 1) == -1)
		return (free(line), 1);
	free(line);
	return (0);
}

char	*here_doc_getline(t_mshell *sh, size_t i, t_fd fd, int *err)
{
	t_token	line;
	char	*tmp;

	line.txt = readline(PROMPT_HEREDOC);
	if (!line.txt)
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
	printf("txt = %s\n", line.txt);
	*err = here_doc_line(fd, line.txt);
	return (tmp);
}

int	get_final_heredoc_fd(t_execute *exec, t_fd old)
{
	close_fd(&old);
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

	exec->has_redirect = true;
	close_fd(&exec->in);
	file = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		exec->in = -1;
		error(".heredoc");
		return (1);
	}
	line = here_doc_getline(sh, i + 1, file, &err);
	while (line && ft_strncmp(line, ((t_token *)sh->tokens.tab)[i + 1].txt,
		((t_token *)sh->tokens.tab)[i + 1].txt_size))
	{
		free(line);
		line = here_doc_getline(sh, i + 1, file, &err);
	}
	if (err)
		return (1);
	free(line);
	return (get_final_heredoc_fd(exec, file));
}
