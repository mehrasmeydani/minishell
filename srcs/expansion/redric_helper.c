/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redric_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megardes <megardes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:54:13 by megardes          #+#    #+#             */
/*   Updated: 2025/11/06 17:13:48 by megardes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/expand.h"

int	re_h(int mode, ssize_t i, char *org, ssize_t k)
{
	if (mode == 1)
		return (((i > 0) && (ft_strchr("\t\n\r\v\f ", org[i - 1]))));
	return (((org[i + k]) && (ft_strchr("\t\n\r\v\f ", org[i + k]))));
}

t_expands	*reparse_help(char *in, ssize_t i, ssize_t k, char *org)
{
	char		*tmp2;
	t_expands	*out;

	tmp2 = ft_strdup(in);
	if (!tmp2)
		return (NULL);
	out = exp_new(tmp2, re_h(1, i, org, k), re_h(0, i, org, k), 0);
	if (!out)
		return (free(tmp2), NULL);
	return (out);
}
