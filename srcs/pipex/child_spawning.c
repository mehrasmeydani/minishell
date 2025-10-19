#include "../../header/execution.h"

size_t	count_cmds(t_lex *lex) // is this really needed? why not pipes + 1?
{
	t_lex *temp;
	size_t	i;

	temp = lex;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}


void	fill_file_fd(t_lex *head)
{
	t_redirect	*temp;

	temp = head->redic;
	while(head != NULL)
	{
		temp = head->redic;
		while (temp != NULL)
		{
			temp->fd = -1;
			temp = temp->next;
		}
		head = head->next;
	}
}

void	safe_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void close_backups(t_exec *exec)
{
	safe_close_fd(&(exec->backup_stdin));
	safe_close_fd(&(exec->backup_stdout));
}

int	backup_needed(t_exec *exec, char **cmd)
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
		if (exec->backup_stdin == -1 && 
			(temp->level == HEREDOC || temp->level == INFILE))
		{
			exec->backup_stdin = dup(STDIN_FILENO);
			if (exec->backup_stdin == -1)
				return (close_backups(exec), -1);
		}
		else if (exec->backup_stdout == -1 &&
			(temp->level == OUTFILE || temp->level == APPEND))
		{
			exec->backup_stdout = dup(STDOUT_FILENO);
			if (exec->backup_stdout == -1)
				return (close_backups(exec), -1);
		}
		temp = temp->next;
	}
	return (1);
}



int	fill_struct(t_exec *exec, t_minishell *mini)
{
	size_t	i;

	i = -1;
	exec->status = 1;
	fill_file_fd(mini->lex);
	exec->children_count = count_cmds(mini->lex);
	if (back_up_standardfds(exec, mini->lex) == -1)
		return (perror("backup stdin/out"), -1);
	exec->pathlist = get_path_array(mini->env.raw_var);
	if (!exec->pathlist)
		return (perror("paths not retrieved"), close_backups(exec), -1);
	exec->pids = malloc(exec->children_count * sizeof(pid_t));
	if (!exec->pids)
		return(perror("pid allocation"), freepaths(exec->pathlist), 
			exec->pathlist = NULL, close_backups(exec), -1);
	while (++i < exec->children_count)
		exec->pids[i] = -1;
 	exec->pipe[0][0] = -1;
	exec->pipe[0][1] = -1;
	exec->pipe[1][0] = -1;
	exec->pipe[1][1] = -1;
	return (1);
}


void	close_all_pipes(int pipes[2][2])
{
	safe_close_fd(&pipes[0][0]);
	safe_close_fd(&pipes[0][1]);
	safe_close_fd(&pipes[1][0]);
	safe_close_fd(&pipes[1][1]);
}
/*
UNUSED: Redirs are closed on duping.
void	close_redirs(t_lex *cmds)
{
	t_redirect	*redir;
	
	while (cmds != NULL)
	{
		redir = cmds->redic;
		while (redir != NULL)
		{
			if (redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cmds = cmds->next;
	}

}
*/
void	close_exit(t_exec *exec, t_minishell *mini, char *errorstr, int ex_code)
{
	(void) mini;
	freepaths(exec->pathlist);
	exec->pathlist = NULL;
	close_all_pipes(exec->pipe);
	if (errorstr != NULL) // null when no error, pass a str for error.
		perror(errorstr);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	lex_clear(&(mini->lex), ft_free);
	free_env(&mini->env);
	free(exec->pids);
	exit(ex_code);
}

void my_pipe_dup(t_minishell *mini, t_exec *exec, size_t i)
{
	if (i > 0)
	{
		if (dup2(exec->pipe[(i - 1) % 2][0], STDIN_FILENO) == -1) // if not first command, previous command to STDIN.
			close_exit(exec, mini, "dup STDIN", 1);
	}
	if (i < exec->children_count - 1)
	{
		if (dup2(exec->pipe[i % 2][1], STDOUT_FILENO) == -1) // if not last command, current to to out.
				close_exit(exec, mini, "dup STDOUT", 1);
	}
}

