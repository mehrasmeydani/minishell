#include "../../header/minishell.h"

void	redirect_addback(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*tmp;

	if (redirect)
	{
		tmp = redirect_last(*redirect);
		if (tmp)
			(tmp)->next = new;
		else
			*redirect = new;
	}
}
