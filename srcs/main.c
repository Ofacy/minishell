/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:11:23 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 19:59:03 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv, char **env)
{
	t_vector lex;
	size_t i = 0;
	
	lexer(&lex, argv[1]);
	while (i < lex.len)
	{
		printf("type = '%d'", ((t_token *)lex.tab)[i].type);
		if (((t_token *)lex.tab)[i].txt != NULL)
			printf(" txt = '%s'", ((t_token *)lex.tab)[i].txt);
		printf("\n");
		i++;
	}
	vector_free(&lex);
	(void)argc;
	(void)argv;
	(void)env;
}
