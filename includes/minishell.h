/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:55:03 by lcottet           #+#    #+#             */
/*   Updated: 2024/03/10 21:39:03 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lexer.h"

# define CMD_COUNT 7

# define ENV_NAME_CHAR "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\
	0123456789_?"

# define PROMPT_DEFAULT "\e[1;32m$USER@$NAME\e[0m:\e[1;36m$PWD\e[0m$ "
# define PATH_DEFAULT "/usr/local/sbin:/usr/local/bin:/usr/sbin:\
	/usr/bin:/sbin:/bin"
# define SHELL_NAME "minishell"

typedef int	t_fd;

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
	t_fd	in;
	t_fd	out;
	t_fd	nextin;
	char	*cmd;
	char	**args;
}	t_execute;

typedef struct s_mshell
{
	t_cmd		commands[CMD_COUNT];
	t_vector	tokens;
	t_vector	env;
	t_fd		stdout;
	t_fd		pipe[2];
	t_vector	history_entry;
	char		*input;
}	t_mshell;

void	free_token(t_token *token);

int		expander(t_vector *lex, t_vector *env);
int		get_expended_str(t_token *token, t_vector *env);
void	env_free(void *env);
t_env	*env_get(t_vector *env, char *key);
int		env_set(t_vector *env, char *key, char *value);
int		create_env(t_vector *vector, char **env);

char	*get_user_input(t_mshell *sh);

char	*get_openable_path(char *file, int access_mode, t_vector *env);

int		check_syntax(t_vector *tokens);
bool	is_unclosed_quotes(t_token *token);
bool	is_type_arrow(t_tokentype type);
bool	is_special(t_tokentype type);
char	*get_token_str(t_tokentype type);

int		exec(t_mshell *sh);
pid_t	exec_fork(t_execute *exec, t_mshell *sh);
void	exec_cmd(t_execute *exec, t_mshell *sh, char **envp);

char	*expander_join(t_token *t1, t_token *t2);

void	error(char *str);
void	custom_error(char *str, char *error_msg);

int		close_fd(t_fd *fd);
void	free_mshell(t_mshell *sh);
int		close_exec(t_execute *exec);

char	**env_to_envp(t_vector *env);

#endif