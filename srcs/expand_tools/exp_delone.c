#include "../header/minishell.h"

void	exp_delone(t_expands *exp, char *(*del)(char *))
{
	if (exp && del)
	{
		(*del)(exp->str);
		free(exp);
	}
}
