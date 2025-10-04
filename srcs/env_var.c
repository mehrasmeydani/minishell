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
	ssize_t	i;

	i = -1;
	while (++i < env->allocated_l)
	{
		if (env->raw_var)
			free(env->raw_var[i]);
		if (env->var_name)
			free(env->var_name[i]);
		if (env->var_value)
			free(env->var_value[i]);
	}
	free(env->raw_var);
	env->raw_var = NULL;
	free(env->var_name);
	env->var_name = NULL;
	free(env->var_value);
	env->var_value = NULL;
	free(env->var_pass_to_exec);
	env->var_pass_to_exec = NULL;
	env->allocated_l = 0;
}

int	set_pass_to_exec(t_env *env)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = 0;
	while (env->raw_var[++i])
		if (ft_strchr(env->raw_var[i], '='))
			j++;
	env->var_pass_to_exec = ft_calloc(j + 1, sizeof(char *));
	if (!env->var_pass_to_exec)
		return (free_env(env), 0);
	i = -1;
	j = 0;
	while (env->raw_var[++i])
		if (ft_strchr(env->raw_var[i], '='))
			env->var_pass_to_exec[j++] = env->raw_var[i];
	return (1);
}

int	set_name_value(t_env *env, ssize_t i)
{
	char	*tmp;

	env->var_name = ft_calloc(i + 1, sizeof(char *));
	env->var_value = ft_calloc(i + 1, sizeof(char *));
	if (!env->var_name || !env->var_value)
		return (free_env(env), 0);
	i = -1;
	while (env->raw_var[++i])
	{
		tmp = ft_strchr(env->raw_var[i], '=');
		if (!tmp)
		{
			env->var_name[i] = ft_strdup(env->raw_var[i]);
			if (!env->var_name[i])
				return (free_env(env), 0);
		}
		else
		{
			env->var_name[i] = ft_substr(env->raw_var[i], 0, tmp - env->raw_var[i]);
			env->var_value[i] = ft_strdup(tmp + 1);
			if (!env->var_name[i] || !env->var_value[i])
				return (free_env(env), 0);
		}
		if (!ft_strcmp(env->var_name[i], "SHLVL"))
			if (!shlvl(env, ft_atoi(env->var_value[i]), i))
				return (free_env(env), 0);
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
		if (!preset_var(env))
			return (0);
	if (!env->raw_var)
	{
		env->raw_var = ft_duostrdup(env_var, i);
		if (!env->raw_var)
			return (0);
	}
	env->allocated_l = i;
	if (!set_name_value(env, i) || !set_pass_to_exec(env)) // must_env(SHLVL, PWD, OLDPWD)
		return (0);
	return (1);
}
