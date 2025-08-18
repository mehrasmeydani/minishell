#include "../header/minishell.h"

int	quotes(char c, int *state)
{
	if (c == '"' && *state == DOUBLE)
		*state = 0;
	else if (c == '"' && *state != SINGLE && *state != DOUBLE)
		*state = DOUBLE;
	else if (c == '\'' && *state == SINGLE)
		*state = 0;
	else if (c == '\'' && *state != SINGLE && *state != DOUBLE)
		*state = SINGLE;
	return (1);
}
