#include "../../header/minishell.h"
void	echo(char **cmd)
{
	size_t	i;
	bool	trailingn;

	trailingn = true;
	i = 1;
	if (!ft_strcmp(cmd[1], "-n"))
	{
		i++;
		trailingn = false;
	}
	while (cmd[i] != NULL)
	{
		if (trailingn == false)
			if(cmd[i + 1] == NULL)
				return ;
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		i++;
	}
}
