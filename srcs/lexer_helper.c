#include "../header/minishell.h"

ssize_t	clean_rest_helper(t_lex *tmp)
{
	ssize_t	i;
	ssize_t	str_len;

	i = -1;
	str_len = 0;
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i][0] == '<' || tmp->cmd[i][0] == '>')
			i++;
		else
			str_len++;
	}
	return (str_len);
}

static int	find_type(char *str)
{
	if (*str == '<')
	{
		if (ft_strlen(str) == 1)
			return (0);
		else
			return (2);
	}
	else if (ft_strlen(str) == 1)
		return (1);
	return (3);
}

int	clean_rest_helper2(t_lex *tmp, char **tmp_str)
{
	ssize_t	i;
	ssize_t	str_len;

	i = -1;
	str_len = 0;
	while (tmp->cmd[++i])
	{
		if (tmp->cmd[i][0] == '<' || tmp->cmd[i][0] == '>')
			i++;
		else
		{
			tmp_str[str_len] = ft_strdup(tmp->cmd[i]);
			if (!tmp_str[str_len])
				return (ft_free(tmp_str), 0);
			str_len++;
		}
	}
	return (1);
}

int	lex_redir_helper(t_lex *lex, t_lex	*tmp, ssize_t i)
{
	t_redirect	*redir;
	char		*tmp_str;

	tmp_str = ft_strdup(tmp->cmd[i + 1]);
	if (!tmp_str)
		return (lex_clear(&lex, ft_free), 0);
	redir = redirect_new(tmp_str, find_type(tmp->cmd[i++]));
	if (!redir)
		return (lex_clear(&lex, ft_free), free(tmp_str), 0);
	redirect_addback(&tmp->redic, redir);
	return (1);
}
