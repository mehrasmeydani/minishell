/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:34:21 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/04 19:52:07 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	lentilspace(char *str)
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

static void	check_read(t_parts *parts, char **argv)
{
	if (parts->fdin == FAIL)
		return (perror(argv[1]));
	if (parts->fdout == FAIL)
	{
		perror(argv[4]);
		return ;
	}
}

void	check_files(t_parts *parts, int argc, char **argv)
{
	int		indexin;
	int	indexout;

	indexout = argc - 1;
	indexin = 1;
	if (access(argv[indexin], R_OK) == 0)
		parts->fdin = open(argv[indexin], O_RDONLY);
	else
		parts->fdin = FAIL;
	if (access(argv[indexout], F_OK) == -1)
		parts->fdout = open(argv[indexout], O_WRONLY | O_CREAT, 0644);
	else if (access(argv[indexout], W_OK) == 0)
		parts->fdout = open(argv[indexout], O_WRONLY | O_TRUNC);
	else
		parts->fdout = FAIL;
	check_read(parts, argv);
}

static char	*check_cmd(t_parts *parts, char *cmd)
{
	char	**templist;
	char	*temp;
	size_t	i;

	i = 0;
	templist = parts->pathlist;
	while (templist[i] != NULL)
	{
		temp = partialjoin(templist[i], cmd, lentilspace(cmd));
		if (!temp)
			return (parts->cmds_fail = YES, NULL);
		if (access(temp, X_OK) == 0)
		{
			free(temp);
			temp = ft_strjoin(templist[i], cmd);
			if (!temp)
				return (parts->cmds_fail = YES, NULL);
			return (temp);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

void	init_cmd_properties(t_parts *parts)
{
	parts->cmd1 = NULL;
	parts->cmd2 = NULL;
	parts->cmds_fail = NO;
}
void	set_commands(t_parts *parts, char **argv)
{
	char	*temp;
	
	init_cmd_properties(parts);
	temp = check_cmd(parts, argv[2]);
	if (!temp && parts->cmds_fail == YES)
		return (freepaths(parts));
	if (temp != NULL)
		{
			parts->cmd1 = ft_split(temp, ' ');
			if(!parts->cmd1)
				return(free(temp), freepaths(parts));
		}
	free(temp);
	temp = check_cmd(parts, argv[3]);
	freepaths(parts);
	if (!temp && parts->cmds_fail == YES)
		return (free_cmds(parts, CMD1));
	if (temp != NULL)
	{
		parts->cmd2 = ft_split(temp, ' ');
		if (!parts->cmd2)
			return (free(temp), free_cmds(parts, CMD1));
	}
	free(temp);
}
