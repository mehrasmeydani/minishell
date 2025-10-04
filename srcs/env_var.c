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

int	set_name_value(t_env *env, int start)
{
	char	*tmp;
	ssize_t	i;

	env->var_name = ft_calloc(env->allocated_l + 1, sizeof(char *));
	env->var_value = ft_calloc(env->allocated_l + 1, sizeof(char *));
	if (!env->var_name || !env->var_value)
		return (free_env(env), 0);
	i = -1;
	while (++i < env->allocated_l)
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
		if (start && !ft_strcmp(env->var_name[i], "SHLVL"))
			if (!shlvl(env, ft_atoi(env->var_value[i]) + 1, i))
				return (free_env(env), 0);
	}
	return (1);
}

int	add_env(t_env *env, int i1, int i2, int i3)
{
	ssize_t	i;
	char	**tmp;
	char	*tmp2;

	i = ft_str_str_len(env->raw_var);
	tmp = ft_duostrdup(env->raw_var, i + i1 + i2 + i3);
	free_env(env);
	if (!tmp)
		return (0);
	env->raw_var = tmp;
	(env->allocated_l) = i + (i1 + i2 + i3);
	if (i1)
	{
		tmp[i + i1 - 1] = ft_strdup("SHLVL=0");
		if (!tmp[i + i1 - 1])
			return (free_env(env), 0);
	}
	if (i2)
	{
		tmp2 = getcwd(NULL, 0);
		if (!tmp2)
			return (free_env(env), 0);
		tmp[i + i1 + i2 - 1] = ft_strjoin("PWD=", tmp2);
		free(tmp2);
		if (!tmp[i + i1 + i2 - 1])
			return (free_env(env), 0);
	}
	if (i3)
	{
		tmp[i + i1 + i2 + i3 - 1] = ft_strdup("OLDPWD");
		if (!tmp[i + i1 + i2 + i3 - 1])
			return (free_env(env), 0);
	}
	return (1);
}

int	set_must_var(t_env *env)
{
	ssize_t	i;
	ssize_t	must;
	char	*tmp;
	ssize_t	len;

	must = 7;
	i = -1;
	while (++i < env->allocated_l)
	{
		tmp = ft_strchr(env->raw_var[i], '=');
		len = (((tmp != NULL) * (tmp - env->raw_var[i]))
			+ ((tmp == NULL) * ft_strlen(env->raw_var[i])));
		if (!ft_strncmp(env->raw_var[i], "SHLVL", len))
			must -= 1;
		if (!ft_strncmp(env->raw_var[i], "PWD", len))
			must -= 2;
		if (!ft_strncmp(env->raw_var[i], "OLDPWD", len))
			must -= 4;
	}
	if (must)
		return(add_env(env, must % 2, must / 2 % 2, must / 4 % 2));
	return (1);
}

int	set_var(t_minishell *mini, char **env_var, bool first)
{
	t_env	*env;
	ssize_t	i;

	(void)mini;
	env = &mini->env;
	i = ft_str_str_len(env_var);
	env->raw_var = ft_duostrdup(env_var, i);
	if (!env->raw_var)
		return (0);
	env->allocated_l = i;
	if ((first && !set_must_var(env)) || !set_name_value(env, first)
		|| !set_pass_to_exec(env))
		return (0);
	return (1);
}
