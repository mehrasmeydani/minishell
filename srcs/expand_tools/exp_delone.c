#include "../../header/minishell.h"

void	exp_delone(t_expands *exp, void (*del)(void *))
{
	if (exp && del)
	{
		(*del)(exp->str);
		free(exp);
	}
}
