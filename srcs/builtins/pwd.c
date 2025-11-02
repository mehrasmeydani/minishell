/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:46 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:47 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	pwd(void)
{
	char	*currdir;

	currdir = getcwd(NULL, 0);
	if (!currdir)
		return (0);
	write(STDOUT_FILENO, currdir, ft_strlen(currdir));
	write(STDOUT_FILENO, "\n", 1);
	free(currdir);
	return (1);
}
