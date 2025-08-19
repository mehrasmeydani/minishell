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
	while (in[++i])
	{
		state_one = state_set(in[i][0], "<>|");
		if (in[i + 1])
			state_two = state_set(in[i + 1][0], "<>|");
		if (((state_one == 3 || state_one == 4) && (ft_strlen(in[i]) > 2
					|| !in[i + 1] || (in[i + 1] && state_two != -1)))
			|| (state_one == 5 && (ft_strlen(in[i]) > 1 || !in[i + 1])))
		{
			if (state_one == 5)
				mini->num_pipes++;
			return (0);
		}
	}
	return (1);
}

// int	check_heredoc(t_lex *lex, char **in)
// {

// }

int	my_read(t_minishell *mini)
{
	t_lex	*tmp;
	t_redirect	*tmp_2;

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
		return (ft_free(mini->out, ft_str_str_len(mini->out)), mini->out = NULL
			, ft_putendl_fd("Syntax error", 2), 1); //syntax error
	mini->lex = lexer(mini->out);
	tmp = mini->lex;
	while (tmp)
	{
		for (size_t i = 0; tmp->cmd[i]; i++)
			printf("\t*%s*\n", tmp->cmd[i]);
		printf ("\t============\n");
		tmp_2 = tmp->redic;
		while (tmp_2)
		{
			printf("\t*%s* -", tmp_2->name);
			tmp_2 = tmp_2->next;
		}
		printf ("\n============================\n");
		tmp = tmp->next;
	}
	// if (!check_heredoc(mini, mini->out))
	// 	return (0);
	return (1);
}
