#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_expands
{
	char				*str;
	int					quotes;
	struct s_expands	*next;
}	t_expands;

typedef struct s_expand
{
	t_expands	**exp;
	ssize_t		len;
}	t_expand;

t_expands	*exp_new(char *in);
t_expands	*exp_last(t_expands *exp);
void		exp_delone(t_expands *exp, char *(*del)(char *));
void		exp_clear(t_expands **exp, char *(*del)(char *));
void		exp_addback(t_expands **exp, t_expands *new);
char		**exp_split(char *in);

#endif