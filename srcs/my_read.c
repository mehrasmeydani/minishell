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

int	check_heredoc(t_lex *lex)
{
	t_redirect	*tmp;
	char		*tmp_str;

	while (lex)
	{
		tmp = lex->redic;
		while (tmp)
		{
			tmp_str = NULL;
			if (tmp->level == HEREDOC)
			{
				if (has_quotes(tmp->name))
					tmp->input_expand = 1;
				if (!remove_quotes(&tmp->name))
					return(0);
				while (true)
				{
					tmp_str = readline(">");
					if (!tmp_str)
						return (0);
					if (!ft_strcmp(tmp->name, tmp_str))
					{
						free(tmp_str);
						tmp_str = NULL;
						break;
					}
					if (tmp->input)
						tmp->input = ft_relocat(tmp->input, "\n");
					tmp->input = ft_relocat(tmp->input, tmp_str); //alloc check
					free(tmp_str);
					tmp_str = NULL;
				}
			}
			tmp = tmp->next;
		}
		lex = lex->next;
	}
	return (1);
}

int	expand_all(t_minishell *mini)
{
	t_redirect	*red;
	t_lex		*lex;
	char		*tmp;
	ssize_t		i;

	lex = mini->lex;
	while (lex)
	{
		red = lex->redic;
		while (red)
		{
			if (red->level == HEREDOC && red->input_expand == 0)
			{
				tmp = expand(red->input, mini->env, 1);
				if (!tmp)
					return (0);
				free(red->input);
				red->input = tmp;
			}
			red = red->next;
		}
		i = -1;
		while (lex->cmd[++i])
		{
			tmp = expand(lex->cmd[i], mini->env, 0);
			if (!tmp)
				return (0);
			free(lex->cmd[i]);
			lex->cmd[i] = tmp;
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
	if (!check_quotes(mini->in))
		return (free(mini->in), mini->in = NULL
			, ft_putendl_fd("Count your quotes", 2), 1);
	mini->out = mini_split(mini->in);
	free(mini->in);
	mini->in = NULL;
	if (!mini->out)
		return (1); //error
	if (!check_syntax(mini, mini->out))
		return (ft_free(mini->out), mini->out = NULL
			, ft_putendl_fd("Syntax error", 2), 1); //syntax error
	mini->lex = lexer(mini->out);
	if (!mini->lex)
		return (ft_free(mini->out), mini->out = NULL, 1);
	if (!check_heredoc(mini->lex))
		return (1); //free and error for alloc
	if (!expand_all(mini))
		return (1); //free and error for alloc
	ft_free(mini->out);
	return (1);
}
