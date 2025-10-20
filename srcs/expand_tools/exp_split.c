#include "../../header/minishell.h"

static int	is_valid_env(char c, int j)
{
	return (ft_isalpha(c) || c == '_' || (ft_isdigit(c) && j != 1));
}

static int	quotes2(char c, int *state)
{
	if (c == '"' && *state == DOUBLE)
		*state = 0;
	else if (c == '"' && *state != SINGLE && *state != DOUBLE)
		*state = DOUBLE;
	else if (c == '\'' && *state == SINGLE)
		*state = 0;
	else if (c == '\'' && *state != SINGLE && *state != DOUBLE)
		*state = SINGLE;
	return (0);
}

static ssize_t	count(char *in)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	num;
	int		quotes_status;
	int		prev_status;

	i = 0;
	prev_status = 0;
	quotes_status = 0;
	num = 0;
	while (in[i])
	{
		quotes2(in[i], &quotes_status);
		if (prev_status != quotes_status)
		{
			prev_status = quotes_status;
			while (in[i] && prev_status == quotes_status)
			{
				i++;
				quotes2(in[i], &quotes_status);
			}
			prev_status = quotes_status;
			if (in[i])
				i++;
		}
		else if (in[i] == '$')
		{
			j = 1;
			while (in[i + j] && is_valid_env(in[i + j], j))
				j++;
			i += j;
		}
		else
		{
			while (in[i] && in[i] != '\'' && in[i] != '"' && in[i] != '$')
				i++;
		}
		num++;
	}
	return (num);
}

char	**exp_split(char *in)
{
	//char	**out;
	ssize_t	num;

	num	= count(in);
	printf("%zd\n", num);
	return (NULL);
}
