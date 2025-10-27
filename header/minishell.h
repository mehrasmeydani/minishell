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

# include "./execution.h"

int		my_read(t_minishell *mini);
char	**mini_split(char *in);
int		quotes(char c, int *state);
char	**ft_free(char **in);
size_t	ft_str_str_len(char **in);
char	**ft_duostrdup(char **in, ssize_t len);
int		remove_quotes(char **in);
char	*ft_relocat(char *in, char *buff);
char	*expand(t_minishell *mini, char *in, t_env env, int here_doc);
int		preset_var(t_env *env);
void	free_env(t_env *env);
int		set_var(t_minishell *mini, char **env_var, bool first);
int		is_builtin(char **cmd);
void	env(t_minishell *mini);
int		export(t_minishell *mini, char **cmd);
int		expand_all(t_minishell *mini); //change
void	echo(char **cmd);
int		remove_quotes_2(char **in);
int		cd(t_minishell *mini, char **cmd);
int		pwd(void);
ssize_t	var_exists(t_env *env, char	*input, char *tmp);
int		unset(t_minishell *mini, char **cmd);

#endif