void	my_pipe_dup_close(t_exec *exec, size_t i)
{	
	if (i > 0)
		safe_close_fd(&exec->pipe[(i - 1) % 2][0]);
	if (i < exec->children_count - 1)
		safe_close_fd(&exec->pipe[i % 2][1]);
}

t_lex	*find_current_cmd(t_lex *head, size_t pos)
{
	size_t	i;
	t_lex	*temp;

	temp = head;
	i = -1;
	while(++i < pos)
		temp = temp->next;
	return (temp);
}

void	executor(t_minishell *mini, t_exec *exec, size_t i, t_redirect *cur)
{
	t_lex	*cmd;
	char	*tmp;

	
	cmd = find_current_cmd(mini->lex, i);
	cur = cmd->redic;
	my_pipe_dup(mini, exec, i);
	close_all_pipes(exec->pipe);
	if (redirect_and_filecheck(cur) == -1)
		close_exit(exec, mini, NULL, 1);
	if (is_builtin(cmd->cmd))
	{
		if (!exec_builtin(cmd->cmd, mini))
		{
			if (exec->children_count > 1)
				return (close_exit(exec, mini, "builtin", 127));
			else
				return ((void)(mini->error_code = 127));
		}
		if (exec->children_count > 1)
			close_exit(exec, mini, NULL, 0); // freed everything from exec, missing free of stuff
		return ((void)(mini->error_code = 0));
	}
	tmp = check_against_cmd(cmd, exec->pathlist);
	if (!tmp)
		close_exit(exec, mini, cmd->cmd[0], 1);
	freepaths(exec->pathlist); // paths are freed if alloc failure
	exec->pathlist = NULL;
	free(cmd->cmd[0]);
	cmd->cmd[0] = tmp;
	free(exec->pids);
	if (execve(cmd->cmd[0], cmd->cmd, mini->env.var_pass_to_exec) == -1)
		return (close_exit(exec, mini, "execution", 1));
}

void	set_exit_status(t_minishell *mini, int status)
{
	if (WIFEXITED(status))
		mini->error_code = WEXITSTATUS(status);
	else
		mini->error_code = EXIT_FAILURE;
}
void	wait_for_death(t_minishell *mini, t_exec *exec)
{
	size_t	i;
	int status;

	status = 0;
	i = -1;
	while(++i < exec->children_count)
	{
		if (exec->pids[i] != -1)
			waitpid(exec->pids[i], &status, 0);
	}
	set_exit_status(mini, status);
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
void	clean_after_exec(t_exec *exec, t_minishell *mini, char *errormsg)
{
	(void) mini;
	close_all_pipes(exec->pipe);
	free(exec->pids);
	exec->pids = NULL;
	freepaths(exec->pathlist);
	exec->pathlist = NULL;
	if (errormsg != NULL)
		perror(errormsg);
	restore_stdin_stdout(exec);
}
void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec	exec;
	t_redirect *current;
	t_lex	*cmd;

	if (fill_struct(&exec, mini) == -1)
		return ;
	i = -1;
	while(++i < exec.children_count)
	{
		cmd = find_current_cmd(mini->lex, i);
		expand_all(mini, cmd);
		remove_quotes(cmd->cmd);
		exec.pids[i] = -2;
		current = mini->lex->redic;
		if (pipe(exec.pipe[i % 2]) < 0)
			return (clean_after_exec(&exec, mini, "pipe"), 
			wait_for_death(mini, &exec));
		if (exec.children_count != 1 || !is_builtin(mini->lex->cmd))
			if ((exec.pids[i] = fork()) == -1)
				return (clean_after_exec(&exec, mini, "fork"),
				wait_for_death(mini, &exec));// i should also wait here for all the previous commands!
		if (exec.pids[i] == 0 || exec.pids[i] == -2)
			executor(mini, &exec, i, current);
		my_pipe_dup_close(&exec, i);
	}
	if (exec.children_count != 1 || !is_builtin(mini->lex->cmd))
		wait_for_death(mini, &exec);
	clean_after_exec(&exec,mini, NULL);
}

