#include "../../header/minishell.h"

int	my_export(t_minishell *mini, char **cmd)
{
	if (ft_str_str_len(cmd) > 1)
		return (add_var(mini, cmd));
	else
		print_export(mini);
	return (1);
}
