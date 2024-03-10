/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:25:35 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/10 21:44:32 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

pid_t	exec_fork(t_execute *exec, t_mshell *sh)
{
	pid_t	pid;
	char	**envp;

	pid = fork();
	if (pid == -1)
	{
		error("fork");
		free_mshell(sh);
		return (-1);
	}
	envp = env_to_envp(&sh->env);
	if (!envp)
	{
		error("envp");
		free_mshell(sh);
		return (-1);
	}
	if (pid == 0)
		exec_cmd(exec, sh, envp);
	ft_freesplit(envp);
	return (pid);
}
