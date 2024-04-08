/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:22:29 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/08 11:43:58 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"
#include <readline/readline.h>
#include <stdbool.h>

char	*hd_get_user_input(void)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && isatty(STDERR_FILENO))
		return (readline(PROMPT_HEREDOC));
	return (get_next_line(STDIN_FILENO));
}

bool	hd_cmp(char *s1, char *s2, size_t s1len)
{
	size_t	i;

	i = 0;
	while (i < s1len)
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s2[i] == '\0' || s2[i] == '\n')
		return (true);
	return (false);
}
