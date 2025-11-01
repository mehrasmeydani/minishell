/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/01 17:03:17 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

char	*get_cmd_absolute(char *cmd, int *errorcode)
{
	char	*new_cmd;

	new_cmd = ft_strdup(cmd);
	if (!new_cmd)
		return (*errorcode = 1, (NULL));
	if (access(new_cmd, F_OK) == 0)
	{
		if (access(new_cmd, X_OK) == 0)
			return (new_cmd);
		else
			return (free(new_cmd), *errorcode = 126, NULL);
	}
	return (free(new_cmd), *errorcode = 127, NULL);
}

char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode)
{
	ssize_t	i;
	char	*new_cmd;

	i = -1;
	new_cmd = NULL;
	if (node->cmd[0] == NULL)
		return (NULL);
	if (ft_strchr(node->cmd[0], '/') != NULL)
		return (new_cmd = get_cmd_absolute(node->cmd[0], errorcode));
	if (!pathlist)
		return (*errorcode = 127, errno = ENOENT, NULL);
	while (pathlist[++i] != NULL)
	{
		new_cmd = ft_strjoin(pathlist[i], node->cmd[0]);
		if (!new_cmd)
			return (*errorcode = 1, perror("command alloc"), NULL);
		if (access(new_cmd, F_OK) == 0)
			break ;
		free(new_cmd);
		if (pathlist[i + 1] == NULL)
			return (*errorcode = 127, NULL);
	}
	if (access(new_cmd, X_OK) != 0)
		return (free(new_cmd), *errorcode = 126, NULL);
	return (new_cmd);
}
