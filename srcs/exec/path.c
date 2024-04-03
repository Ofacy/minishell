/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:23:03 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/03 22:43:56 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char	**get_path_folders(t_mshell *sh)
{
	t_env	*var;
	char	*path;

	path = PATH_DEFAULT;
	var = env_get(sh, "PATH", false);
	if (var && var->value)
	{
		path = var->value;
	}
	return (ft_split(path, ':'));
}

char	*path_valid(char *file, char *curr_path, int access_mode)
{
	char	*tmp1;
	char	*tmp;

	tmp1 = ft_strjoin(curr_path, "/");
	if (!tmp1)
		return (NULL);
	tmp = ft_strjoin(tmp1, file);
	free(tmp1);
	if (!tmp)
		return (NULL);
	if (access(tmp, access_mode) != -1)
		return (tmp);
	free(tmp);
	return (NULL);
}

char	*get_openable_path(char *file, int access_mode, t_mshell *sh)
{
	char	*tmp;
	int		i;
	char	**path;

	if (!file)
		return (NULL);
	if (ft_strchr(file, '/') && access(file, access_mode) != -1)
		return (ft_strdup(file));
	if (errno == EACCES)
		return (NULL);
	path = get_path_folders(sh);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = path_valid(file, path[i], access_mode);
		if (tmp)
			return (ft_freesplit(path), tmp);
		if (errno == EACCES)
			return (ft_freesplit(path), NULL);
		i++;
	}
	ft_freesplit(path);
	return (NULL);
}
