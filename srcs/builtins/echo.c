/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:57:42 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/21 12:15:06 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

bool	echo_is_valid_flag(char *src, bool *has_n)
{
	size_t	i;

	if (src[0] != '-')
		return (false);
	i = 1;
	while (src[i] == 'n')
	{
		*has_n = false;
		i++;
	}
	return (src[i] == '\0');
}

size_t	echo_skip_flag(char **args, bool *has_n)
{
	size_t	i;

	i = 1;
	*has_n = true;
	while (args[i] && echo_is_valid_flag(args[i], has_n))
	{
		i++;
	}
	return (i);
}

int	echo_print_args(char **args, size_t i)
{
	int		res;

	res = -2;
	while (args[i])
	{
		if (res == -2)
			res = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		else
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				error("echo");
				return (1);
			}
			res = write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		}
		if (res == -1)
		{
			error("echo");
			return (1);
		}
		i++;
	}
	return (0);
}

int	echo(t_mshell *sh, t_execute *exec)
{
	size_t	i;
	char	**args;
	bool	has_nl;

	args = exec->args.tab;
	(void)sh;
	i = echo_skip_flag(args, &has_nl);
	if (echo_print_args(args, i) != 0)
		return (1);
	if (has_nl && write(1, "\n", 1) == -1)
	{
		error("echo");
		return (1);
	}
	return (0);
}
