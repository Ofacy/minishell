/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:11:23 by lcottet           #+#    #+#             */
/*   Updated: 2024/04/08 14:10:03 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

int	minishell(t_mshell *sh, char *input)
{
	int		syntax;
	pid_t	pid;

	if (lexer(&sh->tokens, input) != 0)
		return (-1);
	if (sh->tokens.len != 0 && isatty(STDERR_FILENO))
		add_history(input);
	syntax = check_syntax(&sh->tokens);
	if (syntax == 0)
	{
		expander(sh, 0, sh->tokens.len);
		pid = exec(sh);
		if (pid != -4)
			set_env_return(sh, wait_for_child(pid));
		reset_signal();
	}
	else
		set_env_return(sh, syntax);
	free(input);
	vector_foreach(&sh->tokens, (void (*)(void *))free_token);
	vector_free(&sh->tokens);
	return (0);
}

void	finish_mshell(t_mshell *mshell)
{
	rl_clear_history();
	close_fd(&mshell->stdout);
	close_fd(&mshell->stdin);
	vector_foreach(&mshell->env, (void (*)(void *))env_free);
	vector_free(&mshell->env);
	free(mshell->last_return.value);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

int	prepare_mshell(t_mshell *mshell, char **env)
{
	signal(SIGQUIT, signal_handler);
	mshell->stdout = dup(STDOUT_FILENO);
	if (mshell->stdout == -1)
		return (1);
	mshell->stdin = dup(STDIN_FILENO);
	if (mshell->stdin == -1)
		return (1);
	init_mshell(mshell);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (create_env(mshell, env) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mshell	mshell;
	char		*input;

	(void)argc;
	(void)argv;
	if (prepare_mshell(&mshell, env) != 0)
		return (error("init"), 1);
	while (mshell.exit == -1)
	{
		signal(SIGINT, signal_handler);
		input = get_user_input(&mshell);
		signal(SIGINT, signal_stop);
		if (!input)
			break ;
		mshell.input = input;
		minishell(&mshell, input);
	}
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	finish_mshell(&mshell);
	if (mshell.exit == -1)
		return (0);
	return ((char)mshell.exit);
}
