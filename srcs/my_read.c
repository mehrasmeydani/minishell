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

static int	check_syntax(char **in)
{
	ssize_t	i;
	ssize_t	state_one;
	ssize_t	state_two;

	i = -1;
	while (in[++i])
	{
		state_one = state_set(in[i][0], "<|>");
		if (in[i + 1])
			state_two = state_set(in[i + 1][0], "<|>");
		if ((state_one != -1 && in[i + 1] && state_two != -1)
			|| ((state_one == 3 || state_one == 5) && ft_strlen(in[i]) > 2)
			|| (state_one == 4 && ft_strlen(in[i]) > 1))
			return (0);
	}
	return (1);
}

// int	check_heredoc(t_lex *lex, char **in)
// {

// }

int	my_read(t_minishell *mini, t_lex *lex)
{
	(void)mini;
	lex->in = readline("minishell>");
	if (!lex->in)
		return (1); //error
	if (!check_quotes(lex->in))
		return (free(lex->in), lex->in = NULL
			, ft_putendl_fd("Count your quotes", 2), 1);
	lex->out = mini_split(lex->in);
	free(lex->in);
	lex->in = NULL;
	if (!lex->out)
		return (1); //error
	for (size_t i = 0; lex->out[i]; i++)
		printf("%s-\n", lex->out[i]);
	if (!check_syntax(lex->out))
		return (ft_free(lex->out, ft_str_str_len(lex->out)), lex->out = NULL
			, ft_putendl_fd("Syntax error", 2), 1); //syntax error
	// if (!check_heredoc(lex, lex->out))
	// 	return (0);
	return (1);
}
