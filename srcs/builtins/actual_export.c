/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:17 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	my_export(t_minishell *mini, char **cmd)
{
	if (ft_str_str_len(cmd) > 1)
		return (add_var(mini, cmd));
	else
		print_export(mini);
	return (1);
}
