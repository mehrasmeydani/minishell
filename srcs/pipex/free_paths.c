/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:42:07 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:42:08 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

void	freepaths(char **pathlist)
{
	size_t	i;

	if (!pathlist)
		return ;
	i = 0;
	while (pathlist[i] != NULL)
	{
		free(pathlist[i]);
		pathlist[i] = NULL;
		i++;
	}
	free(pathlist);
}
