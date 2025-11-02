#include "../../header/minishell.h"

void	exp_exp(t_expands *tmp, char **out)
{
	ssize_t	i;

	i = 0;
	while (tmp)
	{
		if ((tmp->str && *tmp->str) || tmp->quotes)
		{
			out[i] = tmp->str;
			tmp->str = NULL;
			i++;
		}
		else
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		tmp = tmp->next;
	}
}

int	sub_helper_helper(t_expands **exp_tmp, char **tmp2, char *tmp, int mode)
{
	if (mode == 1)
	{
		*exp_tmp = reparse(tmp2, tmp);
		if (!*exp_tmp)
			return (ft_free(tmp2), free(tmp), 0);
	}
	else if (mode == 2)
	{
		*exp_tmp = exp_new(NULL, 1, 1, 0);
		if (!*exp_tmp)
			return (ft_free(tmp2), free(tmp), 0);
	}
	return (1);
}

int	sub_helper(t_expands **_exp, t_expands **exp, char *tmp)
{
	char		**tmp2;
	t_expands	*exp_tmp2;
	t_expands	*exp_tmp;

	if (!((*exp)->quotes) && is_in(tmp, "\t\n\r\v\f "))
	{
		tmp2 = split_2(tmp, "\t\n\r\v\f ");
		if (!tmp2)
			return (free(tmp), 0);
		if (*tmp2 && !sub_helper_helper(&exp_tmp, tmp2, tmp, 1))
			return (0);
		else if (!(*tmp2) && !sub_helper_helper(&exp_tmp, tmp2, tmp, 2))
			return (0);
		free(tmp);
		ft_free(tmp2);
		exp_tmp2 = (*exp)->next;
		exp_removeandinject(_exp, (*exp), exp_tmp);
		(*exp) = exp_tmp2;
		return (-1);
	}
	free((*exp)->str);
	(*exp)->str = tmp;
	return (1);
}
