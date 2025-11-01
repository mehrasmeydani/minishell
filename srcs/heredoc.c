#include "../header/minishell.h"

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

int	here_docrl(t_redirect *tmp, char *tmp_str)
{
	if (has_quotes(tmp->name))
		tmp->input_expand = 1;
	if (!remove_quotes_2(&tmp->name))
		return (0);
	while (true)
	{
		tmp_str = readline(">");
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
