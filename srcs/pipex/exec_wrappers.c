/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:41:53 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:41:55 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
