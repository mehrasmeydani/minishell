#ifndef EXECUTION_H
# define EXECUTION_H

# define FAIL -1

# include "redirect.h"
# include "lexer.h"
# include <sys/wait.h>
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>

typedef struct s_minishell	t_minishell;
typedef struct s_exec
{
	char	**pathlist;
	size_t	children_count;
	pid_t	*pids;
	int		pipe[2][2];
	int		status;
	int		backup_stdin;
	int		backup_stdout;
}	t_exec;

char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode);
void	freepaths(char **pathlist);
char	**get_path_array(char **envp, bool *isemptypath);
int		redirect_and_filecheck(t_redirect *head);
void	spawn_children(t_minishell *mini);
int		name_heredocs(t_minishell *mini);
void	clear_heredoc_fns(t_lex *cmds);
void	safe_close_fd(int *fd);
void	close_backups(t_exec *exec);
int		back_up_standardfds(t_exec *exec, t_lex *firstcmd);
int		restore_stdin_stdout(t_exec *exec);
void	close_all_pipes(int pipes[2][2]);
void	close_exit(t_exec *exec, t_minishell *mini, char *error, int ex_code);
void	clean_after_exec(t_exec *exec, t_minishell *mini, char *errormsg);
int		fill_struct(t_exec *exec, t_minishell *mini);
void	my_pipe_dup(t_minishell *mini, t_exec *exec, size_t i);
void	my_pipe_dup_close(t_exec *exec, size_t i);
void	exit_or_return(t_exec *exec, t_minishell *mini, char *error, int excd);
int		exec_builtin(char **cmd, t_minishell *mini, t_exec *exec);
int		is_builtin(char **cmd);
void	ft_free_free(char ***str);
size_t	ft_str_str_len(char **in);
void	sig_handler_int_parent(int sig);
void	sig_handler_quit(int sig);
void	sig_handler_quit_parent(int sig);
void	wait_for_death(t_minishell *mini, t_exec *exec);
void	run_builtin(char **cmd_args, t_minishell *mini, t_exec *exec);

#endif
