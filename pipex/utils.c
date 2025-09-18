/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:47:38 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/06 16:16:40 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	len = ft_strlen(s);
	copy = (char *)malloc((len + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strlcpy (copy, s, len + 1);
	return (copy);
}

int	splitlen(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		i++;
	}
	return (i);
}

void	freepaths(t_parts *parts)
{
	size_t	i;

	i = 0;
	while (parts->pathlist[i] != NULL)
	{
		free(parts->pathlist[i]);
		parts->pathlist[i] = NULL;
		i++;
	}
	free(parts->pathlist);
	parts->pathlist = NULL;
}

int	lentilspace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}
