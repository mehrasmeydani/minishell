/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preset_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:46:27 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:46:30 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	preset_var(t_env *env)
{
	char	*tmp;

	env->raw_var = ft_calloc(5, sizeof(char *));
	if (!env->raw_var)
		return (0);
	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (ft_free(env->raw_var), 0);
	env->raw_var[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	if (!env->raw_var[0])
		return (ft_free(env->raw_var), 0);
	env->raw_var[1] = ft_strdup("SHLVL=0");
	if (!env->raw_var[1])
		return (ft_free(env->raw_var), 0);
	env->raw_var[2] = ft_strdup("_=./minishell");
	if (!env->raw_var[2])
		return (ft_free(env->raw_var), 0);
	env->raw_var[3] = ft_strdup("OLDPWD");
	if (!env->raw_var[3])
		return (ft_free(env->raw_var), 0);
	return (1);
}
