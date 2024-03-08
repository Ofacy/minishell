/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:55:03 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/08 17:56:01 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "vector.h"
# include "lexer.h"

# define CMD_COUNT 7

# define ENV_NAME_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
	0123456789_?"

typedef struct s_env
{
	char	*key;
	char	*value;
	size_t	value_size;
	size_t	key_size;
}	t_env;

typedef struct s_cmd
{
	char	*name;
	int		(*func)(int argc, char **argv, t_vector *env);
}	t_cmd;

typedef struct s_execute
{
	char	*cmd;
	char	**args;
}	t_execute;

typedef struct s_mshell
{
	t_cmd		commands[CMD_COUNT];
	t_vector	tokens;
	t_vector	env;
	int			stdout;
}	t_mshell;

void	free_token(t_token *token);

int		expander(t_vector *lex, t_vector *env);
int		get_expended_str(t_token *token, t_vector *env);
void	env_free(void *env);
t_env	*env_get(t_vector *env, char *key);
int		env_set(t_vector *env, char *key, char *value);
int		create_env(t_vector *vector, char **env);

int 	check_syntax(t_vector *tokens);
bool	is_unclosed_quotes(t_token *token);
bool	is_type_arrow(t_tokentype type);
bool	is_special(t_tokentype type);
char	*get_token_str(t_tokentype type);

char	*expander_join(t_token *t1, t_token *t2);

#endif