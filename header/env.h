/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:42:41 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:42:43 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char	**raw_var;
	char	**var_name;
	char	**var_value;
	char	**var_pass_to_exec;
	ssize_t	allocated_l;
}	t_env;

int	set_pass_to_exec(t_env *env);
int	shlvl_i(t_env *env, int lvl, ssize_t i);
int	set_name_value(t_env *env, int start);

#endif
