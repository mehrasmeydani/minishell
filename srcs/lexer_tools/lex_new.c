#include "../../header/minishell.h"

t_lex	*lex_new(char **in)
{
	t_lex	*out;

	out = (t_lex *)calloc(1, sizeof(t_lex));
	if (!out)
		return (NULL);
	out->cmd = in;
	return (out);
}
