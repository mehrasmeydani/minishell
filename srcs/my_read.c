#include "../header/minishell.h"

static int	check_quotes(char *in)
{
	ssize_t	i;
	int		quotes_status;

	i = -1;
	quotes_status = 0;
	while (in[++i])
		quotes(in[i], &quotes_status);
	if (quotes_status)
		return (0);
	return (1);
}

static int	state_set(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i + 3);
	return (-1);
}

static int	check_syntax(t_minishell *mini, char **in)
{
	ssize_t	i;
	ssize_t	state_one;
	ssize_t	state_two;

	i = -1;
	(void)mini;
	while (in[++i])
	{
		state_one = state_set(in[i][0], "<>|");
		if (in[i + 1])
			state_two = state_set(in[i + 1][0], "<>|");
		if (((state_one == 3 || state_one == 4) && (ft_strlen(in[i]) > 2
					|| !in[i + 1] || (in[i + 1] && state_two != -1)))
			|| (state_one == 5 && (ft_strlen(in[i]) > 1 || !in[i + 1] || i == 0)))
			return (0);
	}
	return (1);
}

char	*ft_relocat(char *in, char *buff)
{
	char	*out;
	size_t	mlen;

	mlen = ft_strlen(buff) + 1;
	if (!in)
	{
		out = (char *)ft_calloc(mlen, 1);
		if (!out)
			return (NULL);
		ft_strlcat(out, buff, mlen);
		return (out);
	}
	out = (char *)ft_calloc(ft_strlen(in) + mlen, 1);
	if (!out)
		return (free(in), NULL);
	ft_strlcat(out, in, ft_strlen(in) + 1);
	ft_strlcat(out, buff, ft_strlen(out) + mlen);
	free(in);
	return (out);
}

int	has_quotes(char *in)
{
	ssize_t	i;

	i = -1;
	while (in && in[++i])
		if (in[i] == '\'' || in[i] == '"')
			return (1);
	return (0);
}

int	here_docrl2(t_redirect *tmp, char *tmp_str)
{
	if (tmp->input)
	{
		tmp->input = ft_relocat(tmp->input, "\n");
			if (!tmp->input)
				return (free(tmp_str), 0);
	}
	tmp->input = ft_relocat(tmp->input, tmp_str);
	free(tmp_str);
	tmp_str = NULL;
	if (!tmp->input)
		return (0);
	return (1);
}

int	here_docrl(t_redirect *tmp, char *tmp_str)
{
	if (has_quotes(tmp->name))
		tmp->input_expand = 1;
	if (!remove_quotes(&tmp->name))
		return(0);
	while (true)
	{
		tmp_str = readline(">");
		if (!tmp_str)
			return (-1);
		if (!ft_strcmp(tmp->name, tmp_str))
		{
			free(tmp_str);
			tmp_str = NULL;
			free(tmp->name);
			tmp->name = NULL;
			tmp->input = ft_relocat(tmp->input, "\n");
			if (!tmp->input)
				return (0);
			break;
		}
		if (!here_docrl2(tmp, tmp_str))
			return (0);
	}
	return (1);
}

int	check_heredoc(t_lex *lex)
{
	t_redirect	*tmp;
	char		*tmp_str;
	int			err;

	while (lex)
	{
		tmp = lex->redic;
		while (tmp)
		{
			tmp_str = NULL;
			if (tmp->level == HEREDOC)
			{
				err = here_docrl(tmp, tmp_str);
				if (err == 0)
					return (0);
			}
			tmp = tmp->next;
		}
		lex = lex->next;
	}
	return (1);
}

void	free_exp(t_expand *exp)
{
	ssize_t	i;

	i = -1;
	while (++i < exp->len)
		exp_clear(&(exp->exp[i]), free);
	free(exp->exp);
}

t_expands	*create_exp(char **in)
{
	t_expands	*out;
	t_expands	*tmp;
	ssize_t		i;

	i = -1;
	out = NULL;
	while (in[++i])
	{
		tmp = exp_new(in[i], 0, 0, (*in[i] == '\'' || *in[i] == '"'));
		if (!tmp)
			return (exp_clear(&out, free), NULL);
		exp_addback(&out, tmp);
	}
	return (out);
}

