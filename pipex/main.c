/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:16:59 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/04 19:55:58 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_parts	parts;

	if (argc != 5)
		return (errno = EINVAL, perror("Argument count wrong"), 1);
	check_files(&parts, argc, argv);
	if (parts.fdin == FAIL && parts.fdout == FAIL)
		return (1);
	getpatharray(&parts, envp);
	if (parts.pathlist == NULL)
		return (errno = ENOMEM, perror("Path couldn't be retrieved"), 1);
	set_commands(&parts, argv);
	if (!parts.cmd1 && !parts.cmd2 && parts.cmds_fail == YES)
		return (errno = ENOMEM, perror("cmds couldn't be retrieved"), 1);
	have_a_child(&parts, envp);
	free_cmds(&parts, ALLCMDS);
	if (parts.fdin != FAIL)
		close(parts.fdin);
	if (parts.fdout != FAIL)
		close(parts.fdout);
	exit(parts.status);
}
