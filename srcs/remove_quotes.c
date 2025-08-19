#include "../header/minishell.h"

int	remove_quotes(char **in)
{
	ssize_t	i;
	ssize_t	j;
	char	*tmp;
	char	*tmp_2;
	int		quotes_status;

	i = 0;
	quotes_status = 0;
	j = 0;
	tmp_2 = NULL;
	while ((*in)[i + j])
	{
		j = 0;
		while (quotes((*in)[i + j], &quotes_status) && quotes_status)
			j++;
		if (j)
		{
			tmp = ft_substr((*in), i + 1, j - 1);
			if (!tmp)
				return (0);
			tmp_2 = ft_strjoin(tmp, &(*in)[i + j + 1]); //fix
			if (!tmp_2)
				return (free(tmp), 0);
			*in = tmp_2;
			free(tmp);
			i = 0;
			continue;
		}
		i++;
	}
	return (1);
}
