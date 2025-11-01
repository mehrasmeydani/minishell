#ifndef MINISHELL_H
# define MINISHELL_H

# define __USE_POSIX 1

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "./libft.h"
# include "./redirect.h"
# include "./lexer.h"
# include "./env.h"
# include "./expand.h"
# include <limits.h>
# include "./execution.h"

# define SINGLE 1
# define DOUBLE 2

typedef unsigned int	t_ui;
typedef struct s_minishell
{
	char		*in;
	char		**out;
	t_lex		*lex;
	t_expand	expd;
	t_env		env;
	int			error_code;
}	t_minishell;

int		quotes(char c, int *state);
char	*ft_relocat(char *in, char *buff);
int		remove_quotes(char **in);
int		remove_quotes_2(char **in);
char	**ft_duostrdup(char **in, ssize_t len);
char	**ft_free(char **in);
size_t	ft_str_str_len(char **in);
int		check_heredoc(t_lex *lex);

/*********************built ins*********************/

int		cd(t_minishell *mini, char **cmd);
int		pwd(void);
void	echo(char **cmd);
void	env(t_minishell *mini);
int		my_export(t_minishell *mini, char **cmd);
int		is_builtin(char **cmd);
int		unset(t_minishell *mini, char **cmd);

/********************readfile***********************/

int		my_read(t_minishell *mini);
char	**mini_split(char *in);

/*********************expansion*********************/

int		expand_all(t_minishell *mini);
char	*expand(t_minishell *mini, char *in, int here_doc);

/**********************env var**********************/

int		set_var(t_minishell *mini, char **env_var, bool first);
int		preset_var(t_env *env);
ssize_t	var_exists(t_env *env, char	*input, char *tmp);
void	free_env(t_env *env);

#endif
