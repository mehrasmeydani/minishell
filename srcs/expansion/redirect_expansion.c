#include "../../header/minishell.h"

void	free_exp(t_expand *exp)
{
	ssize_t	i;

	i = -1;
	while (++i < exp->len)
		exp_clear(&(exp->exp[i]), free);
	free(exp->exp);
}

t_expands	*create_exp(char **in)
{
	t_expands	*out;
	t_expands	*tmp;
	ssize_t		i;

	i = -1;
	out = NULL;
	while (in[++i])
	{
		tmp = exp_new(in[i], 0, 0, (*in[i] == '\'' || *in[i] == '"'));
		if (!tmp)
			return (exp_clear(&out, free), NULL);
		exp_addback(&out, tmp);
	}
	return (out);
}

t_expands	*reparse(char **in, char *org)
{
	ssize_t		i;
	ssize_t		j;
	ssize_t		k;
	t_expands	*out;
	t_expands	*tmp;

	i = -1;
	j = 0;
	out = NULL;
	while (org[++i])
	{
		if (in[j] && org[i] == in[j][0])
		{
			k = ft_strlen(in[j]);
			tmp = exp_new(in[j], ((i > 0) && (ft_strchr("\t\n\r\v\f ",
								org[i - 1]))), ((org[i + k])
						&& (ft_strchr("\t\n\r\v\f ", org[i + k]))), 0);
			if (!tmp)
				return (exp_clear(&out, free), NULL);
			exp_addback(&out, tmp);
			i += k - 1;
			j++;
		}
	}
	return (out);
}

int	redirect_exp2(t_minishell *mini, t_redirect *red)
{
	char	*tmp;

	tmp = expand(mini, red->name, 0);
	if (!tmp)
		return (0);
	free(red->name);
	red->name = tmp;
	if (!has_quotes(red->name) && is_in(red->name, "\t\n\r\v\f "))
		return (errno = 1, perror("ambiguous redirect"), 0);
	if (!remove_quotes(&red->name))
		return (0);
	return (1);
}

int	redirect_exp(t_minishell *mini, t_redirect *red)
{
	char	*tmp;

	while (red)
	{
		if (red->level == HEREDOC && red->input_expand != 1)
		{
			tmp = expand(mini, red->input, 1);
			if (!tmp)
				return (0);
			free(red->input);
			red->input = tmp;
		}
		else if (red->level != HEREDOC)
			if (!redirect_exp2(mini, red))
				return (0);
		red = red->next;
	}
	return (1);
}
