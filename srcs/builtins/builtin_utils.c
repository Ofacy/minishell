/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 18:30:15 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/14 19:51:50 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	builtin_init(t_mshell *sh)
{
	sh->commands[0] = (t_cmd){"echo", echo, true};
	sh->commands[1] = (t_cmd){"cd", cd, false};
	sh->commands[2] = (t_cmd){"pwd", pwd, true};
	sh->commands[3] = (t_cmd){"env", env, true};
	sh->commands[4] = (t_cmd){"unset", unset, false};
}

t_cmd	*get_builtin(t_mshell *sh, char *cmd)
{
	size_t	i;

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(sh->commands[i].name, cmd) == 0)
			return (&sh->commands[i]);
		i++;
	}
	return (NULL);
}
