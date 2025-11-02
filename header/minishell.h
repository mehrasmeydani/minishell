/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:43:01 by alvcampo          #+#    #+#             */
/*   Updated: 2025/11/02 17:43:03 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define __USE_POSIX 1

# include "./libft.h"
# include "./redirect.h"
# include "./lexer.h"
# include "./env.h"
# include "./expand.h"
# include "./execution.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <limits.h>

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
int		check_heredoc(t_lex *lex, t_minishell *mini);
int		find_var(char **var, char *in, ssize_t len, t_env env);
int		heredoc_eof(t_redirect *tmp);

/*********************built ins*********************/

int		cd(t_minishell *mini, char **cmd);
int		pwd(void);
void	echo(char **cmd);
void	env(t_minishell *mini);
int		my_export(t_minishell *mini, char **cmd);
int		is_builtin(char **cmd);
int		unset(t_minishell *mini, char **cmd);
void	builtin_exit(t_exec *exec, t_minishell *mini, char **cmd);
void	print_export(t_minishell *mini);
int		add_var(t_minishell *mini, char **cmd);

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

/*********************split exp*********************/

void	str_helper1(char **in, ssize_t *i, int *q_s, int *prev_status);
void	str_helper2(char **in, ssize_t *i);
void	count_helper2(char *in, ssize_t *i);
void	count_helper(char *in, ssize_t *i, int *q_s, int *prev);
int		quotes2(char c, int *state);

#endif
