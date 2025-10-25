#include "../../header/minishell.h"

ssize_t	exp_len(t_expands *exp)
{
	ssize_t	i;

	i = 0;
	while (exp)
	{
		i++;
		exp = exp->next;
	}
	return (i);
}