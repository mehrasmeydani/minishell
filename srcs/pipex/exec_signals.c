/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:41:49 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:41:50 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

extern int	g_signaln;

void	sig_handler_int_parent(int sig)
{
	g_signaln = sig;
	rl_on_new_line();
	ft_putendl_fd("", 0);
	rl_replace_line("", 0);
}

void	sig_handler_quit(int sig)
{
	g_signaln = sig;
	rl_on_new_line();
	ft_putendl_fd("", 0);
	rl_replace_line("", 0);
	exit(sig + 128);
}

void	sig_handler_quit_parent(int sig)
{
	(void)sig;
	rl_on_new_line();
	ft_putendl_fd("", 0);
	rl_replace_line("", 0);
}
