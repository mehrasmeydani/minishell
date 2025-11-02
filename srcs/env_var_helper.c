/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:40 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:40 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	shlvl_i(t_env *env, int lvl, ssize_t i)
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

int	set_name_value_helper(t_env *env, ssize_t i, char *tmp)
{
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
		if (!set_name_value_helper(env, i, tmp))
			return (0);
		if (start && !ft_strcmp(env->var_name[i], "SHLVL"))
			if (!shlvl_i(env, ft_atoi(env->var_value[i]) + 1, i))
				return (free_env(env), 0);
	}
	return (1);
}
