/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_children.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:49:00 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/06 14:59:01 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_pipe(t_parts *parts, int *pipes, int cmd)
{
	if (cmd == CMD1)
	{
		if (dup2(parts->fdin, STDIN_FILENO) == -1)
			clean_children(parts, pipes, cmd);
		parts->fdin = CLOSED;
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			return (close(STDIN_FILENO), clean_children(parts, pipes, cmd));
	}
	else if (cmd == CMD2)
	{
		pipes[1] = CLOSED;
		parts->fdin = CLOSED;
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			clean_children(parts, pipes, cmd);
		pipes[0] = CLOSED;
		if (dup2(parts->fdout, STDOUT_FILENO) == -1)
			return (close(STDIN_FILENO), clean_children(parts, pipes, cmd));
	}
}

static void	execute_cmd(t_parts *parts, int *pipes, char **envp, int cmd)
{
	if (cmd == CMD1)
	{
		execve(parts->cmd1[0], parts->cmd1, envp);
		perror(parts->cmd1[0]);
		close(STDIN_FILENO);
		free_cmds(parts, ALLCMDS);
		clean_children(parts, pipes, cmd);
	}
	execve(parts->cmd2[0], parts->cmd2, envp);
	perror(parts->cmd2[0]);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	free_cmds(parts, ALLCMDS);
	clean_children(parts, pipes, cmd);
}

void	construct_baby(t_parts *parts, int *pipes, char **envp, int cmd)
{
	if (cmd == CMD1)
	{
		set_pipe(parts, pipes, CMD1);
		execute_cmd(parts, pipes, envp, CMD1);
	}
	else if (cmd == CMD2)
	{
		set_pipe(parts, pipes, CMD2);
		execute_cmd(parts, pipes, envp, CMD2);
	}
}
