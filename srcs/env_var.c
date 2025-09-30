#include "../header/minishell.h"

static int	shlvl(t_env *env, int lvl, ssize_t i)
{
	char	*tmp;

	tmp = ft_itoa(lvl);
	if (!tmp)
		return (0);
	free(env->var_value[i]);
	env->var_value[i] = tmp;
	tmp = ft_strdup("SHLVL=");
	if (!tmp)
		return (0);
	free(env->raw_var[i]);
	env->raw_var[i] = tmp;
	tmp = ft_strjoin(env->raw_var[i], env->var_value[i]);
	if (!tmp)
		return (0);
	free(env->raw_var[i]);
	env->raw_var[i] = tmp;
	return (1);
}

void	free_env(t_env *env)
{
	if (env->raw_var)
	{
		ft_free(env->raw_var);
		env->raw_var = NULL;
	}
	if (env->var_name)
	{
		ft_free(env->var_name);
		env->var_name = NULL;
	}
	if (env->var_pass_to_exec)
	{
		ft_free(env->var_pass_to_exec);
		env->var_pass_to_exec = NULL;
	}
	if (env->var_value)
	{
		ft_free(env->var_value);
		env->var_value = NULL;
	}
	if (env->sorted)
	{
		ft_free(env->sorted);
		env->sorted = NULL;
	}
}

static int	set_var2(t_env *env, ssize_t i)
{
	char	*tmp;

	env->var_name = ft_calloc(i + 1, sizeof(char *));
	env->var_value = ft_calloc(i + 1, sizeof(char *));
	if (!env->var_value || !env->var_name)
		return (free_env(env), 0);
	i = -1;
	while (env->raw_var[++i])
	{
		tmp = ft_strchr(env->raw_var[i], '=');
		env->var_name[i] = ft_substr(env->raw_var[i], 0, tmp - env->raw_var[i]);
		env->var_value[i] = ft_substr(env->raw_var[i], tmp - env->raw_var[i] + 1, ft_strlen(tmp) - 1);
		if (!env->var_value[i] || !env->var_name[i])
			return (free_env(env), 0);
		if (!ft_strcmp("SHLVL", env->var_name[i]))
			if (!shlvl(env, ft_atoi(env->var_value[i]) + 1, i))
				return (free_env(env), 0);
	}
	return (1);
}

static int	set_var3(t_env *env)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = 0;
	while (env->raw_var[++i])
		if (ft_strlen(env->var_value[i]) > 0)
			j++;
	env->var_pass_to_exec = ft_calloc(j + 1, sizeof(char *));
	if (!env->var_pass_to_exec)
		return (free_env(env), 0);
	i = -1;
	j = 0;
	while (env->raw_var[++i])
	{
		if (ft_strlen(env->var_value[i]) > 0)
		{
			env->var_pass_to_exec[j] = ft_strdup(env->raw_var[i]);
			if (!env->var_pass_to_exec[j])
				return (free_env(env), 0);
			j++;
		}
	}
	return (1);
}

int	set_var(t_minishell *mini, char **env_var)
{
	t_env	*env;
	ssize_t	i;

	(void)mini;
	env = &mini->env;
	i = ft_str_str_len(env_var);
	if (!i && ++i && ++i && ++i && ++i)
	{
		if (!preset_var(env))
			return (0);
	}
	else
	{
		env->raw_var = ft_duostrdup(env_var, i);
		env->sorted = ft_duostrdup(env_var, i);
		if (!env->raw_var || !env->sorted)
			return (free_env(env), 0);
	}
	if (!set_var2(env, i))
		return (0);
	if (!set_var3(env))
		return (0);
	ft_sort_string_tab(env->sorted);
	return (1);
}
