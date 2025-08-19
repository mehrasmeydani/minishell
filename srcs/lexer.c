#include "../header/minishell.h"

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
				, ft_free(cmd, ft_str_str_len(cmd)), NULL);
		lex_addback(&out, tmp);
		if (in[i])
		{
			in = &in[i + 1];
			i = 0;
		}
	}
	return (out);
}

t_lex	*lexer(char **in)
{
	t_lex	*out;

	out = lex_pipes(in, 0);
	if (!out)
		return (NULL);
	(void)out;
	//out = lex_redir(out);
	return (out);
}
