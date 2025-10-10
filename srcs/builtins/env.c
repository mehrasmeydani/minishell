#include "../../header/minishell.h"

void	env(t_minishell *mini)
{
	ssize_t	i;

	i = -1;
	while (mini->env.raw_var[++i])
		if (mini->env.var_value[i])
			ft_putendl_fd(mini->env.raw_var[i], STDOUT_FILENO);
}
