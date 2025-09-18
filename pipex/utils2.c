/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:47:18 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/06 13:02:18 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	newstr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (newstr == NULL)
		return (NULL);
	ft_strlcpy(newstr, s1, len1 + 1);
	ft_strlcpy(newstr + len1, s2, len2 + 1);
	return (newstr);
}

char	*partialjoin(const char *s1, const char *s2, int len2)
{
	char	*newstr;
	size_t	len1;

	if (len2 == 0)
		return (NULL);
	len1 = ft_strlen(s1);
	newstr = malloc((len1 + len2 + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, len1 + 1);
	ft_strlcpy(newstr + len1, s2, len2 + 1);
	return (newstr);
}
