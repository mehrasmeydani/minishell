#ifndef EXECUTION_H
# define EXECUTION_H

# define FAIL -1

# include "../header/minishell.h"
#include <sys/wait.h>
typedef struct	s_exec
{
	char	**pathlist;
	size_t children_count;
	pid_t	*pids;
	int		pipe[2][2];
	int		status;
}				t_exec;

void	open_fds(t_redirect *head);
char	*check_against_cmd(t_lex *node, char **pathlist);
void	freepaths(char **pathlist);
char	**get_path_array(char **envp);
int	redirect_and_filecheck(t_redirect *head);

#endif
