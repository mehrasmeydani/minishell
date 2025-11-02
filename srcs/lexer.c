/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:46:10 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:46:10 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static t_lex	*lex_pipes(char **in, ssize_t i)
{
	t_lex	*out;
	t_lex	*tmp;
	char	**cmd;

	i = 0;
	out = NULL;
	while (in[i])
	{
		while (in[i] && in[i][0] != '|')
			i++;
		cmd = ft_duostrdup(in, i);
		if (!cmd)
			return (lex_clear(&out, ft_free), NULL);
		tmp = lex_new(cmd);
		if (!tmp)
			return (lex_clear(&out, ft_free)
				, ft_free(cmd), NULL);
		lex_addback(&out, tmp);
		if (in[i])
		{
			in = &in[i + 1];
			i = 0;
		}
	}
	return (out);
}

int	clean_rest(t_lex *lex)
{
	t_lex	*tmp;
	ssize_t	str_len;
	char	**tmp_str;

	tmp = lex;
	while (tmp)
	{
		str_len = clean_rest_helper(tmp);
		tmp_str = (char **)ft_calloc(str_len + 1, sizeof(char *));
		if (!tmp_str)
			return (0);
		if (!clean_rest_helper2(tmp, tmp_str))
			return (0);
		ft_free(tmp->cmd);
		tmp->cmd = tmp_str;
		tmp = tmp->next;
	}
	return (1);
}

t_lex	*lex_redir(t_lex *lex)
{
	t_lex		*tmp;
	ssize_t		i;

	tmp = lex;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			if (tmp->cmd[i][0] == '<' || tmp->cmd[i][0] == '>')
				if (!lex_redir_helper(lex, tmp, i))
					return (NULL);
		}
		tmp = tmp->next;
	}
	if (!clean_rest(lex))
		return (lex_clear(&lex, ft_free), NULL);
	return (lex);
}

t_lex	*lexer(char **in)
{
	t_lex	*out;

	out = lex_pipes(in, 0);
	if (!out)
		return (NULL);
	(void)out;
	out = lex_redir(out);
	if (!out)
		return (NULL);
	return (out);
}
