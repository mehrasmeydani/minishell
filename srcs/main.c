#include "../header/minishell.h"

void	sigint(int sig)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	execution(t_minishell *mini)
{
	spawn_children(mini);
}

void	set_zero(t_minishell *mini)
{
	if (mini)
	{
		mini->error_code = 0;
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
		signal(SIGQUIT, SIG_IGN); //
		signal(SIGINT, sigint);
		set_zero(&mini);
		if (!my_read(&mini))
			return (free_env(&mini.env), 1);
		execution(&mini);
		lex_clear(&mini.lex, ft_free);
	}
}
