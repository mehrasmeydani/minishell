/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:04 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:04 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	exp_delone(t_expands *exp, void (*del)(void *))
{
	if (exp && del)
	{
		(*del)(exp->str);
		free(exp);
	}
}
