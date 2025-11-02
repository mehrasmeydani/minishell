#include "../../header/minishell.h"

t_expands	*exp_last(t_expands *exp)
{
	while (exp && exp->next)
		exp = exp->next;
	return (exp);
}
