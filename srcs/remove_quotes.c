#include "../header/minishell.h"

void	remove_quotes_3(char *str)
{
	ssize_t	i;

	i = -1;
	while (str[++i] && str[i + 1])
	{
		ft_swap(&(str[i]), &(str[i + 1]));
	}
	str[i - 1] = 0;
}

static ssize_t	count(char *in)
{
	ssize_t	i;
	ssize_t	j;
	int		quotes_status;

	i = 0;
	quotes_status = 0;
	j = 0;
	while (in[i + j])
	{
		if (quotes(in[i + j], &quotes_status) && quotes_status)
		{
			j++;
			while (quotes(in[i + j], &quotes_status) && quotes_status)
				i++;
			j++;
			continue ;
		}
		i++;
	}
	return (i);
}

static char	*str(char *in, ssize_t i, int quotes_status)
{
	ssize_t	j;
	char	*tmp;

	tmp = ft_calloc(i + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (in[i + j])
	{
		if (quotes(in[i + j], &quotes_status) && quotes_status)
		{
			j++;
			while (quotes(in[i + j], &quotes_status) && quotes_status)
			{
				tmp[i] = in[j + i];
				i++;
			}
			j++;
			continue ;
		}
		tmp[i] = in[j + i];
		i++;
	}
	return (tmp);
}

int	remove_quotes_2(char **in)
{
	char	*tmp;
	ssize_t	len;

	len = count(*in);
	tmp = str(*in, len, 0);
	if (!tmp)
		return (0);
	free (*in);
	*in = tmp;
	return (1);
}

int	remove_quotes(char **in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		if (!remove_quotes_2(&in[i]))
			return (0);
	return (1);
}
