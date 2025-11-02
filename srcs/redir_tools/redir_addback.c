/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_addback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:20 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:21 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	redirect_addback(t_redirect **redirect, t_redirect *new)
{
	t_redirect	*tmp;

	if (redirect)
	{
		tmp = redirect_last(*redirect);
		if (tmp)
			(tmp)->next = new;
		else
			*redirect = new;
	}
}
