/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_with_slashes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:41:40 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:41:41 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

static int	is_a_dir(char *cmd, int *errorcode)
{
	struct stat	stats;

	if (stat(cmd, &stats) == -1)
	{
		if (errno == ENOENT)
			return (*errorcode = 127, -1);
		else
			return (*errorcode = 1, -1);
	}
	if (S_ISDIR(stats.st_mode))
		return (*errorcode = 126, errno = EISDIR, 1);
	return (0);
}

static char	*get_cmd_absolute(char *cmd, int *errorcode)
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

char	*get_cmd_with_slashes(t_lex *node, int *errorcode)
{
	if (!is_a_dir(node->cmd[0], errorcode))
		return (get_cmd_absolute(node->cmd[0], errorcode));
	return (NULL);
}
