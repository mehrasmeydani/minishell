/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_delone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:04 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:05 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	lex_delone(t_lex *lex, char **(*del)(char **))
{
	if (lex && del)
	{
		(*del)(lex->cmd);
		free(lex);
	}
}
