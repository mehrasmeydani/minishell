#include "../../header/minishell.h"

int	is_in(char *str, char *set)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	while (str && str[++i])
	{
		j = -1;
		while (set && set[++j])
			if (str[i] == set[j])
				return (1);
	}
	return (0);
}

int	reconnect_helper(t_expands *tmp, t_expands *exp)
{
	while (tmp)
	{
		if (exp->after_space || tmp->behind_space)
			exp = tmp;
		else
		{
			exp->str = ft_relocat(exp->str, tmp->str);
			if (!exp->str)
				return (0);
			free(tmp->str);
			tmp->str = NULL;
			if (tmp->quotes)
				exp->quotes = 1;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	exp_reconnect(t_expands **_exp)
{
	t_expands	*exp;
	t_expands	*tmp;

	exp = *_exp;
	if (!exp)
		return (1);
	if (!reconnect_helper(exp->next, exp))
		return (0);
	tmp = exp->next;
	while (tmp)
	{
		if (!tmp->str)
		{
			exp->next = NULL;
			exp_addback(&exp, tmp->next);
			exp_delone(tmp, free);
			tmp = exp;
		}
		else
			exp = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	exp_remove_quotes(t_expands *exp)
{
	while (exp)
	{
		if (exp->quotes)
			remove_quotes_3(exp->str);
		exp = exp->next;
	}
	return (1);
}

int	expand_sub(t_minishell *mini, t_expands **_exp)
{
	char		*tmp;
	t_expands	*exp;
	int			out;

	exp = *_exp;
	while (exp)
	{
		tmp = expand(mini, exp->str, 0);
		if (!tmp)
			return (0);
		if (ft_strcmp(exp->str, tmp))
		{
			out = sub_helper(_exp, &exp, tmp);
			if (!out)
				return (0);
			else if (out == -1)
				continue ;
		}
		else
			free(tmp);
		exp = exp->next;
	}
	return (1);
}
