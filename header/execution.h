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
	size_t	heredoc_amount;
}				t_exec;

char	*check_against_cmd(t_lex *node, char **pathlist);
void	freepaths(char **pathlist);
char	**get_path_array(char **envp);
int		redirect_and_filecheck(t_redirect *head);
void	spawn_children(t_minishell *mini);
int		name_heredocs(t_minishell *mini);
void	clear_heredoc_fns(t_lex *cmds);
#endif
