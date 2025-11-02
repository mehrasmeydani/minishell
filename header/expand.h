#ifndef EXPAND_H
# define EXPAND_H

# include "redirect.h"
# include <stdbool.h>
# include "libft.h"

typedef struct s_minishell	t_minishell;
typedef struct s_expands
{
	char				*str;
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

typedef struct s_expansion
{
	ssize_t	i;
	ssize_t	j;
	char	*out;
	char	*tmp;
	char	*tmp_var;
	int		quotes_state;
	char	*tmp2;
}	t_expansion;

t_expands	*exp_new(char *in, bool back_space, bool front_space, int quotes);
t_expands	*exp_last(t_expands *exp);
void		exp_delone(t_expands *exp, void (*del)(void *));
void		exp_clear(t_expands **exp, void (*del)(void *));
void		exp_addback(t_expands **exp, t_expands *add);
char		**exp_split(char *in);
int			is_valid_env(char c, int j);
char		**split_2(char *str, char *charset);
void		exp_removeandinject(t_expands **_exp, t_expands *remove,
				t_expands *add);
ssize_t		exp_len(t_expands *exp);
int			redirect_exp(t_minishell *mini, t_redirect *red);
int			exp_reconnect(t_expands **_exp);
int			expand_sub(t_minishell *mini, t_expands **_exp);
t_expands	*create_exp(char **in);
int			exp_remove_quotes(t_expands *exp);
void		ft_free_free(char ***str);
void		free_exp(t_expand *exp);
t_expands	*reparse(char **in, char *org);
int			has_quotes(char *in);
int			is_in(char *str, char *set);
void		remove_quotes_3(char *str);
void		ft_swap(char *a, char *b);
void		exp_exp(t_expands *tmp, char **out);
int			sub_helper(t_expands **_exp, t_expands **exp, char *tmp);

#endif