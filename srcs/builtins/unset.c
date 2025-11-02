#include "../../header/minishell.h"

static void	ft_swap2(char **a, char **b)
{
	char	*why;

	why = *a;
	*a = *b;
	*b = why;
}

int	unset_helper(t_env *env, char *cmd)
{
	ssize_t	k;

	k = var_exists(env, cmd, NULL);
	if (k == -1)
		return (-1);
	while (env->raw_var[k] && env->raw_var[k + 1])
	{
		ft_swap2(&env->raw_var[k], &env->raw_var[k + 1]);
		k++;
	}
	free(env->raw_var[k]);
	env->raw_var[k] = NULL;
	return (1);
}

int	unset(t_minishell *mini, char **cmd)
{
	ssize_t	i;
	char	**tmp;
	t_env	*env;

	i = 0;
	env = &mini->env;
	while (cmd[++i])
	{
		if (unset_helper(env, cmd[i]) == -1)
			continue ;
		tmp = ft_duostrdup(env->raw_var, env->allocated_l - 1);
		if (!tmp)
			return (0);
		free_env(env);
		if (!set_var(mini, tmp, 0))
			return (ft_free(tmp), 0);
		ft_free(tmp);
	}
	return (1);
}
