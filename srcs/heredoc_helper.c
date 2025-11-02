#include "../header/minishell.h"

int	heredoc_eof(t_redirect *tmp)
{
	if (tmp->input)
	{
		tmp->input = ft_relocat(tmp->input, "\n");
		if (!tmp->input)
			return (0);
	}
	return (ft_putendl_fd("Warning: EOF!", 2),
		free(tmp->name), tmp->name = NULL, -1);
}
