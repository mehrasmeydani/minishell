#include "../../header/execution.h"

void	safe_close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void	close_all_pipes(int pipes[2][2])
{
	safe_close_fd(&pipes[0][0]);
	safe_close_fd(&pipes[0][1]);
	safe_close_fd(&pipes[1][0]);
	safe_close_fd(&pipes[1][1]);
}

void	close_exit(t_exec *exec, t_minishell *mini, char *error, int ex_code)
{
	freepaths(exec->pathlist);
	exec->pathlist = NULL;
	close_all_pipes(exec->pipe);
	if (error != NULL) // null when no error, pass a str for error.
		perror(error);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	lex_clear(&(mini->lex), ft_free);
	free_env(&mini->env);
	free(exec->pids);
	exit(ex_code);
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

void	exit_or_return(t_exec *exec, t_minishell *mini, char *error, int excd)
{
	if (is_builtin(mini->lex->cmd) && exec->children_count == 1)
	{
		mini->error_code = excd;
		return ;
	}
	else
		close_exit(exec, mini, error, excd);
}
