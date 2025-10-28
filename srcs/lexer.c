#include "../header/minishell.h"
#include "../header/redirect.h"
#include <unistd.h>

static t_lex	*lex_pipes(char **in, ssize_t i)
{
	t_lex	*out;
	t_lex	*tmp;
	char	**cmd;

	i = 0;
	out = NULL;
	while (in[i])
	{
		while (in[i] && in[i][0] != '|')
			i++;
		cmd = ft_duostrdup(in, i);
		if (!cmd)
			return (lex_clear(&out, ft_free), NULL);
		tmp = lex_new(cmd);
		if (!tmp)
			return (lex_clear(&out, ft_free)
				, ft_free(cmd), NULL);
		lex_addback(&out, tmp);
		if (in[i])
		{
			in = &in[i + 1];
			i = 0;
		}
	}
	return (out);
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

int	clean_rest(t_lex *lex)
{
	t_lex 	*tmp;
	ssize_t	i;
	ssize_t	str_len;
	char	**tmp_str;

	tmp = lex;
	while (tmp)
	{
		str_len = 0;
		i = -1;
		while (tmp->cmd[++i])
		{
			if (tmp->cmd[i][0] == '<' || tmp->cmd[i][0] == '>')
				i++;
			else
				str_len++;
		}
		tmp_str = (char **)ft_calloc(str_len + 1, sizeof(char *));
		if (!tmp_str)
			return (0);
		str_len = 0;
		i = -1;
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
		ft_free(tmp->cmd);
		tmp->cmd = tmp_str;
		tmp = tmp->next;
	}
	return (1);
}

t_lex	*lex_redir(t_lex *lex)
{
	char		*tmp_str;
	t_lex		*tmp;
	t_redirect	*redir;
	ssize_t		i;

	tmp = lex;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
			if (tmp->cmd[i][0] == '<' || tmp->cmd[i][0] == '>')
			{
				tmp_str = ft_strdup(tmp->cmd[i + 1]);
				if (!tmp_str)
					return (lex_clear(&lex, ft_free), NULL);
				redir = redirect_new(tmp_str, find_type(tmp->cmd[i++]));
				if (!redir)
					return (lex_clear(&lex, ft_free), free(tmp_str), NULL);
				redirect_addback(&tmp->redic, redir);
			}
		}
		tmp = tmp->next;
	}
	if (!clean_rest(lex))
		return (lex_clear(&lex, ft_free), NULL);
	return (lex);
}

t_lex	*lexer(char **in)
{
	t_lex	*out;

	out = lex_pipes(in, 0);
	if (!out)
		return (NULL);
	(void)out;
	out = lex_redir(out);
	if (!out)
		return (NULL);
	return (out);
}
