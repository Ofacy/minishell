/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:36 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/08 13:07:43 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static long long	ft_getnb(const char *nptr, size_t i)
{
	long	nb;

	nb = 0;
	while (ft_isdigit(nptr[i]))
	{
		if (nb != (nb * 10 + nptr[i] - 48) / 10)
		{
			builtin_error("exit", "numeric argument required");
			return (-1);
		}
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb);
}

static long long	ft_atoll(const char *nptr)
{
	size_t	i;
	char	sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = ft_getnb(nptr, i);
	return ((int)(nb * sign));
}

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
		sh->exit = (int)(unsigned char)ft_atoll(args[1]);
		return (sh->exit);
	}
	sh->exit = ft_atoll(sh->last_return.key);
	return (0);
}
