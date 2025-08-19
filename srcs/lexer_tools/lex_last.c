#include "../header/minishell.h"

t_lex	*lex_last(t_lex *lex)
{
	while (lex && lex->next)
		lex = lex->next;
	return (lex);
}