int	is_in(char *str, char *set)
{
	ssize_t i;
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

t_expands *reparse(char **in, char *org)
{
	ssize_t		i;
	ssize_t		j;
	ssize_t		k;
	t_expands	*out;
	t_expands	*tmp;

	i = -1;
	j = 0;
	out = NULL;
	while (org[++i])
	{
		if (in[j] && org[i] == in[j][0])
		{
			k = ft_strlen(in[j]);
			tmp = exp_new(in[j],
				((i > 0) && (ft_strchr("\t\n\r\v\f ", org[i - 1])))
				, ((org[i + k])
				&& (ft_strchr("\t\n\r\v\f ", org[i + k]))), 0);
			if (!tmp)
				return (exp_clear(&out, free), NULL);
			exp_addback(&out, tmp);
			i += k - 1;
			j++;
		}
	}
	return (out);
}

void	ft_swap(char *a, char *b)
{
	char	why;

	why = *a;
	*a = *b;
	*b = why;
}

void	remove_quotes_3(char *str)
{
	ssize_t	i;

	i = -1;
	while (str[++i] && str[i + 1])
	{
		ft_swap(&(str[i]), &(str[i + 1]));
	}
	str[i - 1] = 0;
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
	char		**tmp2;
	t_expands	*exp_tmp;
	t_expands	*exp_tmp2;
	t_expands	*exp;

	exp = *_exp;
	while (exp)
	{
		tmp = expand(mini, exp->str, mini->env, 0);
		if (!tmp)
			return (0);
		if (ft_strcmp(exp->str, tmp))
		{
			if (!(exp->quotes) && is_in(tmp, "\t\n\r\v\f "))
			{
				exp_tmp = NULL;
				tmp2 = split_2(tmp, "\t\n\r\v\f ");
				if (!tmp2)
					return (free(tmp), 0);
				if (*tmp2)
				{
					exp_tmp = reparse(tmp2, tmp);
					if (!exp_tmp)
						return (ft_free(tmp2), free(tmp), 0);
				}
				free(tmp);
				free(tmp2);
				exp_tmp2 = exp->next;
				exp_removeandinject(_exp, exp, exp_tmp);
				exp = exp_tmp2;
				continue ;
			}
			else
			{
				free(exp->str);
				exp->str = tmp;
			}
		}
		else
			free(tmp);
		exp = exp->next;
	}
	return (1);
}

int	exp_reconnect(t_expands **_exp)
{
	t_expands	*exp;
	t_expands	*tmp;
	//char		*str;

	exp = *_exp;
	if (!exp)
		return (1);
	tmp = exp->next;
	while (tmp)
	{
		if (exp->after_space || tmp->behind_space)
			exp = tmp;
		else
		{
			exp->str = ft_relocat(exp->str, tmp->str);
			free(tmp->str);
			tmp->str = NULL;
			if (tmp->quotes)
				exp->quotes = 1;
		}
		tmp = tmp->next;
	}
	exp = *_exp;
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


char	**expand_exp(t_minishell *mini, t_expands **exp)
{
	char		**out;
	t_expands	*tmp;
	ssize_t		i;

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
	i = 0;
	tmp = *exp;
	while (tmp)
	{
		if ((tmp->str && *tmp->str) || tmp->quotes)
		{
			out[i] = tmp->str;
			tmp->str = NULL;
			i++;
		}
		else
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		tmp = tmp->next;
	}
	return (out);
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
	str2 =  (char ***)ft_calloc(ft_str_str_len(lex->cmd) + 1, sizeof(char **));
	if (!str2)
		return (0);
	while (lex->cmd[++i])
	{
		str	= exp_split(lex->cmd[i]);
		if (!str)
			return (free(str2), free_exp(exp), 0);
		exp->exp[i] = create_exp(str);
		if (!exp->exp[i])
			return (free(str2), free_exp(exp), 0);
		free(str);
		str2[i] = expand_exp(mini, &(exp->exp[i]));
		if (!str2[i])
			return (ft_free_free(str2), free_exp(exp), 0);
	}
	//;
	if (!replace_command(lex, str2))
		return (ft_free_free(str2), 0);
	return (1);
}

int	expand_all(t_minishell *mini) //change
{
	t_lex		*lex;
	t_redirect	*red;
	t_expand	exp;
	ssize_t		i;

	lex = mini->lex;
	errno = 0;
	while (lex)
	{
		i = ft_str_str_len(lex->cmd);
		exp.exp	= ft_calloc(i, sizeof(t_expands *));
		if (!exp.exp)
			return (0);
		exp.len = i;
		if (!expand_tmp(mini, lex, &exp))
			return (0);
		free_exp(&exp);
		red = lex->redic;
		while (red)
		{
			if (red->level == HEREDOC && red->input_expand)
			{
				red->input = expand(mini, red->input, mini->env, 1);
				if (!red->input)
					return (0);
			}
			else if (red->level != HEREDOC)
			{
				red->name = expand(mini, red->name, mini->env, 0);
				if (!red->name)
					return (0);
				if (!has_quotes(red->name) && is_in(red->name, "\t\n\r\v\f "))
					return (errno = 1, perror("ambiguous redirect"), 0);
				if (!remove_quotes(&red->name))
					return (0);
			}
			red = red->next;
		}
		lex = lex->next;
	}
	return (1);
}

int	my_read(t_minishell *mini)
{
	mini->in = readline("minishell>");
	if (!mini->in)
		return (0); //error
	add_history(mini->in);
	if (!*(mini->in))
		return (free(mini->in), mini->in = NULL, 1);
	if (!check_quotes(mini->in))
		return (free(mini->in), mini->in = NULL
			, ft_putendl_fd("Count your quotes", 2), mini->error_code = 2, 1);
	mini->out = mini_split(mini->in);
	free(mini->in);
	mini->in = NULL;
	if (!mini->out)
		return (1); //error
	if (!check_syntax(mini, mini->out))
		return (ft_free(mini->out), mini->out = NULL
			, ft_putendl_fd("syntax error", 2), mini->error_code = 2, 1); //syntax error
	mini->lex = lexer(mini->out);
	ft_free(mini->out);
	mini->out = NULL;
	if (!mini->lex)
		return (mini->error_code = -1, 1); // alloc fail
	expand_all(mini);
	if (!check_heredoc(mini->lex))
		return (lex_clear(&(mini->lex), ft_free), mini->lex = NULL, 1); // alloc fail
	return (1);
}
