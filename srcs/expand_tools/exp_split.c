#include "../../header/minishell.h"

int	is_valid_env(char c, int j)
{
	return (ft_isalpha(c) || c == '_' || (ft_isdigit(c) && j != 1 ));
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
			if (j == 1 && in[j + i] == '?')
				j++;
			else
				while (in[i + j] && is_valid_env(in[i + j], j))
					j++;
			i += j;
		}
		else
			while (in[i] && in[i] != '\'' && in[i] != '"' && in[i] != '$')
				i++;
		num++;
	}
	return (num);
}

char	*str(char **in)
{
	ssize_t	i;
	ssize_t	j;
	char	*out;
	int		quotes_status;
	int		prev_status;

	i = 0;
	prev_status = 0;
	quotes_status = 0;
	quotes2((*in)[i], &quotes_status);
	if (prev_status != quotes_status)
	{
		prev_status = quotes_status;
		while ((*in)[i] && prev_status == quotes_status)
		{
			i++;
			quotes2((*in)[i], &quotes_status);
		}
		prev_status = quotes_status;
		if ((*in)[i])
			i++;
	}
	else if ((*in)[i] == '$')
	{
		j = 1;
		if (j == 1 && (*in)[i + j] == '?')
			j++;
		else
			while ((*in)[i + j] && is_valid_env((*in)[i + j], j))
				j++;
		i += j;
	}
	else
		while ((*in)[i] && (*in)[i] != '\'' && (*in)[i] != '"' && (*in)[i] != '$')
			i++;
	out = ft_substr(*in, 0, i);
	*in = *in + i;
	return (out);
}

char	**exp_split(char *in)
{
	char	**out;
	ssize_t	num;
	ssize_t	i;

	num	= count(in);
	out = ft_calloc(num + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		out[i] = str(&in);
		if (!out[i])
			return (ft_free(out));
	}
	return (out);
}
