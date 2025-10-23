#include "../../header/minishell.h"

t_expands	*exp_new(char *in, bool back_space, bool front_space)
{
	t_expands	*out;

	out = (t_expands *)ft_calloc(1, sizeof(t_expands));
	if (!out)
		return (NULL);
	out->str = in;
	if (in)
	{
		if (*in == '\'')
			out->quotes = SINGLE;
		else if (*in == '"')
			out->quotes	= DOUBLE;
	}
	out->back_space = back_space;
	out->front_space = front_space;
	return (out);
}
