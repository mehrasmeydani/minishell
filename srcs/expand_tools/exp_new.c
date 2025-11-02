/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:44:12 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:44:13 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_expands	*exp_new(char *in, bool back_space, bool front_space, int quotes)
{
	t_expands	*out;

	out = (t_expands *)ft_calloc(1, sizeof(t_expands));
	if (!out)
		return (NULL);
	out->quotes = quotes;
	out->str = in;
	out->behind_space = back_space;
	out->after_space = front_space;
	return (out);
}
