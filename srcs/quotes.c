#include "../header/minishell.h"

int quotes(char c, int *state)
{
	if (c == '"' && *state == DOUBLE)
		*state = 0;
	else if (c == '"' && *state == 0)
		*state = DOUBLE;
	else if (c == '\'' && *state == SINGLE)
		*state = 0;
	else if (c == '\'' && *state == 0)
		*state = SINGLE;
	return (1);
}