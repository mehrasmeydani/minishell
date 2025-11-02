/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:45:13 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:45:14 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_lex	*lex_new(char **in)
{
	t_lex	*out;

	out = (t_lex *)ft_calloc(1, sizeof(t_lex));
	if (!out)
		return (NULL);
	out->cmd = in;
	return (out);
}
