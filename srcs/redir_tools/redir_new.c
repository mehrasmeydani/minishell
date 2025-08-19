#include "../../header/minishell.h"

t_redirect	*redirect_new(char *in, int i)
{
	t_redirect	*out;

	out = (t_redirect *)calloc(1, sizeof(t_redirect));
	if (!out)
		return (NULL);
	out->name = in;
	out->level = i;
	return (out);
}
