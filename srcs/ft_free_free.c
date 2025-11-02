/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:54 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:55 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	has_quotes(char *in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		if (in[i] == '\'' || in[i] == '"')
			return (1);
	return (0);
}

void	ft_free_free(char ***str)
{
	ssize_t	i;

	i = -1;
	while (str[++i])
	{
		ft_free(str[i]);
	}
	free (str);
}
