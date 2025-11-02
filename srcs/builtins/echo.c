#include "../../header/minishell.h"

void	echo_flags(char **cmd, ssize_t *i, ssize_t *j, bool *trailingn)
{
	while (cmd[*i] && !ft_strncmp(cmd[*i], "-n", 2)
		&& !is_in(cmd[*i], "\t\n\r\v\f "))
	{
		(*j) = 1;
		while (cmd[*i][++(*j)] && cmd[*i][(*j)] == 'n')
			;
		if (!cmd[*i][(*j)])
			*trailingn = false;
		else
			break ;
		(*i)++;
	}
}

void	echo(char **cmd)
{
	ssize_t	i;
	ssize_t	j;
	bool	trailingn;

	trailingn = true;
	i = 1;
	if (cmd[1] == NULL)
		return ((void) write(STDOUT_FILENO, "\n", 1));
	echo_flags(cmd, &i, &j, &trailingn);
	while (cmd[i] != NULL)
	{
		write(STDOUT_FILENO, cmd[i], ft_strlen(cmd[i]));
		if (cmd[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (trailingn == true)
		write(STDOUT_FILENO, "\n", 1);
}
