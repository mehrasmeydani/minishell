#include "../header/minishell.h"

char	**ft_free(char **in)
{
	ssize_t	j;
	ssize_t	i;

	j = -1;
	i = ft_str_str_len(in);
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
