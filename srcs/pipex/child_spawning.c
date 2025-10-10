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



void	fill_file_fd(t_redirect *head)
{
	t_redirect	*temp;

	temp = head;
	while(temp != NULL)
	{
		temp->fd = -1;
		temp = temp->next;
	}
}

int	fill_struct(t_exec *exec, t_minishell *mini)
{
	size_t	i;

	i = -1;
	exec->status = 1;
	fill_file_fd(mini->lex->redic);
	exec->pathlist = get_path_array(mini->env.var_pass_to_exec);
	if (!exec->pathlist)
		return (perror("paths not retrieved"), -1);
	exec->children_count = count_cmds(mini->lex);
	exec->pids = malloc(exec->children_count * sizeof(pid_t));
	if (!exec->pids)
		return(perror("pid allocation"), freepaths(exec->pathlist), 
		exec->pathlist = NULL, -1);
	while (++i < exec->children_count)
		exec->pids[i] = -1;
 	exec->pipe[0][0] = -1;
	exec->pipe[0][1] = -1;
	exec->pipe[1][0] = -1;
	exec->pipe[1][1] = -1;
	//ft_memset(&(exec->pipe), -1, sizeof(int[2][2]));
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
			return (exit(127));
		exit(0); // free mehras
	}
	tmp = check_against_cmd(cmd, exec->pathlist);
	if (!tmp)
		close_exit(exec, mini, "Arg[0]", 1);
	//free(mini->lex->cmd[0]);
	free(cmd->cmd[0]);
	cmd->cmd[0] = tmp;
	if (execve(cmd->cmd[0], cmd->cmd, mini->env.var_pass_to_exec) == -1)
		return (close(STDIN_FILENO), close(STDOUT_FILENO), 
			close_exit(exec, mini, "execution", 1));
}

void	set_exit_status(t_exec *exec, int status)
{
	if (WIFEXITED(status))
		exec->status = WEXITSTATUS(status);
	else
		exec->status = EXIT_FAILURE;
}
void	wait_for_death(t_exec *exec)
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
	set_exit_status(exec, status);
}
void	spawn_children(t_minishell *mini)
{
	size_t	i;
	t_exec	exec;
	t_redirect *current;

	if (fill_struct(&exec, mini) == -1)
		return ; // cleaned, all pids closed except for redirs
	if (exec.children_count == 1 && is_builtin(mini->lex->cmd)) // this check should also verify if its a builtin
		if (!exec_builtin(mini->lex->cmd, mini))
			return ; // free_and_seterror mehras
	i = -1;
	while(++i < exec.children_count)
	{
		current = mini->lex->redic;
		if (pipe(exec.pipe[i % 2]) < 0)
			return (perror("pipe"), wait_for_death(&exec));
		if ((exec.pids[i] = fork()) == -1)
			return (perror("fork"), wait_for_death(&exec));// i should also wait here for all the previous commands!
		if (exec.pids[i] == 0)
			executor(mini, &exec, i, current);
		my_pipe_dup_close(&exec, i);
		//current = current->next; // shouldnt be a problem with currenty being NULL because of incrementation
	}
	wait_for_death(&exec);
	//freeing
	//closing pipes
}

