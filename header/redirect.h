/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:05 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:06 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

enum e_redirect_level
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
};

typedef enum e_redirect_level	t_redir_type;

typedef struct s_redirect
{
	char				*name;
	int					fd;
	char				*input;
	int					input_expand;
	t_redir_type		level;
	struct s_redirect	*next;
}	t_redirect;

void		redirect_addback(t_redirect **redirect, t_redirect *add);
void		redirect_clear(t_redirect **redirect, void (*del)(void *));
void		redirect_delone(t_redirect *redirect, void (*del)(void *));
t_redirect	*redirect_new(char *in, int i);
t_redirect	*redirect_last(t_redirect *redirect);

#endif
