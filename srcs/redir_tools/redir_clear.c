#include "../header/minishell.h"

void	redirect_clear(t_redirect **redirect, void (*del)(void *))
{
	t_redirect	*tmp;

	if (redirect)
	{
		while (*redirect)
		{
			tmp = *redirect;
			*redirect = (*redirect)->next;
			redirect_delone(tmp, del);
		}
	}
}
