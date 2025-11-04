/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 00:53:14 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

char	*unset_path_cmd(char *cmd, int *errorcode)
{
	char	*new_cmd;

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

int	pre_cmd_check(t_lex *node, int *errorcode, ssize_t *i)
{
	*i = -1;
	if (node->cmd[0] == NULL)
		return (0);
	if (!ft_strcmp(node->cmd[0], ".") || !ft_strcmp(node->cmd[0], ".."))
		return (errno = ENOENT, *errorcode = 127, 0);
	return (1);
}

int	post_cmd_check(t_lex *node, char **pathlist, int *errorcode, char *new_cmd)
{
	if (!*pathlist || !*node->cmd[0])
		return (free(new_cmd), *errorcode = 127, errno = ENOENT, 0);
	if (new_cmd && access(new_cmd, X_OK) != 0)
		return (free(new_cmd), *errorcode = 126, 0);
	return (1);
}

char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode)
{
	ssize_t	i;
	char	*new_cmd;

	new_cmd = NULL;
	if (!pre_cmd_check(node, errorcode, &i))
		return (NULL);
	if (ft_strchr(node->cmd[0], '/') != NULL)
		return (get_cmd_with_slashes(node, errorcode));
	if (!pathlist || !*pathlist)
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
		if (pathlist[i + 1] == NULL)
			return (*errorcode = 127, NULL);
	}
	if (!post_cmd_check(node, pathlist, errorcode, new_cmd))
		return (NULL);
	return (new_cmd);
}
