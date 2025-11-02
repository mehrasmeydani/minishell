/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:23 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:24 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	redirect_clear(t_redirect **redirect, void (*del)(void *))
{
	t_redirect	*tmp;

	if (redirect)
	{
		while (*redirect)
		{
			tmp = *redirect;
			*redirect = (*redirect)->next;
			redirect_delone(tmp, del);
		}
	}
}
