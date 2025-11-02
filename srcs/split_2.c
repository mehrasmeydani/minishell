/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:46:42 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 18:52:40 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/expand.h"

static int	is_in2(char c, char *base)
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
		while (is_in2(str[len_sub + len_sep], charset)
			&& str[len_sub + len_sep])
			len_sep++;
		if (!is_in2(str[len_sub + len_sep], charset)
			&& str[len_sub + len_sep])
			i++;
		while (!is_in2(str[len_sub + len_sep], charset)
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
	while (is_in2(*str, charset) && *str)
		str++;
	while (!is_in2(str[++i], charset) && str[i])
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
		return ((char **)ft_calloc(1, sizeof(char *)));
	out = (char **)ft_calloc((count(str, charset) + 1), sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	tmp = str;
	len = 0;
	while (++i < count(str, charset))
	{
		tmp = skip(&tmp[len], charset, &len);
		out[i] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!out[i])
			return (ft_free(out));
		ft_strncpy(out[i], tmp, len);
	}
	return (out);
}
