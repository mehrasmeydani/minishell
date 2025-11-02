/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:30 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:30 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	env(t_minishell *mini)
{
	ssize_t	i;

	i = -1;
	while (mini->env.raw_var[++i])
		if (mini->env.var_value[i])
			ft_putendl_fd(mini->env.raw_var[i], STDOUT_FILENO);
}
