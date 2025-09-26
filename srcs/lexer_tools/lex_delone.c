#include "../header/minishell.h"

void	lex_delone(t_lex *lex, char **(*del)(char **))
{
	if (lex && del)
	{
		(*del)(lex->cmd);
		free(lex);
	}
}
