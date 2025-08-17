#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SINGLE 1
# define DOUBLE 2

typedef unsigned int	t_ui;

typedef struct s_lex
{
	char	*in;
	char	**out;
	ssize_t	num_pipes;
}	t_lex;

typedef struct s_minishell
{
	char	**env;
	t_lex	*lex;
}	t_minishell;

int		my_read(t_minishell *mini, t_lex *lex);
char	**mini_split(char *in);
int 	quotes(char c, int *state);

#endif