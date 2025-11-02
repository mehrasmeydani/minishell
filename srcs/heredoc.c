#include "../header/minishell.h"

extern int g_signaln;

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

int	heredoc_eof(t_redirect *tmp)
{
	if (tmp->input)
	{
		tmp->input = ft_relocat(tmp->input, "\n");
		if (!tmp->input)
			return (0);
	}
	return (ft_putendl_fd("Warning: EOF!", 2),
		free(tmp->name), tmp->name = NULL, -1);
}

void	heredoc_sig(int sig)
{
	//ft_putendl_fd("", 1);
	if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
		exit(2);
	//rl_replace_line("", 0);
	rl_done = 1;
	rl_on_new_line();
	//rl_redisplay();
	g_signaln = sig;
}
int	here_docrl(t_redirect *tmp, char *tmp_str)
{
	if (has_quotes(tmp->name))
		tmp->input_expand = 1;
	if (!remove_quotes_2(&tmp->name))
		return (0);
	while (true)
	{
		signal(SIGINT, heredoc_sig);
		tmp_str = readline(">");
		if (g_signaln != 0)
			return(2);
		if (!tmp_str)
			return (heredoc_eof(tmp));
		if (!ft_strcmp(tmp->name, tmp_str))
		{
			free(tmp_str);
			tmp_str = NULL;
			free(tmp->name);
			tmp->name = NULL;
			tmp->input = ft_relocat(tmp->input, "\n");
			if (!tmp->input)
				return (0);
			break ;
		}
		if (!here_docrl2(tmp, tmp_str))
			return (0);
	}
	return (1);
}

int	check_heredoc(t_lex *lex, t_minishell *mini)
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
				if (err == 2)
					return (2);
				if (err == -1)
					mini->error_code = 0;
			}
			tmp = tmp->next;
		}
		lex = lex->next;
	}
	return (1);
}
