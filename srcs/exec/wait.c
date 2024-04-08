/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:58:52 by bwisniew          #+#    #+#             */
/*   Updated: 2024/04/08 14:04:46 by bwisniew         ###   ########.fr       */
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
	if (last_pid == -3)
		return (0);
	if (last_pid == -2)
		return (1);
	if (errno != ECHILD)
		return (error("wait"), 127);
	if (last_pid == -1 && g_signal == 0)
		return (127);
	else if (last_pid == -1)
		return (128 + g_signal);
	if (WIFSIGNALED(last_pid_status))
		return (WTERMSIG(last_pid_status) + 128);
	return (WEXITSTATUS(last_pid_status));
}
