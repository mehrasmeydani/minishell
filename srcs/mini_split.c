#include "../header/minishell.h"

int	state_set(char c, char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 3);
	return (-1);
}

static void	skip(char **str, ssize_t *i)
{
	int	state;
	int	prev_state;

	state = 0;
	while ((*str)[(*i)] == ' ')
			(*str)++;
	quotes((*str)[(*i)], &state);
	if ((state == DOUBLE || state == SINGLE) && ++(*i))
	{
		while ((*str)[(*i)] && quotes((*str)[(*i)], &state) && state)
			(*i)++;
		(*i)++;
	}
	else
	{
		state = state_set((*str)[(*i)], "<|> ");
		prev_state = state;
		while ((*str)[(*i)] && state == prev_state)
			state = state_set((*str)[++(*i)], "<|> ");
	}
}

static ssize_t	count(char *str)
{
	ssize_t	i;
	ssize_t	tokens;

	i = 0;
	tokens = 0;
	while (str[i])
	{
		skip(&str, &i);
		tokens++;
	}
	return (tokens);
}

static char	**ft_free(char **in, ssize_t i)
{
	ssize_t	j;

	j = -1;
	while (++j < i)
		free(in[j]);
	free(in);
	return (NULL);
}

static char	*str(char **str)
{
	ssize_t	i;
	char	*out;

	i = 0;
	skip(str, &i);
	out = ft_substr(*str, 0, i);
	*str = *str + i;
	return (out);
}

char	**mini_split(char *in)
{
	ssize_t	i;
	char	**out;
	ssize_t	num;

	num = count(in);
	out = (char **)calloc(num + 1, sizeof(char *));
	i = -1;
	while (++i < num)
	{
		out[i] = str(&in);
		if (!out[i])
			return (ft_free(out, 0));
	}
	return (out);
}
