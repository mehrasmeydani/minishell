#include "../../header/minishell.h"

int	is_valid_env2(char c, int j)
{
	return (ft_isalpha(c) || c == '_' || (ft_isdigit(c) && j != 0));
}

int	export_syntax(char **cmd, ssize_t i, char **tmp2)
{
	ssize_t	j;

	*tmp2 = ft_strchr(cmd[i], '=');
	if (*tmp2)
	{
		if (*tmp2 == cmd[i])
			return (errno = EINVAL, 0);
		*tmp2 = ft_substr(cmd[i], 0, *tmp2 - cmd[i]);
		if (!*tmp2)
			return (0);
		j = -1;
		while (i == 1 && (*tmp2)[++j])
			if (!is_valid_env2((*tmp2)[j], j))
				return (free(*tmp2), errno = EINVAL, 0);
	}
	else
	{
		j = -1;
		while (i == 1 && cmd[i][++j])
			if (!is_valid_env2(cmd[i][j], j))
				return (errno = EINVAL, 0);
	}
	return (1);
}

int	add_var1(t_minishell *mini, char *tmp2, char *cmd, ssize_t k)
{
	char	**tmp;

	free(tmp2);
	tmp = ft_duostrdup(mini->env.raw_var, ft_str_str_len(mini->env.raw_var));
	if (!tmp)
		return (0);
	tmp2 = ft_strdup(cmd);
	if (!tmp2)
		return (ft_free(tmp), 0);
	free(tmp[k]);
	tmp[k] = tmp2;
	free_env(&(mini->env));
	if (!set_var(mini, tmp, 0))
		return (ft_free(tmp), 0);
	ft_free(tmp);
	return (1);
}

int	add_var2(t_minishell *mini, char *tmp2, char *cmd, t_env *env)
{
	char	**tmp;
	ssize_t	j;

	free(tmp2);
	j = ft_str_str_len(env->raw_var);
	tmp = ft_duostrdup(env->raw_var, j + 1);
	if (!tmp)
		return (0);
	tmp[ft_str_str_len(env->raw_var)] = ft_strdup(cmd);
	if (!tmp[ft_str_str_len(env->raw_var)])
		return (ft_free(tmp), 0);
	free_env(env);
	if (!set_var(mini, tmp, 0))
		return (ft_free(tmp), 0);
	ft_free(tmp);
	return (1);
}

int	add_var(t_minishell *mini, char **cmd)
{
	t_env	*env;
	char	*tmp2;
	ssize_t	i;
	ssize_t	k;

	env = &(mini->env);
	i = 0;
	while (cmd[++i])
	{
		if (!export_syntax(cmd, i, &tmp2))
			return (0);
		k = var_exists(env, cmd[i], tmp2);
		if (!tmp2 && k != -1)
			return (1);
		else if (tmp2 && k != -1 && !add_var1(mini, tmp2, cmd[i], k))
			return (0);
		else if (k == -1 && !add_var2(mini, tmp2, cmd[i], env))
			return (0);
	}
	return (1);
}

