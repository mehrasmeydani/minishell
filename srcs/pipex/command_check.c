/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/01 18:36:33 by megardes         ###   ########.fr       */
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

char	*unset_path_cmd(char *cmd, int *errorcode)
{
	char *new_cmd;

	new_cmd = ft_strjoin("./", cmd);
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

int	is_a_dir(char *cmd, int *errorcode)
{
	struct stat	stats;

	if (stat(cmd, &stats) == -1)
		return (*errorcode = 1, -1);
	if (S_ISDIR(stats.st_mode))
		return (*errorcode = 126, errno = EISDIR, 1);
	return (0);
}

char	*absolute_cmd_or_dir(char *cmd, int *errorcode)
{
	if (!is_a_dir(cmd, errorcode))
		return (get_cmd_absolute(cmd, errorcode));
	return (NULL);
}

char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode)
{
	ssize_t	i;
	char	*new_cmd;

	i = -1;
	if (node->cmd[0] == NULL)
		return (NULL);
	if (ft_strchr(node->cmd[0], '/') != NULL)
		return (absolute_cmd_or_dir(node->cmd[0], errorcode));
	if (!pathlist)
		return (unset_path_cmd(node->cmd[0], errorcode));
	while (pathlist && pathlist[++i] != NULL)
	{
		new_cmd = ft_strjoin(pathlist[i], node->cmd[0]);
		if (!new_cmd)
			return (*errorcode = 1, perror("command alloc"), NULL);
		if (access(new_cmd, F_OK) == 0)
			break ;
		free(new_cmd);
		new_cmd = NULL;
		if(pathlist[i+1] == NULL)
			return (*errorcode = 127, NULL);
	}
	if (!*pathlist)
		return (*errorcode = 127, errno = ENOENT, NULL);
	if (new_cmd && access(new_cmd, X_OK) != 0)
		return(free(new_cmd), *errorcode = 126, NULL);
	return(new_cmd);
}
