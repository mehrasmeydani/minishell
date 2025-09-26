#include "../header/minishell.h"

char	**ft_duostrdup(char **in, ssize_t len)
{
	ssize_t	i;
	char	**out;

	out = (char **)calloc(len + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
			return (ft_free(out));
	}
	return (out);
}
