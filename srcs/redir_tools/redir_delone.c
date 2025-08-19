#include "../header/minishell.h"

void	redirect_delone(t_redirect *redirect, void (*del)(void *))
{
	if (redirect && del)
	{
		(*del)(redirect->name);
		(*del)(redirect->input);
		free(redirect);
	}
}
