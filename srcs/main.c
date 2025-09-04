#include "../header/minishell.h"

void	sigint(int sig)
{
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	(void)env;
	while (true)
	{
		signal(SIGQUIT, SIG_IGN); //
		signal(SIGINT, sigint);
		ft_bzero(&mini, sizeof(mini));
		if (!my_read(&mini))
			return (1);
		//signal(SIGINT, SIG_IGN);
		open("lol.tmp", __O_TMPFILE);
		lex_clear(&mini.lex, ft_free);
	}
}
