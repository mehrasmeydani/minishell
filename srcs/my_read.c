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
			|| (state_one == 5 && (ft_strlen(in[i]) > 1 || !in[i + 1])))
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



int	expand_tmp(t_lex *lex, t_expand *exp)
{
	ssize_t	i;
	char	**str;

	i = -1;
	(void)exp;
	while (lex->cmd[++i])
	{
		str	= exp_split(lex->cmd[i]);
	}
	return (1);
}

int	expand_all(t_minishell *mini) //change
{
	t_lex		*lex;
	t_expand	exp;
	//ssize_t		i;

	lex = mini->lex;
	while (lex)
	{
		// i = ft_str_str_len(lex->cmd);
		// exp.exp	= ft_calloc(i, sizeof(t_expands *));
		// if (!exp.exp)
		// 	return (0);
		// exp.len = i;
		if (!expand_tmp(lex, &exp))
			return (0);
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
			, ft_putendl_fd("Syntax error", 2), mini->error_code = 2, 1); //syntax error
	mini->lex = lexer(mini->out);
	ft_free(mini->out);
	mini->out = NULL;
	if (!mini->lex)
		return (mini->error_code = -1, 1); // alloc fail
	expand_all(mini);
	//remove_quotes(mini); //
	if (!check_heredoc(mini->lex))
		return (lex_clear(&(mini->lex), ft_free), mini->lex = NULL, 1); // alloc fail
	return (1);
}
