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
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
	return (0);
}

int	exec_builtin(char **cmd, t_minishell *mini, t_exec *exec)
{
	if (exec->children_count != 1)
		signal(SIGPIPE, SIG_IGN);
	if (!cmd || !*cmd)
		return (0);
	if (!ft_strcmp(cmd[0], "env"))
		return (env(mini), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (builtin_exit(exec, mini, cmd), 1);
	if (!ft_strcmp(cmd[0], "export"))
		return (my_export(mini, cmd));
	if (!ft_strcmp(cmd[0], "echo"))
		return (echo(cmd), 1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (cd(mini, cmd));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (pwd());
	if (!ft_strcmp(cmd[0], "unset"))
		return (unset(mini, cmd));
	return (1);
}
