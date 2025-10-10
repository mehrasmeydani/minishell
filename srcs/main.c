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
		//ft_bzero(&mini, sizeof(mini)); // still needed
		if (!my_read(&mini))
			return (free_env(&mini.env), 1);
		/*int i = -1;
	 	t_lex *lex;
	 	lex = mini.lex;
	 	while (lex)
	 	{
	 		i = -1;
	 		while (lex->cmd[++i])
	 		{
	 			printf("%s\n", lex->cmd[i]);
	 		}
	 		lex = lex->next;
	 	}*/

		execution(&mini);
		lex_clear(&mini.lex, ft_free);
	}
}
