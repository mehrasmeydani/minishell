#include "../../header/execution.h"

void my_pipe_dup(t_minishell *mini, t_exec *exec, size_t i)
{
	if (i > 0)
	{
		if (dup2(exec->pipe[(i - 1) % 2][0], STDIN_FILENO) == -1)
			close_exit(exec, mini, "dup STDIN", 1);
	}
	if (i < exec->children_count - 1)
	{
		if (dup2(exec->pipe[i % 2][1], STDOUT_FILENO) == -1)
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

