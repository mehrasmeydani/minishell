/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:16:03 by alvcampo          #+#    #+#             */
/*   Updated: 2025/08/15 19:06:57 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static int	isemptypath(char *path)
{
	size_t	i;

	i = 0;
	while (path[i])
	{
		if (path[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static void	sanitizepaths(t_parts *parts)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (parts->pathlist[i] != NULL)
	{
		if (isemptypath(parts->pathlist[i]) == 0)
		{
			temp = ft_strjoin(parts->pathlist[i], "/");
			if (!temp)
				return (freepaths(parts));
			free(parts->pathlist[i]);
			parts->pathlist[i] = temp;
		}
		else
		{
			temp = ft_strdup("");
			if (!temp)
				return (freepaths(parts));
			free(parts->pathlist[i]);
			parts->pathlist[i] = temp;
		}
		i++;
	}
}

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

static char **emptysplit()
{
	char	**split;
	split = malloc (2 * sizeof(char*));
	if (!split)
		return (NULL);
	split[0] = ft_strdup("");
	if (!split[0])
	{
		free(split);
		return (NULL);
	}
	split[1] = NULL;
	return(split);
}

void	getpatharray(t_parts *parts, char **envp)
{
	char	*path;
	char	*temp;

	path = findpath(envp);
	if (!path)
	{
		parts->pathlist = emptysplit();
		return ;
	}
	temp = ft_strjoin(" :", path);
	if (!temp)
	{
		parts->pathlist = NULL;
		return ;
	}
	parts->pathlist = ft_split(temp, ':');
	free(temp);
	if (!parts->pathlist)
		return ;
	sanitizepaths(parts);
}
