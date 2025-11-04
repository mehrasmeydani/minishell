/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_construct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:42:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:42:16 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	**sanitize_paths(char **pathlist)
{
	ssize_t	i;
	char	*temp;

	i = -1;
	while (pathlist[++i] != NULL)
	{
		temp = ft_strjoin(pathlist[i], "/");
		if (!temp)
			return (freepaths(pathlist), NULL);
		free(pathlist[i]);
		pathlist[i] = temp;
	}
	return (pathlist);
}

static int	has_preceding_trailing_colon(char *envp_path)
{
	if (!*envp_path)
		return (0);
	if (envp_path[0] == ':')
		return (1);
	if (envp_path[ft_strlen(envp_path - 1)] == ':')
		return (2);
	return (0);
}

static char	*join_dot_path(char *path)
{
	char	*temp;

	if (has_preceding_trailing_colon(path) == 1)
	{
		temp = ft_strjoin(".", path);
		free (path);
		return (temp);
	}
	if (has_preceding_trailing_colon(path) == 2)
	{
		temp = ft_strjoin(path, ".");
		free (path);
		return (temp);
	}
	else
		return (path);
}

char	**get_path_array(char **envp, bool *isemptypath)
{
	char	*envp_path;
	char	**pathlist;
	char	*path;

	envp_path = findpath(envp);
	if (!envp_path)
		return (*isemptypath = true, NULL);
	path = ft_strdup(envp_path);
	if (!path)
		return (NULL);
	path = join_dot_path(path);
	if (!path)
		return (NULL);
	pathlist = ft_split(path, ':');
	free(path);
	if (!pathlist)
		return (NULL);
	pathlist = sanitize_paths(pathlist);
	return (pathlist);
}
