#include "../../header/execution.h"
#include "../../header/minishell.h"

static size_t	count_cmds(t_lex *lex)
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

static void	fill_file_fd(t_lex *head)
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

int	fill_struct(t_exec *exec, t_minishell *mini)
{
	size_t	i;
	bool	isemptypath;

	i = -1;
	isemptypath = false;
	exec->status = 1;
	fill_file_fd(mini->lex);
	exec->children_count = count_cmds(mini->lex);
	if (back_up_standardfds(exec, mini->lex) == -1)
		return (perror("backup stdin/out"), -1);
	exec->pathlist = get_path_array(mini->env.raw_var, &isemptypath);
	if (!exec->pathlist && isemptypath == false)
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


