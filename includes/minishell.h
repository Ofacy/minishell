/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:55:03 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/07 17:00:45 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "vector.h"

# define CMD_COUNT 7

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
}	t_mshell;

#endif
