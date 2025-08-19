#include "../header/minishell.h"

void	lex_delone(t_lex *lex, char **(*del)(char **, ssize_t), ssize_t i)
{
	if (lex && del)
	{
		(*del)(lex->cmd, i);
		free(lex);
	}
}
