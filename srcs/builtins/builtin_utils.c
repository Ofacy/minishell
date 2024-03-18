/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:30:15 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/18 10:36:45 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_init(t_mshell *sh)
{
	sh->commands[0] = (t_cmd){"echo", echo};
	sh->commands[1] = (t_cmd){"cd", cd};
	sh->commands[2] = (t_cmd){"pwd", pwd};
	sh->commands[3] = (t_cmd){"env", env};
	sh->commands[4] = (t_cmd){"unset", unset};
	sh->commands[5] = (t_cmd){"export", export};
	sh->commands[6] = (t_cmd){"exit", exit_builtin};
}

t_cmd	*get_builtin(t_mshell *sh, char *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(sh->commands[i].name, cmd) == 0)
			return (&sh->commands[i]);
		i++;
	}
	return (NULL);
}
