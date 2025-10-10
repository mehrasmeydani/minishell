#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft.h"
# include "./redirect.h"
# include "./lexer.h"
# include "./env.h"
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# define SINGLE 1
# define DOUBLE 2

typedef unsigned int	t_ui;
typedef struct s_minishell
{
	char	*in;
	char	**out;
	ssize_t	num_pipes;
	t_lex	*lex;
	t_env	env;
	int		error_code;
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
char	*expand(char *in, t_env env, int);
int		preset_var(t_env *env);
void	free_env(t_env *env);
int		set_var(t_minishell *mini, char **env_var, bool first);
int		is_builtin(char **cmd);
int		exec_builtin(char **cmd, t_minishell *mini);
void	env(t_minishell *mini);
int		export(t_minishell *mini, char **cmd);

#endif