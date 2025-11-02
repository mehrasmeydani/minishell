/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:28 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:29 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_swap(char *a, char *b)
{
	char	why;

	why = *a;
	*a = *b;
	*b = why;
}

char	**expand_exp(t_minishell *mini, t_expands **exp)
{
	char		**out;

	out = NULL;
	if (!expand_sub(mini, exp))
		return (NULL);
	if (!exp_remove_quotes(*exp))
		return (NULL);
	if (!exp_reconnect(exp))
		return (NULL);
	out = ft_calloc(exp_len(*exp) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	exp_exp(*exp, out);
	return (out);
}

int	replace_command(t_lex *lex, char ***str)
{
	char	**tmp;
	ssize_t	i;
	ssize_t	j;
	ssize_t	k;

	i = -1;
	j = 0;
	while (str[++i])
		j += ft_str_str_len(str[i]);
	tmp = ft_calloc(j + 1, sizeof(char *));
	if (!tmp)
		return (0);
	i = -1;
	k = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			tmp[++k] = str[i][j];
		free(str[i]);
	}
	free(str);
	ft_free(lex->cmd);
	lex->cmd = tmp;
	return (1);
}

int	expand_tmp(t_minishell *mini, t_lex *lex, t_expand *exp)
{
	ssize_t	i;
	char	***str2;
	char	**str;

	i = -1;
	str2 = (char ***)ft_calloc(ft_str_str_len(lex->cmd) + 1, sizeof(char **));
	if (!str2)
		return (free_exp(exp), 0);
	while (lex->cmd[++i])
	{
		str = exp_split(lex->cmd[i]);
		if (!str)
			return (free(str2), free_exp(exp), 0);
		exp->exp[i] = create_exp(str);
		if (!exp->exp[i])
			return (ft_free(str), free(str2), free_exp(exp), 0);
		free(str);
		str2[i] = expand_exp(mini, &(exp->exp[i]));
		if (!str2[i])
			return (ft_free_free(str2), free_exp(exp), 0);
	}
	if (!replace_command(lex, str2))
		return (ft_free_free(str2), free_exp(exp), 0);
	return (1);
}

int	expand_all(t_minishell *mini)
{
	t_lex		*lex;
	t_expand	exp;
	ssize_t		i;

	lex = mini->lex;
	errno = 0;
	while (lex)
	{
		i = ft_str_str_len(lex->cmd);
		exp.exp = ft_calloc(i, sizeof(t_expands *));
		if (!exp.exp)
			return (0);
		exp.len = i;
		if (!expand_tmp(mini, lex, &exp))
			return (0);
		free_exp(&exp);
		if (!redirect_exp(mini, lex->redic))
			return (0);
		lex = lex->next;
	}
	return (1);
}
