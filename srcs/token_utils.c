
#include "minishell.h"

bool	is_type_arrow(t_tokentype type)
{
	return (type == HEREDOC || type == REDIRECT_APPEND ||
		type == REDIRECT_INPUT || type == REDIRECT_OUTPUT);
}

bool	is_unclosed_quotes(t_token *token)
{
	return (token->txt == NULL && (token->type == DOUBLE_QUOTED
		|| token->type == SINGLE_QUOTED));
}

bool	is_special(t_tokentype type)
{
	return (is_type_arrow(type) || type == PIPE);
}

char	*get_token_str(t_tokentype type)
{
	if (type == REDIRECT_APPEND)
		return (">>");
	else if (type == REDIRECT_OUTPUT)
		return (">");
	else if (type == HEREDOC)
		return ("<<");
	else if (type == REDIRECT_INPUT)
		return ("<");
	else if (type == DOUBLE_QUOTED)
		return ("\"");
	else if (type == SINGLE_QUOTED)
		return ("'");
	else if (type == NEWLINE)
		return ("newline");
	return ("UNKNOWN");
}
