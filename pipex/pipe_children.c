/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:18:13 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/04 19:52:35 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void set_pipe(t_parts *parts, int *pipes, int cmd)
{
	if (cmd == CMD1)
	{
		if (dup2(parts->fdin, STDIN_FILENO) == -1)
			clean_children(parts, pipes, cmd);
		parts->fdin = CLOSED;
		if (dup2(pipes[1], STDOUT_FILENO) == -1)
			return(close(STDIN_FILENO), clean_children(parts, pipes, cmd));
	}
	else if (cmd == CMD2)
	{
				pipes[1] = CLOSED;
		parts->fdin = CLOSED;
		if (dup2(pipes[0], STDIN_FILENO) == -1)
			clean_children(parts, pipes, cmd);
		pipes[0] = CLOSED;
		if (dup2(parts->fdout, STDOUT_FILENO) == -1)
			return(close(STDIN_FILENO), clean_children(parts, pipes, cmd));
	}
}

static void wait_for_death(t_parts *parts)
{
	int	status1;
	int	status2;
	int use;

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

static void	execute_cmd(t_parts *parts, int *pipes, char **envp, int cmd)
{
	if (cmd == CMD1)
	{
		execve(parts->cmd1[0], parts->cmd1, envp);
		close(STDIN_FILENO); //fdin also closed now
		free_cmds(parts, ALLCMDS);
		clean_children(parts, pipes, cmd);
	}
	printf("exec");
	execve(parts->cmd2[0], parts->cmd2, envp);
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

void	first_cmd(t_parts *parts, int *pipes, char **envp)
{

	parts->pid1 = fork();
	if (parts->pid1 == -1)
		return(perror("fork CMD1"));
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
			return(perror("Fork CMD2"));
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
	if(pipe(pipes) == -1)
		return(perror("pipes"));
	if (parts->fdin != FAIL && parts->cmd1 != NULL)
		first_cmd(parts, pipes, envp);
	if (parts->fdout != FAIL && parts->cmd2 != NULL)
		second_cmd(parts, pipes, envp);
	close(pipes[1]);
	close(pipes[0]);
	wait_for_death(parts);
}


