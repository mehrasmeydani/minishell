#include "../../header/execution.h"
// NULL t_lext->cmd[0] means the command wont be run as it does not exist!
// how we handle redirections without commands like " < test2 > test4 > test7  | ls"
char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode)
{
	ssize_t	i;
	char	*new_cmd;
	
	*errorcode = -1;
	i = -1;
	while(pathlist[++i] != NULL)
	{
		new_cmd = ft_strjoin(pathlist[i], node->cmd[0]);
		if (errno == ENOMEM)
		{
			perror("cmd allocation");
			*errorcode = 1;
		}
		if (!new_cmd)
		{
		if (*errorcode != 1)
				*errorcode = 0;
			return (NULL);
		}
		// THIS ERROR CODE HANDLING!
		if (access(new_cmd, F_OK) == 0 && access(new_cmd, X_OK) == 0)
		{
			*errorcode = 1;
			return (new_cmd);
		}
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
