/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:10 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:10 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

ssize_t	exp_len(t_expands *exp)
{
	ssize_t	i;

	i = 0;
	while (exp)
	{
		i++;
		exp = exp->next;
	}
	return (i);
}
