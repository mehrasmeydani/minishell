#ifndef EXECUTION_H
# define EXECUTION_H

# define FAIL -1

# include "./minishell.h"
#include <sys/wait.h>

typedef struct	s_exec
{
	char	**pathlist;
	size_t children_count;
	pid_t	*pids;
	int		pipe[2][2];
	int		status;
	int		backup_stdin;
	int		backup_stdout;
}				t_exec;

char	*check_against_cmd(t_lex *node, char **pathlist);
void	freepaths(char **pathlist);
char	**get_path_array(char **envp);
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
void my_pipe_dup(t_minishell *mini, t_exec *exec, size_t i);
void	my_pipe_dup_close(t_exec *exec, size_t i);
#endif
