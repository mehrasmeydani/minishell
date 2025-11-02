/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:32 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:33 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_redirect	*redirect_new(char *in, int i)
{
	t_redirect	*out;

	out = (t_redirect *)ft_calloc(1, sizeof(t_redirect));
	if (!out)
		return (NULL);
	out->name = in;
	out->level = i;
	return (out);
}
