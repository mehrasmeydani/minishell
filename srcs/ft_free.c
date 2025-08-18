#include "../header/minishell.h"

char	**ft_free(char **in, ssize_t i)
{
	ssize_t	j;

	j = -1;
	while (++j < i)
		free(in[j]);
	free(in);
	return (NULL);
}

size_t	ft_str_str_len(char **in)
{
	size_t	i;

	i = 0;
	while (in[i])
		i++;
	return (i);
}
