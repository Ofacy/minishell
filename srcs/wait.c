/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:58:52 by bwisniew          #+#    #+#             */
/*   Updated: 2024/03/11 18:00:43 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <wait.h>
#include <errno.h>
#include <unistd.h>

int	wait_for_child(pid_t last_pid)
{
	int		last_pid_status;
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid)
			last_pid_status = status;
		pid = wait(&status);
	}
	if (last_pid == -2)
		return (127);
	if (errno != ECHILD)
		return (error("wait"), 127);
	if (last_pid == -1)
		return (1);
	if (WIFSIGNALED(last_pid_status))
		return (WTERMSIG(last_pid_status) + 128);
	return (WEXITSTATUS(last_pid_status));
}
