#include "../header/minishell.h"

int	is_builtin(char **cmd)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "env"))
		return (1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd[0], "export"))
		return (1);
	return (0);
}

int		exec_builtin(char **cmd, t_minishell *mini)
{
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "env"))
		return (env(mini), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (exit(ft_atoi(cmd[1])), 1);
	if (!ft_strcmp(cmd[0], "export"))
		return (export(mini, cmd), 1);
	return (1);
}
