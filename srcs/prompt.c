/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:12:55 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/08 17:56:00 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*prompt(t_mshell *sh)
{
	t_token	prompt;

	prompt.txt = "$PROMPT";
	prompt.txt_size = 7;
	prompt.is_txt_heap = false;
	prompt.type = UNQUOTED;
	if (get_expended_str(&prompt, &sh->env) != 0)
		return (NULL);
	if (get_expended_str(&prompt, &sh->env) != 0)
	{
		free_token(&prompt);
		return (NULL);
	}
	return (prompt.txt);
}
