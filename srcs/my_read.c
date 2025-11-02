#include "../header/minishell.h"

extern int	g_signaln;

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
			|| (state_one == 5 && (ft_strlen(in[i]) > 1
					|| !in[i + 1] || i == 0)))
			return (0);
	}
	return (1);
}

int	my_read2(t_minishell *mini)
{
	int	i;

	ft_free(mini->out);
	mini->out = NULL;
	if (!mini->lex)
		return (mini->error_code = 1, 1);
	i = check_heredoc(mini->lex, mini);
	if (!i)
		return (lex_clear(&(mini->lex), ft_free), mini->lex = NULL, 1);
	if (i == -1)
		return (lex_clear(&(mini->lex), ft_free),
			mini->lex = NULL, mini->error_code = 0, 1);
	if (i == 2)
		return (lex_clear(&(mini->lex), ft_free), mini->lex = NULL,
			mini->error_code = 130, 1);
	if (!expand_all(mini))
		return (lex_clear(&(mini->lex), ft_free), mini->lex = NULL, 1);
	return (1);
}

int	my_read(t_minishell *mini)
{
	mini->in = readline("minishell>");
	if (!mini->in)
		return (0);
	if (g_signaln != 0)
	{
		mini->error_code = 128 + g_signaln;
		g_signaln = 0;
	}
	//add_history(mini->in);
	if (!*(mini->in))
		return (free(mini->in), mini->in = NULL, 1);
	if (!check_quotes(mini->in))
		return (free(mini->in), mini->in = NULL
			, ft_putendl_fd("Count your quotes", 2), mini->error_code = 2, 1);
	mini->out = mini_split(mini->in);
	free(mini->in);
	mini->in = NULL;
	if (!mini->out)
		return (1);
	if (!check_syntax(mini, mini->out))
		return (ft_free(mini->out), mini->out = NULL
			, ft_putendl_fd("syntax error", 2), mini->error_code = 2, 1);
	mini->lex = lexer(mini->out);
	return (my_read2(mini));
}
