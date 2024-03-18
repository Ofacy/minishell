/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:11:23 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/18 19:22:42 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>

int	main(int argc, char **argv, char **env)
{
	t_mshell mshell;
	size_t	i = 0;
	char	*input;

	mshell.stdout = dup(STDOUT_FILENO);
	init_mshell(&mshell);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (create_env(&mshell.env, env) != 0)
		return (1);
	while (mshell.exit == -1)
	{
		signal(SIGINT, signal_handler);
		input = get_user_input(&mshell);
		signal(SIGINT, signal_stop);
		if (!input)
			break ;
		mshell.input = input;
		lexer(&mshell.tokens, input);
		if (check_syntax(&mshell.tokens) == 0)
		{
			expander(&mshell, 0, mshell.tokens.len);
			set_env_return(&mshell, wait_for_child(exec(&mshell)));
			i = 0;
			while (i < mshell.tokens.len)
			{
				printf("i = %-5lu; old_type = %d, type = %d, sparated = %d, heap = %d", i, ((t_token *)mshell.tokens.tab)[i].old_type, ((t_token *)mshell.tokens.tab)[i].type, ((t_token *)mshell.tokens.tab)[i].is_separated, ((t_token *)mshell.tokens.tab)[i].is_txt_heap);
				if (((t_token *)mshell.tokens.tab)[i].txt != NULL)
					printf(" is_file = %d txt = '%s', size = %lu", ((t_token *)mshell.tokens.tab)[i].is_file, ((t_token *)mshell.tokens.tab)[i].txt, ((t_token *)mshell.tokens.tab)[i].txt_size);
				printf("\n\n");
				i++;
			}
		}
		if (mshell.tokens.len != 0)
			add_history(input);
		free(input);
		vector_foreach(&mshell.tokens, (void (*)(void *))free_token);
		vector_free(&mshell.tokens);
	}
	printf("exit\n");
	rl_clear_history();
	close_fd(&mshell.stdout);
	vector_foreach(&mshell.env, (void (*)(void *))env_free);
	vector_free(&mshell.env);
	free(mshell.last_return.value);
	(void)argc;
	(void)argv;
	(void)env;
	return (mshell.exit);
}
