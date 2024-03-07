/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:55:03 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 23:29:58 by lcottet          ###   ########.fr       */
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
	char	*name;
	char	*value;
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

void		env_free(void *env);
char		*env_get(t_vector *env, char *name, size_t size);
int			env_set(t_vector *env, char *name, char *value);
int			create_env(t_vector *vector, char **env);

#endif