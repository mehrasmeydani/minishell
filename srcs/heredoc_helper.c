/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:46:07 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:46:08 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	heredoc_eof(t_redirect *tmp)
{
	if (tmp->input)
	{
		tmp->input = ft_relocat(tmp->input, "\n");
		if (!tmp->input)
			return (0);
	}
	return (ft_putendl_fd("Warning: EOF!", 2),
		free(tmp->name), tmp->name = NULL, -1);
}
