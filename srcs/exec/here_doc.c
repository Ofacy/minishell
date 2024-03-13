/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:41:37 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/13 17:54:54 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

char	*here_doc_getline(t_mshell *sh, size_t i)
{
	t_token	line;
	
	line.txt = readline(PROMPT_HEREDOC);
	line.txt_size = ft_strlen(line.txt);
	line.is_txt_heap = true;
	if (((t_token *)sh->tokens.tab)[i].old_type == UNQUOTED)
	{
		if (get_expended_str(&line, sh) < 0)
		{
			free_token(&line);
			return (NULL);
		}
	}
	printf("txt = %s\n", line.txt);
	return (line.txt);
}

int	here_doc_line(int file, char *line)
{
	if (write(file, line, ft_strlen(line)) == -1)
		return (free(line), 1);
	if (write(file, "\n", 1) == -1)
		return (free(line), 1);
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
	line = here_doc_getline(sh, i + 1);
	while (line && ft_strncmp(line, ((t_token *)sh->tokens.tab)[i + 1].txt,
		((t_token *)sh->tokens.tab)[i + 1].txt_size))
	{
		if (here_doc_line(file, line))
			return (2);
		line = here_doc_getline(sh, i + 1);
		printf("%s VS %s\n", line, ((t_token *)sh->tokens.tab)[i + 1].txt);
	}
	close_fd(&file);
	exec->in = open(".heredoc", O_RDONLY);
	if (exec->in == -1)
		error(".heredoc");
	unlink(".heredoc");
	return (0);
}
