/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:26 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:27 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	redirect_delone(t_redirect *redirect, void (*del)(void *))
{
	if (redirect && del)
	{
		(*del)(redirect->name);
		(*del)(redirect->input);
		free(redirect);
	}
}
