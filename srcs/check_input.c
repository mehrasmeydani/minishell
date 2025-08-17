#include "../header/minishell.h"

int check_input(char *in)
{
	ssize_t	i;

	i = -1;
	while (in[++i])
	{
		if (in[i] == '|' && (in[i + 1] == 0 || in[i + 1] == '|'))
			return (0);
	}	
}