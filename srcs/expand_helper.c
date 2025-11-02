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
