#include "../../header/minishell.h"
int	pwd()
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (!currdir)
		return (0);
	write(STDOUT_FILENO, currdir, ft_strlen(currdir));
	write(STDOUT_FILENO, "\n", 1);
	free(currdir);
	return (1);
}
