#include "../header/minishell.h"

static ssize_t	count(t_lex *lex, const char *str, char c)
{
	size_t	j;
	ssize_t	i;

	j = 0;
	i = 0;
	while (str[j])
	{
		while ((str[j] && quotes(str[j], &lex->open_quotes) && str[j] == c) || lex->open_quotes)
			j++;
		printf("%zd\t%c\t%zd\n", lex->open_quotes, str[j]);
		if (str[j] && !(str[j] == c))
			i++;
		while (str[j] && !(str[j] == c))
			j++;
	}
	return (i);
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

static char	*str(t_lex *lex, char *s, char c)
{
	ssize_t	i;
	char	*out;

	i = -1;
	while ((s[++i] && quotes(s[i], &lex->open_quotes) && s[i] != c) || lex->open_quotes)
		;
	out = ft_substr(s, 0, i);
	if (!out)
		return (NULL);
	return (out);
}

char	**mini_split(t_lex *lex, char *in, char c)
{
	char	**out;
	char	*tmp;
	ssize_t	i;
	ssize_t	num;

	i = -1;
	num = count(lex, in, c);
	if (!in)
		return (NULL);
	out = (char **)malloc((num + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	//printf("%zd\n", lex->open_quotes);
	tmp = (char *)in;
	while (++i < num)
	{
		while (*tmp && *tmp == c)
			tmp++;
		out[i] = str(lex, tmp, c);
		if (!out[i])
			return (ft_free(out, i));
		while (*tmp && *tmp != c)
			tmp++;
	}
	out[i] = NULL;
	return (out);
}
