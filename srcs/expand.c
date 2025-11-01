#include "../header/minishell.h"

int	find_var(char **var, char *in, ssize_t len, t_env env)
{
	ssize_t	i;
	char	*tmp;

	i = -1;
	tmp = ft_substr(in, 0, len);
	if (!tmp)
		return (0);
	while (env.var_name[++i])
	{
		if (!ft_strcmp (env.var_name[i], tmp))
			return (*var = env.var_value[i], free(tmp), 1);
	}
	return (*var = NULL, free(tmp), 1);
}

int	var_find(t_minishell *mini, char *in, t_expansion *exp)
{
	if (in[exp->i + exp->j] == '?')
	{
		exp->tmp2 = ft_itoa(mini->error_code);
		if (!exp->tmp2)
			return (0);
		exp->tmp_var = exp->tmp2;
		exp->j++;
	}
	else
	{
		while (in[exp->i + exp->j] && is_valid_env(in[exp->i + exp->j], exp->j))
			exp->j++;
		if (!find_var(&exp->tmp_var, in + exp->i + 1, exp->j - 1, mini->env))
			return (0);
	}
	return (1);
}

int	expand_helper(t_expansion *exp)
{
	exp->tmp2 = ft_strdup("$");
	if (!exp->tmp2)
		return (0);
	exp->tmp_var = exp->tmp2;
	return (1);
}

int	expand_helper2(t_expansion *exp, char **out, char **in)
{
	*out = ft_relocat(*out, exp->tmp);
	free(exp->tmp);
	if (!*out)
		return (0);
	if (exp->tmp_var)
	{
		*out = ft_relocat(*out, exp->tmp_var);
		if (!*out)
			return (0);
	}
	free(exp->tmp2);
	*in = *in + exp->i + exp->j;
	exp->i = 0;
	return (1);
}

int	expand_helper3(t_minishell *mini, t_expansion *exp, char **out, char **in)
{
	exp->tmp2 = NULL;
	exp->tmp_var = NULL;
	if (!var_find(mini, *in, exp))
		return (free(*out), 0);
	if (exp->j == 1)
		if (!expand_helper(exp))
			return (free(*out), 0);
	exp->tmp = ft_substr(*in, 0, exp->i);
	if (!exp->tmp)
		return (free(*out), 0);
	if (!expand_helper2(exp, out, in))
		return (0);
	return (1);
}

char	*expand(t_minishell *mini, char *in, int here_doc)
{
	char		*out;
	int			quotes_state;
	t_expansion	exp;

	exp.i = 0;
	out = NULL;
	quotes_state = 0;
	if (!in)
		return (NULL);
	while (in[exp.i])
	{
		exp.j = 1;
		quotes(in[exp.i], &quotes_state);
		if ((quotes_state != SINGLE || here_doc) && in[exp.i] == '$')
		{
			if (!expand_helper3(mini, &exp, &out, &in))
				return (0);
			continue ;
		}
		exp.i++;
	}
	return (ft_relocat(out, in));
}
