/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:40 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:40 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*min_str(char **in)
{
	char	*out;
	ssize_t	i;

	out = *in;
	i = -1;
	while (in && in[++i])
		if (ft_strcmp(out, in[i]) > 0)
			out = in[i];
	return (out);
}

char	*max_str(char **in)
{
	char	*out;
	ssize_t	i;

	out = *in;
	i = -1;
	while (in && in[++i])
		if (ft_strcmp(out, in[i]) < 0)
			out = in[i];
	return (out);
}

void	print_export2(char *str, t_env *env)
{
	ssize_t	i;

	i = -1;
	if (!ft_strcmp("_", str))
		return ;
	while (++i < env->allocated_l)
	{
		if (!ft_strcmp(str, env->var_name[i]))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->var_name[i], 1);
			if (env->var_value[i])
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(env->var_value[i], 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putendl_fd("", 1);
			break ;
		}
	}
}

void	print_export(t_minishell *mini)
{
	t_env	*env;
	char	*print;
	char	*last;
	ssize_t	i;
	ssize_t	j;

	env = &mini->env;
	print = min_str(env->var_name);
	print_export2(print, env);
	last = print;
	i = -1;
	while (++i < env->allocated_l - 1)
	{
		j = -1;
		print = max_str(env->var_name);
		while (++j < env->allocated_l)
		{
			if (ft_strcmp(env->var_name[j], print) < 0
				&& ft_strcmp(env->var_name[j], last) > 0)
				print = env->var_name[j];
		}
		print_export2(print, env);
		last = print;
	}
}

ssize_t	var_exists(t_env *env, char	*input, char *tmp)
{
	ssize_t	i;

	i = -1;
	while (++i < env->allocated_l)
	{
		if (!tmp && !ft_strcmp(input, env->var_name[i]))
			return (i);
		else if (tmp && !ft_strcmp(tmp, env->var_name[i]))
			return (i);
	}
	return (-1);
}
