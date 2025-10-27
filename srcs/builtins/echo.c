#include "../../header/minishell.h"

static int	is_in(char *str, char *set)
{
	ssize_t i;
	ssize_t	j;

	i = -1;
	while (str && str[++i])
	{
		j = -1;
		while (set && set[++j])
			if (str[i] == set[j])
				return (1);
	}
	return (0);
}

void	echo(char **cmd)
{
	size_t	i;
	bool	trailingn;

	trailingn = true;
	i = 1;
	if (cmd[1] == NULL)
		return ((void) write(STDOUT_FILENO, "\n", 1));
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2) && !is_in(cmd[i], "\t\n\r\v\f "))
	{
		//if (!ft_strncmp(cmd[1], "-n", 2))
			trailingn = false;
		i++;
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
