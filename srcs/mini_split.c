#include "../header/minishell.h"

int	state_set(char c, char *str, int quotes_state)
{
	int i;

	i = -1;
	if (quotes_state)
		return (quotes_state);
	while (str[++i])
		if (str[i] == c)
			return (i + 3);
	return (-1);
}

static ssize_t	count(const char *str)
{
	ssize_t	i;
	ssize_t	tokens;
	int	state;
	int	prev_state;
	int	quotes_state;

	i = 0;
	state = 0;
	tokens = 0;
	quotes_state = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		quotes(str[i], &quotes_state);
		if (quotes_state && ++i)
		{
			while (str[i] && quotes(str[i], &quotes_state) && quotes_state)
				i++;
			i++;
		}
		else
		{
			state = state_set(str[i], "<|> ", quotes_state);
			prev_state = state;
			while (str[i] && state == prev_state)
				state = state_set(str[++i], "<|> ", quotes_state);
		}
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

// static char	*str(char *s)
// {
// }

char	**mini_split(char *in)
{
	//ssize_t	i;
	char	**out;
	ssize_t	num;

	num = count(in);
	out = (char **)calloc(num + 1, sizeof(char *));
	ft_free(out, 0);
	return (NULL);
}
