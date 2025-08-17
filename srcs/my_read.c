#include "../header/minishell.h"

int	my_read(t_minishell *mini, t_lex *lex)
{
	(void)mini;
	lex->in = readline("minishell>");
	if (!lex->in)
		return (0);
	lex->out = mini_split(lex->in);
	if (!lex->out)
		return (1);
	for (size_t i = 0; lex->out[i]; i++)
	{
		printf("%s\n", lex->out[i]);
	}
	return (1);
}