/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:47 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:48 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	lex_clear(t_lex **lex, char **(*del)(char **))
{
	t_lex	*tmp;

	if (lex && del)
	{
		while (*lex)
		{
			tmp = *lex;
			*lex = (*lex)->next;
			redirect_clear(&tmp->redic, free);
			lex_delone(tmp, del);
		}
	}
}
