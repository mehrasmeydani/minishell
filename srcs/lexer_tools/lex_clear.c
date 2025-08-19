#include "../header/minishell.h"

void	lex_clear(t_lex **lex, char **(*del)(char **, ssize_t))
{
	t_lex	*tmp;

	if (lex && del)
	{
		while (*lex)
		{
			tmp = *lex;
			*lex = (*lex)->next;
			redirect_clear(&tmp->redic, free);
			lex_delone(tmp, del, ft_str_str_len(tmp->cmd));
		}
	}
}
