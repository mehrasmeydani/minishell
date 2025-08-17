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
	ssize_t	j;
	int	state;
	int	quotes_state;
	int	prev_state;

	i = 0;
	quotes_state = 0;
	j = 0;
	while (str[i])
	{	
		quotes(str[i], &quotes_state);
		prev_state = state_set(str[i], ">|<", quotes_state);
		state = prev_state;
		while ((str[i] && quotes(str[i], &quotes_state) && state == prev_state) || quotes_state)
		{
			i++;
			state = state_set(str[i], ">|<", quotes_state);
		}
		printf("%c, %zd\n", str[i], i);
		j++;
	}
	printf("%zd\n", j);
	return (j);
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
