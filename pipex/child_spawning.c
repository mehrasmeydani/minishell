#include "execution.h"
size_t	count_cmds(t_lex *lex) // is this really needed? why not pipes + 1?
{
	t_lex *temp;
	size_t	i;

	temp = lex;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}






int	fill_struct(t_exec *exec, t_minishell *mini)
{
	exec->pathlist = get_path_array(mini->env.var_pass_to_exec);
	if (!exec->pathlist)
	{
		/*close(exec->pipes[0]);
		close(exec->pipes[1]);*/
		return (perror("paths not retrieved"), -1);
	}
	exec->children_count = count_cmds(mini->lex);
	exec->pids = ft_calloc(exec->children_count, sizeof(pid_t));
	if (!exec->pids)
	{
		/*close(exec->pipes[0]);
		close(exec->pipes[1]);*/
		return(perror("pid allocation"), freepaths(exec->pathlist),
			exec->pathlist = NULL, -1);
	}
	exec->pipe[0][0] = -1;
	exec->pipe[0][1] = -1;
	exec->pipe[1][0] = -1;
	exec->pipe[1][1] = -1;
	return (1);
}


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

void	close_exit(t_exec *exec, t_minishell *mini, char *errorstr, int ex_code)
{
	(void) mini; // placeholder so i can free ministuff after
	freepaths(exec->pathlist);
	close_all_pipes(exec->pipe);
	if (errorstr != NULL) // null when no error, pass a str for error.
		perror(errorstr);
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
void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec	exec;

	if (fill_struct(&exec, mini) == -1)
		return ; // cleaned, all pids closed
	if (exec.children_count == 1) // this check should also verify if its a builtin
		perror("single command logic with builtin is not here yet, but must be implemented");
	i = -1;
	while(++i < exec.children_count)
	{
		if (pipe(exec.pipe[i % 2]) < 0)
			return (perror("pipe"));
		if ((exec.pids[i] = fork()) == -1)
			return (perror("fork")); // i should also wait here for all the previous commands!
		if (exec.pids[i] == 0)
		{
			my_pipe_dup(mini, &exec, i);
			close_all_pipes(exec.pipe);
			// redirections
			// exec
			// maybe a single function?
		}
		my_pipe_dup_close(&exec, i);
	}
	//waiting
	//freeing
	//closing pipes
}

