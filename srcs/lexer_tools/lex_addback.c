/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:41 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:41 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	lex_addback(t_lex **lex, t_lex *new)
{
	t_lex	*tmp;

	if (lex)
	{
		tmp = lex_last(*lex);
		if (tmp)
			(tmp)->next = new;
		else
			*lex = new;
	}
}
