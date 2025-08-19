#include "../header/minishell.h"

t_redirect	*redirect_last(t_redirect *redirect)
{
	while (redirect && redirect->next)
		redirect = redirect->next;
	return (redirect);
}
