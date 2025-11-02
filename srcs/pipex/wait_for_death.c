/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:42:27 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:42:28 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern int	g_signaln;

static void	set_exit_status(t_minishell *mini, int status)
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
	int		status;

	status = 0;
	i = -1;
	while (++i < exec->children_count)
	{
		if (exec->pids[i] != -1 && exec->pids[i] != -2)
			waitpid(exec->pids[i], &status, 0);
	}
	set_exit_status(mini, status);
}
