#include "../execution.h"
void	freepaths(char **pathlist)
{
	size_t	i;

	i = 0;
	while (pathlist[i] != NULL)
	{
		free(pathlist[i]);
		pathlist[i] = NULL;
		i++;
	}
	free(pathlist);
}

