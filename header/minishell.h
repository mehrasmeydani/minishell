#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include "./redirect.h"
# include "./lexer.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SINGLE 1
# define DOUBLE 2

typedef unsigned int	t_ui;
typedef struct s_minishell
{
	char	**env;
	char	*in;
	char	**out;
	ssize_t	num_pipes;
	t_lex	*lex;

}	t_minishell;

int		my_read(t_minishell *mini);
char	**mini_split(char *in);
int		quotes(char c, int *state);
char	**ft_free(char **in, ssize_t i);
size_t	ft_str_str_len(char **in);
char	**ft_duostrdup(char **in, ssize_t len);
int	remove_quotes(char **in);

#endif