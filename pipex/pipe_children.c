/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:18:13 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/06 12:59:31 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	wait_for_death(t_parts *parts)
{
	int	status1;
	int	status2;
	int	use;

	status1 = 0;
	status2 = 0;
	use = 0;
	if (parts->pid1 != -1)
	{
		waitpid(parts->pid1, &status1, 0);
		use = 1;
	}
	if (parts->pid2 != -1)
	{
		waitpid(parts->pid2, &status2, 0);
		use = 2;
	}
	set_exit_status(parts, use, status1, status2);
}

void	first_cmd(t_parts *parts, int *pipes, char **envp)
{
	parts->pid1 = fork();
	if (parts->pid1 == -1)
		return (perror("fork CMD1"));
	if (parts->pid1 == 0)
	{
		close(pipes[0]);
		pipes[0] = CLOSED;
		if (parts->fdout != FAIL)
			close(parts->fdout);
		parts->fdout = CLOSED;
		construct_baby(parts, pipes, envp, CMD1);
	}
}

void	second_cmd(t_parts *parts, int *pipes, char **envp)
{
	parts->pid2 = fork();
	if (parts->pid2 == -1)
		return (perror("Fork CMD2"));
	if (parts->pid2 == 0)
	{
		close(pipes[1]);
		pipes[1] = CLOSED;
		if (parts->fdin != FAIL)
			close(parts->fdin);
		parts->fdin = CLOSED;
		construct_baby(parts, pipes, envp, CMD2);
	}
}

void	have_a_child(t_parts *parts, char **envp)
{
	int	pipes[2];

	init_pids_status(parts);
	if (pipe(pipes) == -1)
		return (perror("pipes"));
	if (parts->fdin != FAIL && parts->cmd1 != NULL)
		first_cmd(parts, pipes, envp);
	if (parts->fdout != FAIL && parts->cmd2 != NULL)
		second_cmd(parts, pipes, envp);
	close(pipes[1]);
	close(pipes[0]);
	wait_for_death(parts);
}
