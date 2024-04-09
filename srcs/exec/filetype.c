/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 23:12:15 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/09 16:28:15 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "minishell.h"

int	regular_file_check(t_mshell *sh, char *path)
{
	struct stat	sb;

	if (!path)
		return (1);
	if (stat(path, &sb) == -1)
	{
		error(path);
		return (-1);
	}
	if (!S_ISREG(sb.st_mode))
	{
		custom_error(path, "Is a directory");
		if (set_env_return(sh, 127))
			return (-1);
	}
	return (S_ISREG(sb.st_mode));
}
