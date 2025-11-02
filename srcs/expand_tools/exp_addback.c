/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:55 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:56 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exp_addback(t_expands **exp, t_expands *new)
{
	t_expands	*tmp;

	if (exp)
	{
		tmp = exp_last(*exp);
		if (tmp)
		{
			(tmp)->next = new;
			if (new)
				new->prev = tmp;
		}
		else
			*exp = new;
	}
}
