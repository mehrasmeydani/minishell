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

extern sig_atomic_t	g_signaln;

void	sig_handler_quit(int sig)
{
	g_signaln = sig;
}
