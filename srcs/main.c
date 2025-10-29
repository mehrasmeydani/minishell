#include "../header/minishell.h"

int g_signaln = 0;

void	sigint(int sig)
{
	rl_on_new_line();
	ft_putendl_fd("", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_signaln = sig;
}

void	execution(t_minishell *mini)
{
	if (name_heredocs(mini) == -1)
		return ; //failure, freeing and deleting handled
	spawn_children(mini);
	clear_heredoc_fns(mini->lex);
}

void	set_zero(t_minishell *mini)
{
	if (mini)
	{
		mini->in = NULL;
		mini->out = NULL;
		mini->lex = NULL;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	(void)env;
	ft_bzero(&mini, sizeof(mini));
	set_var(&mini, env, 1);
	while (true)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sigint);
		set_zero(&mini);
		if (!my_read(&mini))
			return (free_env(&mini.env), mini.error_code);
		if (!mini.lex)
			continue ;
		execution(&mini);
		lex_clear(&mini.lex, ft_free);
	}
}
