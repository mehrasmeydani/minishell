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


void	rig_child(t_minishell *mini, size_t current_cmd, int *pipes, pid_t pid)
{
	static int prev_rd_end = -1;

	if (pid == -1)
		return (perror("fork"));
	if (pid > 0)
	{
		if (i != 0)
			close(prev_rd_end);
		close[]
	}


}

void	clean_pipes(t_exec *exec, ssize_t num_pipes)
{

}
int	create_pipes(t_exec *exec, t_minishell *mini)
{
	ssize_t	i;

	i = -1;

	exec->pipes = ft_calloc(mini->num_pipes - 1, sizeof(int *));
	if (!exec->pipes)
		return(perror("pipes"), -1);
	while(++i < mini->num_pipes - 1)
	{
		exec->pipes[i] = ft_calloc(2 * sizeof(int));
		if (exec->pipes[i] == NULL)
			return(perror("pipes"), -1);
	}
}
int	fill_struct(t_exec *exec, t_minishell *mini)
{
	//prob this would be in the while loop, actually
/*	if(pipe(exec->pipes) == -1)
		return(perror("initial pipe"), -1); */
	//so i can open pipes on the fly
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
	return (1);
}


void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec	exec;
	int		prevrd;

	if (fill_struct(&exec, mini) == -1)
		return ; // cleaned, all pids closed
	if (exec.children_count == 1) // this check should also verify if its a builtin
		return (perror("single command logic with is not here yet, but must be implemented"));
	i = -1;
	while(++i < exec.children_count)
	{
		if (pipe(exec.pipes) < 0)
			return (perror("pipe")); // fds should be closed
		prevrd = exec.pipes[0];
	
		exec.pids[i] = fork();
		// rig child here to set the rolling pipe correctly
		if (exec.pids[i] == 0)
		{
			// pipe correctly
			// redirections
			// exec
			// maybe a single function?
		}
		if (exec.pids[i] == -1)
			perror("fork"); // not returning so waiting is possible
	}
	//waiting
	//freeing
}

