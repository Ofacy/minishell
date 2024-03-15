/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:36 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/15 18:20:02 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static	int	ft_strisnum(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_mshell *sh, t_execute *exec)
{
	char	**args;
	size_t	argc;

	printf("exit\n");
	args = exec->args.tab;
	argc = 0;
	while (args[argc])
		argc++;
	if (argc > 2)
	{
		custom_error("exit", "too many arguments");
		return (1);
	}
	else if (argc == 2)
	{
		if (!ft_strisnum(args[1]))
		{
			custom_error("exit", "numeric argument required");
			sh->exit = 2;
			return (2);
		}
		sh->exit = (int)(unsigned char)ft_atoi(args[1]);
		return (sh->exit);
	}
	sh->exit = 0;
	return (0);
}
