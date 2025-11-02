#include "../../header/minishell.h"

extern int g_signaln;

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

/*
int	run_builtin (t_minishell *mini, t_exec *exec, t_lex *cmd)
{
	if (is_builtin(cmd->cmd))
	{
		if (!exec_builtin(cmd->cmd, mini, exec))
		{
			if (exec->children_count > 1)
				return (close_exit(exec, mini, cmd->cmd[0], 1), 0);
			else
				return ((void)(perror(cmd->cmd[0]), mini->error_code = 1), 0);
		}
		if (exec->children_count > 1)
			close_exit(exec, mini, NULL, 0);
	}
		return (mini->error_code = 0, 1);

}
*/

void	execve_wrapper(char **cmd_args, t_minishell *mini, t_exec *exec)
{
	execve(cmd_args[0], cmd_args, mini->env.var_pass_to_exec);
	close_exit(exec, mini, "execution", 1);
}

void	end_builtin(t_exec *exec, t_minishell *mini, char *cmd) 
{
	if (exec->children_count > 1)
		return (close_exit(exec, mini, cmd, 1));
	else
		return ((void)(perror(cmd), mini->error_code = 1));
}

void	run_builtin(char **cmd_args, t_minishell *mini, t_exec *exec)
{
	if (!exec_builtin(cmd_args, mini, exec))
		return (end_builtin(exec, mini, cmd_args[0]));
	if (exec->children_count > 1)
		close_exit(exec, mini, NULL, 0);
	return((void)(mini->error_code = 0));
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
		return(exit_or_return(exec, mini, NULL, 1));
	if (is_builtin(cmd->cmd))
		return (run_builtin(cmd->cmd, mini, exec));
	signal(SIGQUIT, sig_handler_quit);
	tmp = check_against_cmd(cmd, exec->pathlist, &mini->error_code);
	if (!tmp)
		close_exit(exec, mini, cmd->cmd[0], mini->error_code);
	freepaths(exec->pathlist);
	exec->pathlist = NULL;
	free(cmd->cmd[0]);
	cmd->cmd[0] = tmp;
	free(exec->pids);
	exec->pids = NULL;
	execve_wrapper(cmd->cmd, mini, exec);
}

void	set_exit_status(t_minishell *mini, int status)
{
	if (WIFEXITED(status))
	{
		mini->error_code = WEXITSTATUS(status);
		g_signaln = 0;
	}
	else if (WIFSIGNALED(status))
	{
		mini->error_code = WTERMSIG(status) + 128;
		g_signaln = 0;
	}
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
		if (exec->pids[i] != -1 && exec->pids[i] != -2)
			waitpid(exec->pids[i], &status, 0);
	}
	set_exit_status(mini, status);
}

void	parent_post_child_cleanup(t_minishell *mini, t_exec *exec)
{
	signal(SIGQUIT, SIG_IGN);
	if (mini->lex->cmd[0] && !ft_strcmp(mini->lex->cmd[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	else
		signal(SIGINT, sig_handler_int_parent);
	if (exec->children_count != 1 || !is_builtin(mini->lex->cmd))
		wait_for_death(mini, exec);
	clean_after_exec(exec, mini, NULL);

}
void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec		exec;
	t_redirect	*current;

	if (fill_struct(&exec, mini) == -1)
		return ;
	i = -1;
	g_signaln = 0;
	while(++i < exec.children_count)
	{
		exec.pids[i] = -2;
		current = mini->lex->redic;
		if (pipe(exec.pipe[i % 2]) < 0)
			return (wait_for_death(mini, &exec),
		   clean_after_exec(&exec, mini, "pipe"));
		if (exec.children_count != 1 || !is_builtin(mini->lex->cmd))
			if ((exec.pids[i] = fork()) == -1)
				return (wait_for_death(mini, &exec),
				clean_after_exec(&exec, mini, "fork"));// i should also wait here for all the previous commands!
		if (exec.pids[i] == 0 || exec.pids[i] == -2)
			executor(mini, &exec, i, current);
		my_pipe_dup_close(&exec, i);
	}
	parent_post_child_cleanup(mini, &exec);
}

