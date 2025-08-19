#ifndef LEXER_H
# define LEXER_H

# include "redirect.h"
# include "minishell.h"

typedef struct s_lex
{
	char			**cmd;
	t_redirect		*redic;
	struct s_lex	*next;
}	t_lex;

void	lex_delone(t_lex *lex, char **(*del)(char **, ssize_t), ssize_t i);
void	lex_clear(t_lex **lex, char **(*del)(char **, ssize_t));
t_lex	*lex_last(t_lex *lex);
void	lex_addback(t_lex **lex, t_lex *new);
t_lex	*lex_new(char **in);
t_lex	*lexer(char **in);

#endif
