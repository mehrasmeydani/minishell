/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:37 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:38 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	shlvl(char **tmp, ssize_t i, ssize_t i1)
{
	tmp[i + i1 - 1] = ft_strdup("SHLVL=0");
	if (!tmp[i + i1 - 1])
		return (0);
	return (1);
}

int	pwd_set(char **tmp, ssize_t i, ssize_t i1, ssize_t i2)
{
	char	*tmp2;

	tmp2 = getcwd(NULL, 0);
	if (!tmp2)
		return (0);
	tmp[i + i1 + i2 - 1] = ft_strjoin("PWD=", tmp2);
	free(tmp2);
	if (!tmp[i + i1 + i2 - 1])
		return (0);
	return (1);
}

int	add_env(t_env *env, int i1, int i2, int i3)
{
	ssize_t	i;
	char	**tmp;

	i = ft_str_str_len(env->raw_var);
	tmp = ft_duostrdup(env->raw_var, i + i1 + i2 + i3);
	free_env(env);
	if (!tmp)
		return (0);
	env->raw_var = tmp;
	(env->allocated_l) = i + (i1 + i2 + i3);
	if (i1)
		if (!shlvl(tmp, i, i1))
			return (free_env(env), 0);
	if (i2)
		if (!pwd_set(tmp, i, i1, i2))
			return (free_env(env), 0);
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
		return (add_env(env, must % 2, must / 2 % 2, must / 4 % 2));
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
