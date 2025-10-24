#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

typedef struct s_expands
{
	char				*str;
	char				**expanded;
	bool				behind_space;
	bool				after_space;
	int					quotes;
	struct s_expands	*next;
	struct s_expands	*prev;
}	t_expands;

typedef struct s_expand
{
	t_expands	**exp;
	ssize_t		len;
}	t_expand;

t_expands	*exp_new(char *in, bool back_space, bool front_space, int quotes);
t_expands	*exp_last(t_expands *exp);
void		exp_delone(t_expands *exp, void (*del)(void *));
void		exp_clear(t_expands **exp, void (*del)(void *));
void		exp_addback(t_expands **exp, t_expands *new);
char		**exp_split(char *in);
int			is_valid_env(char c, int j);
char		**split_2(char *str, char *charset);
void		exp_removeandinject(t_expands **_exp, t_expands *remove, t_expands *add);

#endif