#include "../../header/minishell.h"

int	is_valid_env(char c, int j)
{
	return (ft_isalpha(c) || c == '_' || (ft_isdigit(c) && j != 1));
}

static ssize_t	count(char *in)
{
	ssize_t	i;
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
			count_helper(in, &i, &quotes_status, &prev_status);
		else if (in[i] == '$')
			count_helper2(in, &i);
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
	char	*out;
	int		quotes_status;
	int		prev_status;

	i = 0;
	prev_status = 0;
	quotes_status = 0;
	quotes2((*in)[i], &quotes_status);
	if (prev_status != quotes_status)
		str_helper1(in, &i, &quotes_status, &prev_status);
	else if ((*in)[i] == '$')
		str_helper2(in, &i);
	else
		while ((*in)[i] && (*in)[i] != '\''
			&& (*in)[i] != '"' && (*in)[i] != '$')
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

	num = count(in);
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
