/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_removeinject.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:15 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:15 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/expand.h"

void	exp_removeandinject(t_expands **_exp, t_expands *remove, t_expands *add)
{
	t_expands	*tmp;
	t_expands	*tmp2;

	if (_exp)
	{
		tmp = *_exp;
		if (!tmp)
			return ((void)(*_exp = add));
		if (tmp == remove)
		{
			exp_addback(&add, tmp->next);
			exp_delone(tmp, free);
			*_exp = add;
			return ;
		}
		while (tmp && tmp->next && tmp->next != remove)
			tmp = tmp->next;
		tmp2 = tmp->next;
		if (tmp2)
			tmp2 = tmp2->next;
		exp_addback(&add, tmp2);
		exp_delone(tmp->next, free);
		tmp->next = NULL;
		exp_addback(_exp, add);
	}
}
