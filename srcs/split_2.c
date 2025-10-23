#include "../header/minishell.h"

static int	is_in(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
		if (c == base[i])
			return (1);
	return (0);
}

static int	count(char *str, char *charset)
{
	int		len_sub;
	int		len_sep;
	int		i;

	len_sub = 0;
	len_sep = 0;
	i = 0;
	while (str[len_sub + len_sep])
	{
		while (is_in(str[len_sub + len_sep], charset)
			&& str[len_sub + len_sep])
			len_sep++;
		if (!is_in(str[len_sub + len_sep], charset)
			&& str[len_sub + len_sep])
			i++;
		while (!is_in(str[len_sub + len_sep], charset)
			&& str[len_sub + len_sep])
			len_sub++;
	}
	return (i);
}

static char	*skip(char *str, char *charset, int *len)
{
	int	i;

	i = -1;
	*len = 0;
	while (is_in(*str, charset) && *str)
		str++;
	while (!is_in(str[++i], charset) && str[i])
		*len = *len + 1;
	return (str);
}

static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = -1;
	while (src[++i] != '\0' && i < n)
		dest[i] = src[i];
	i--;
	while (++i < n)
		dest[i] = '\0';
	return (dest);
}

char	**split_2(char *str, char *charset)
{
	char	**out;
	int		i;
	char	*tmp;
	int		len;

	if (!str)
	{
		out = (char **)malloc(1 * sizeof(char *));
		out[0] = NULL;
		return (out);
	}
	out = (char **)malloc((count(str, charset) + 1) * sizeof(char *));
	i = -1;
	tmp = str;
	len = 0;
	while (++i < count(str, charset))
	{
		tmp = skip(&tmp[len], charset, &len);
		out[i] = (char *)malloc((len + 1) * sizeof(char));
		ft_strncpy(out[i], tmp, len);
	}
	out[i] = NULL;
	return (out);
}