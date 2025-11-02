/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:41:58 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:41:59 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/execution.h"

static void	check_infile(t_redirect *file)
{
	if (access(file->name, F_OK) == -1)
	{
		perror(file->name);
		file->fd = FAIL;
		return ;
	}
	if (access(file->name, R_OK) == 0)
		file->fd = open(file->name, O_RDONLY);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

static void	check_outfile(t_redirect *file)
{
	if (access(file->name, F_OK) == -1)
		file->fd = open(file->name, O_WRONLY | O_CREAT, 0644);
	else if (access(file->name, W_OK) == 0)
		file->fd = open(file->name, O_WRONLY | O_TRUNC);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

static void	check_append(t_redirect *file)
{
	if (access(file->name, F_OK) == -1)
		file->fd = open(file->name, O_WRONLY | O_CREAT, 0644);
	else if (access(file->name, W_OK) == 0)
		file->fd = open(file->name, O_WRONLY | O_APPEND);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

static void	dup_redirs(t_redirect *file)
{
	if (file->level == INFILE || file->level == HEREDOC)
	{
		if (dup2(file->fd, STDIN_FILENO) == -1)
		{
			close(file->fd);
			file->fd = FAIL;
			return ;
		}
		close(file->fd);
	}
	if (file->level == OUTFILE || file->level == APPEND)
	{
		if (dup2 (file->fd, STDOUT_FILENO) == -1)
		{
			close(file->fd);
			file->fd = FAIL;
			return ;
		}
		close(file->fd);
	}
}

int	redirect_and_filecheck(t_redirect *head)
{
	t_redirect	*temp;

	temp = head;
	errno = 0;
	while (temp != NULL)
	{
		if (temp->level == INFILE || temp->level == HEREDOC)
			check_infile(temp);
		else if (temp->level == OUTFILE)
			check_outfile(temp);
		else if (temp->level == APPEND)
			check_append(temp);
		if (temp->fd == FAIL)
			return (-1);
		dup_redirs(temp);
		if (temp->fd == FAIL)
			return (perror("dup redirections"), -1);
		temp = temp->next;
	}
	return (1);
}
