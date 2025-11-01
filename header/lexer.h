#ifndef LEXER_H
# define LEXER_H

# include "redirect.h"
# include <stdio.h>

typedef struct s_lex
{
	char			**cmd;
	t_redirect		*redic;
	struct s_lex	*next;
}	t_lex;

void	lex_delone(t_lex *lex, char **(*del)(char **));
void	lex_clear(t_lex **lex, char **(*del)(char **));
t_lex	*lex_last(t_lex *lex);
void	lex_addback(t_lex **lex, t_lex *add);
t_lex	*lex_new(char **in);
t_lex	*lexer(char **in);
ssize_t	clean_rest_helper(t_lex *tmp);
int		clean_rest_helper2(t_lex *tmp, char **tmp_str);
int		lex_redir_helper(t_lex *lex, t_lex	*tmp, ssize_t i);

#endif
