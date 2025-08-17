#include "../header/minishell.h"



int main(int argc, char **argv, char **env)
{
	t_minishell mini;
	t_lex		lex;

	(void)argc;
	(void)argv;
	(void)env;
	mini.lex = &lex;
	while (true)
	{
		my_read(&mini, &lex);
	}
}