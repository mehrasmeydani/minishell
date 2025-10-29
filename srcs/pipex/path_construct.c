#include "../../header/execution.h"

static char	*findpath(char **envp)
{
	char	*path;
	size_t	i;

	i = 0;
	path = "PATH=";
	while (envp[i] != NULL)
	{
		if (ft_strncmp(path, envp[i], 5) == 0)
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

static char **sanitize_paths(char **pathlist)
{
	ssize_t	i;
	char	*temp;

	i = -1;
	while(pathlist[++i] != NULL)
	{
		temp = ft_strjoin(pathlist[i], "/");
		if (!temp)
			return (freepaths(pathlist), NULL);
		free(pathlist[i]);
		pathlist[i] = temp;
	}
	return (pathlist);
}

char	**get_path_array(char **envp, bool *isemptypath)
{
	char	*envp_path;
	char	**pathlist;

	envp_path = findpath(envp);
	if (!envp_path)
		return (*isemptypath = true, NULL);
	pathlist = ft_split(envp_path, ':');
	if(!pathlist)
		return (NULL);
	pathlist = sanitize_paths(pathlist);
	return (pathlist);
}
