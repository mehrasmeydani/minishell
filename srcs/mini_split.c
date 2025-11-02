/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:46:24 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:46:25 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	state_set(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c || (ft_iswhitespace(str[i]) && ft_iswhitespace(c)))
			return (i + 3);
	return (-1);
}

static void	skip(char **str, ssize_t *i)
{
	int	state;
	int	prev_state;
	int	quotes_stat;

	quotes_stat = 0;
	while (ft_iswhitespace((*str)[(*i)]))
		(*str)++;
	state = state_set((*str)[(*i)], "<|> ");
	prev_state = state;
	while ((*str)[(*i)] && state == prev_state)
	{
		quotes((*str)[(*i)], &quotes_stat);
		if (state == -1 && (quotes_stat == DOUBLE || quotes_stat == SINGLE)
			&& ++(*i))
			while ((*str)[(*i)] && quotes((*str)[(*i)], &quotes_stat)
				&& quotes_stat)
				(*i)++;
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
		while (ft_iswhitespace(str[i]))
			str++;
		tokens++;
	}
	return (tokens);
}

static char	*str(char **str)
{
	ssize_t	i;
	char	*out;

	i = 0;
	skip(str, &i);
	out = ft_substr(*str, 0, i);
	if (!out)
		return (NULL);
	*str = *str + i;
	return (out);
}

char	**mini_split(char *in)
{
	ssize_t	i;
	char	**out;
	ssize_t	num;

	num = count(in);
	out = (char **)ft_calloc(num + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < num)
	{
		out[i] = str(&in);
		if (!out[i])
			return (ft_free(out));
	}
	return (out);
}
