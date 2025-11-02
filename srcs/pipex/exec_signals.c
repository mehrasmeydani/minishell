#include "../../header/minishell.h"

extern int g_signaln;

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

