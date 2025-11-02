/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:59 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:00 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exp_clear(t_expands **exp, void (*del)(void *))
{
	t_expands	*tmp;

	if (exp && del)
	{
		while (*exp)
		{
			tmp = *exp;
			*exp = (*exp)->next;
			exp_delone(tmp, del);
		}
	}
}
