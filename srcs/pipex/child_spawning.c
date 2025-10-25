#include "../../header/execution.h"

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
		return(exit_or_return(exec, mini, NULL, 2));
	if (is_builtin(cmd->cmd))
	{
		if (!exec_builtin(cmd->cmd, mini, exec))
		{
			if (exec->children_count > 1)
				return (close_exit(exec, mini, cmd->cmd[0], 1));
			else
				return ((void)(perror(cmd->cmd[0]), mini->error_code = 1));
		}
		if (exec->children_count > 1)
			close_exit(exec, mini, NULL, 0);
		return ((void)(mini->error_code = 0));
	}
	tmp = check_against_cmd(cmd, exec->pathlist, &mini->error_code);
	if (!tmp)
		close_exit(exec, mini, cmd->cmd[0], mini->error_code);
	freepaths(exec->pathlist);
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

void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec		exec;
	t_redirect	*current;
	//t_lex	*cmd;

	if (fill_struct(&exec, mini) == -1)
		return ;
	i = -1;
	while(++i < exec.children_count)
	{
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
	clean_after_exec(&exec, mini, NULL);
}

