#include "../header/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	(void)argc;
	(void)argv;
	(void)env;
	while (true)
	{
		ft_bzero(&mini, sizeof(mini));
		if (!my_read(&mini))
			return (1);
	}
}
