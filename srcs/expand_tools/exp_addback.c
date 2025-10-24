#include "../../header/minishell.h"

void	exp_addback(t_expands **exp, t_expands *new)
{
	t_expands	*tmp;

	if (exp)
	{
		tmp = exp_last(*exp);
		if (tmp)
		{
			(tmp)->next = new;
			if (new)
				new->prev = tmp;
		}
		else
			*exp = new;
	}
}
