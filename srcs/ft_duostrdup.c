/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duostrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:47 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:47 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_duostrdup(char **in, ssize_t len)
{
	ssize_t	i;
	char	**out;

	out = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (in[++i] && i < len)
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
			return (ft_free(out));
	}
	return (out);
}
