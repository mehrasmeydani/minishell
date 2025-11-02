#include "../../header/minishell.h"

void	execve_wrapper(char **cmd_args, t_minishell *mini, t_exec *exec)
{
	execve(cmd_args[0], cmd_args, mini->env.var_pass_to_exec);
	close_exit(exec, mini, "execution", 1);
}

int	fork_wrapper(t_exec *exec, size_t i)
{
	exec->pids[i] = fork();
	if (exec->pids[i] == -1)
		return (-1);
	return (1);
}
