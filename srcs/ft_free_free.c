#include "../header/minishell.h"

int	has_quotes(char *in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		if (in[i] == '\'' || in[i] == '"')
			return (1);
	return (0);
}

void	ft_free_free(char ***str)
{
	ssize_t	i;

	i = -1;
	while (str[++i])
	{
		ft_free(str[i]);
	}
	free (str);
}
