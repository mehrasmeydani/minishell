/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:03:38 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/01 17:07:34 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

void	close_backups(t_exec *exec)
{
	safe_close_fd(&(exec->backup_stdin));
	safe_close_fd(&(exec->backup_stdout));
}

static int	backup_needed(t_exec *exec, char **cmd)
{
	exec->backup_stdin = -1;
	exec->backup_stdout = -1;
	if (exec->children_count != 1 || !is_builtin(cmd))
		return (0);
	return (1);
}

int	back_up_standardfds(t_exec *exec, t_lex *firstcmd)
{
	t_redirect	*temp;

	if (!backup_needed(exec, firstcmd->cmd))
		return (1);
	temp = firstcmd->redic;
	while (temp != NULL)
	{
		if (exec->backup_stdin == -1
			&& (temp->level == HEREDOC || temp->level == INFILE))
		{
			exec->backup_stdin = dup(STDIN_FILENO);
			if (exec->backup_stdin == -1)
				return (close_backups(exec), -1);
		}
		else if (exec->backup_stdout == -1
			&& (temp->level == OUTFILE || temp->level == APPEND))
		{
			exec->backup_stdout = dup(STDOUT_FILENO);
			if (exec->backup_stdout == -1)
				return (close_backups(exec), -1);
		}
		temp = temp->next;
	}
	return (1);
}

int	restore_stdin_stdout(t_exec *exec)
{
	if (exec->backup_stdin != -1)
	{
		if (dup2(exec->backup_stdin, STDIN_FILENO) == -1)
			return (perror("FATAL: error restoring STDIN"),
				close_backups(exec), -1);
	}
	if (exec->backup_stdout != -1)
	{
		if (dup2(exec->backup_stdout, STDOUT_FILENO) == -1)
			return (perror("FATAL: error restoring STDOUT"),
				close_backups(exec), -1);
	}
	close_backups(exec);
	return (1);
}
