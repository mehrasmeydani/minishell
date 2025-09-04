/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:44:03 by alvcampo          #+#    #+#             */
/*   Updated: 2025/08/31 16:47:38 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pids_status(t_parts *parts)
{
	parts->pid1 = -1;
	parts->pid2 = -1;
	parts->status = -1;
}

void	set_exit_status(t_parts *parts, int use, int status1, int status2)
{
	if (use == 2 && WIFEXITED(status2))
		parts->status = WEXITSTATUS(status2);
	else if (use == 1 && WIFEXITED(status1))
		parts->status = WEXITSTATUS(status1);
	else
		parts->status = EXIT_FAILURE;
}

void	clean_children(t_parts *parts, int *pipes, int cmd)
{
	if (pipes[0] != CLOSED)
		close(pipes[0]);
	if (pipes[1] != CLOSED)
		close(pipes[1]);
	if ((cmd == CMD1 || cmd == ALLCMDS) && parts->fdin != CLOSED)
		close(parts->fdin);
	if ((cmd == CMD2 || cmd == ALLCMDS) && parts->fdout != CLOSED)
		close(parts->fdout);
	free_cmds(parts, ALLCMDS);
	exit(EXIT_FAILURE);
}

void	free_cmds(t_parts *parts, int cmd)
{
	if (parts->cmd1 != NULL && (cmd == CMD1 || cmd == ALLCMDS))
	{
		freetable(parts->cmd1, splitlen(parts->cmd1));
		parts->cmd1 = NULL;
	}
	if (parts->cmd2 != NULL && (cmd == CMD2 || cmd == ALLCMDS))
	{
		freetable(parts->cmd2, splitlen(parts->cmd2));
		parts->cmd2 = NULL;
	}
}
