#include "../../header/execution.h"
// NULL t_lext->cmd[0] means the command wont be run as it does not exist!
// how we handle redirections without commands like " < test2 > test4 > test7  | ls"
char	*check_against_cmd(t_lex *node, char **pathlist)
{
	ssize_t	i;
	char	*new_cmd;
	
	i = -1;
	while(pathlist[++i] != NULL)
	{
		new_cmd = ft_strjoin(pathlist[i], node->cmd[0]);
		if (!new_cmd)
			return (perror(node->cmd[0]), NULL);
		if (access(new_cmd, F_OK) == 0 && access(new_cmd, X_OK) == 0)
			return (new_cmd);
		free(new_cmd);
	}
	return (NULL);
}

// actually, i think it's better to have each child check its own cmd, ensuring
// errors are printed accurately and in order, plus parity for the pipeline logic.
// i leave this function here in case i decide not to do that later for any reason.
/*void	cmd_path_replace(t_lex *head, char **pathlist)
{
	t_lex	*temp;
	char	*temp_cmd;
	
	temp = head;
	while (temp != NULL)
	{
		// first check in the builtins, consider heredoc too
		temp_cmd = check_against_cmd(temp, pathlist);
		free(temp->cmd[0]);
		temp->cmd[0] = temp_cmd;
		temp = temp->next;
	}
}*/
