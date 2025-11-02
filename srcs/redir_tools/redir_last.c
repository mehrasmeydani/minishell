/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:29 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:30 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_redirect	*redirect_last(t_redirect *redirect)
{
	while (redirect && redirect->next)
		redirect = redirect->next;
	return (redirect);
}
