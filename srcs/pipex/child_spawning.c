/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_spawning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:41:16 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:41:19 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern volatile sig_atomic_t	g_signaln;

t_lex	*find_current_cmd(t_lex *head, size_t pos)
{
	size_t	i;
	t_lex	*temp;

	temp = head;
	i = -1;
	while (++i < pos)
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
		return (exit_or_return(exec, mini, NULL, 1));
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

void	parent_post_child_cleanup(t_minishell *mini, t_exec *exec)
{
	signal(SIGQUIT, SIG_IGN);
	if (mini->lex->cmd[0] && !ft_strcmp(mini->lex->cmd[0], "./minishell"))
		signal(SIGINT, SIG_IGN);
	if (exec->children_count != 1 || !is_builtin(mini->lex->cmd))
		wait_for_death(mini, exec);
	clean_after_exec(exec, mini, NULL);
}

void	spawn_children(t_minishell *mini)
{
	size_t		i;
	t_exec		exec;
	t_redirect	*current;

	if (fill_struct(&exec, mini) == -1)
		return ;
	i = -1;
	g_signaln = 0;
	while (++i < exec.children_count)
	{
		exec.pids[i] = -2;
		current = mini->lex->redic;
		if (pipe(exec.pipe[i % 2]) < 0)
			return (wait_for_death(mini, &exec),
				clean_after_exec(&exec, mini, "pipe"));
		if (exec.children_count != 1 || !is_builtin(mini->lex->cmd))
			if (fork_wrapper(&exec, i) == -1)
				return (wait_for_death(mini, &exec),
					clean_after_exec(&exec, mini, "fork"));
		if (exec.pids[i] == 0 || exec.pids[i] == -2)
			executor(mini, &exec, i, current);
		my_pipe_dup_close(&exec, i);
	}
	parent_post_child_cleanup(mini, &exec);
}
