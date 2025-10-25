#include "../header/minishell.h"

void	exp_clear(t_expands **exp, void (*del)(void *))
{
	t_expands	*tmp;

	if (exp && del)
	{
		while (*exp)
		{
			tmp = *exp;
			*exp = (*exp)->next;
			exp_delone(tmp, del);
		}
	}
}
