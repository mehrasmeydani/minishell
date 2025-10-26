#include "../../header/minishell.h"
void	echo(char **cmd)
{
	size_t	i;
	bool	trailingn;

	trailingn = true;
	i = 1;
	if (cmd[1] == NULL)
		return ((void) write(STDOUT_FILENO, "\n", 1));
	if (!ft_strcmp(cmd[1], "-n"))
	{
		i++;
		trailingn = false;
	}
	while (cmd[i] != NULL)
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if(cmd[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (trailingn == true)
		write(STDOUT_FILENO, "\n", 1);
} 
