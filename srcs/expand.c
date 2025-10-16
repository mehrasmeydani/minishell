#include "../header/minishell.h"

int	find_var(char **var, char *in, ssize_t len, t_env env)
{
	ssize_t	i;
	char	*tmp;

	i = -1;
	tmp = ft_substr(in, 0, len);
	if (!tmp)
		return (0);
	while (env.var_name[++i])
	{
		if (!ft_strcmp (env.var_name[i], tmp))
			return (*var = env.var_value[i], free(tmp), 1);
	}
	return (*var = NULL, free(tmp), 1);
}

char	*expand(t_minishell *mini, char *in, t_env env, int here_doc)
{
	ssize_t	i;
	ssize_t	j;
	char	*out;
	char	*tmp;
	char	*tmp_var;
	int		quotes_state;
	char	*tmp2;

	i = 0;
	out = NULL;
	quotes_state = 0;
	while (in[i])
	{
		j = 1;
		quotes(in[i], &quotes_state);
		if ((quotes_state != SINGLE || here_doc) && in[i] == '$')
		{
			tmp2 = NULL;
			tmp_var = NULL;
			if (in[i + j] == '?')
			{
				tmp2 = ft_itoa(mini->error_code);
				if (!tmp2)
					return (NULL);
				tmp_var = tmp2;
				j++;
			}
			else
			{
				while (in[i + j] && !ft_iswhitespace(in[i + j]) && in[i + j] != '"' && in[i + j] != '\''&& in[i + j] != '$') //add_whitespaces
					j++;
				if (!find_var(&tmp_var, in + i + 1, j - 1, env))
					return (free(out), NULL);
			}
			tmp = ft_substr(in, 0, i);
			if (!tmp)
				return (NULL);
			out	= ft_relocat(out, tmp);
			free(tmp);
			if (!out)
				return (NULL);
			if (tmp_var)
			{
				out = ft_relocat(out, tmp_var);
				if (!out)
					return (NULL);
			}
			free(tmp2);
			in = in + i + j;
			i = 0;
			continue ;
		}
		i++;
	}
	out = ft_relocat(out, in);
	return (out);
}
