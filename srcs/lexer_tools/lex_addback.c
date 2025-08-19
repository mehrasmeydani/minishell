#include "../../header/minishell.h"

void	lex_addback(t_lex **lex, t_lex *new)
{
	t_lex	*tmp;

	if (lex)
	{
		tmp = lex_last(*lex);
		if (tmp)
			(tmp)->next = new;
		else
			*lex = new;
	}
}
