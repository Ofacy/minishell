/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:11:23 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/09 18:44:16 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

int	main(int argc, char **argv, char **env)
{
	t_mshell mshell;
	size_t	i = 0;
	char	*input;

	mshell.stdout = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (create_env(&mshell.env, env) != 0)
		return (1);
	while (1)
	{
		input = get_user_input(&mshell);
		if (!input)
			break ;
		lexer(&mshell.tokens, input);
		if (mshell.tokens.len != 0)
			add_history(input);
		check_syntax(&mshell.tokens);
		expander(&mshell.tokens, &mshell.env);
		i = 0;
		while (i < mshell.tokens.len)
		{
			printf("i = %-5lu; type = %d, sparated = %d", i, ((t_token *)mshell.tokens.tab)[i].type, ((t_token *)mshell.tokens.tab)[i].is_separated);
			if (((t_token *)mshell.tokens.tab)[i].txt != NULL)
				printf(" txt = '%s', size = %lu", ((t_token *)mshell.tokens.tab)[i].txt, ((t_token *)mshell.tokens.tab)[i].txt_size);
			printf("\n");
			i++;
		}
		free(input);
		vector_foreach(&mshell.tokens, (void (*)(void *))free_token);
		vector_free(&mshell.tokens);
	}
	rl_clear_history();
	vector_foreach(&mshell.env, (void (*)(void *))env_free);
	vector_free(&mshell.env);
	(void)argc;
	(void)argv;
	(void)env;
}
