#include "../../header/minishell.h"

static void	end_builtin(t_exec *exec, t_minishell *mini, char *cmd)
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
	return ((void)(mini->error_code = 0));
}
