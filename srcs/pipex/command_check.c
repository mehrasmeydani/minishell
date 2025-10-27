#include "../../header/execution.h"
// NULL t_lext->cmd[0] means the command wont be run as it does not exist!
// how we handle redirections without commands like " < test2 > test4 > test7  | ls"

char	*get_cmd_absolute(char *cmd, int *errorcode)
{
	char	*new_cmd;

	new_cmd = ft_strdup(cmd);
	if (!new_cmd)
		return(*errorcode = 1, (NULL));
	if (access(new_cmd, F_OK) == 0)
	{
		if (access(new_cmd, X_OK) == 0)
			return(new_cmd);
		else
			return(free(new_cmd), *errorcode = 126, NULL);
	}
	return(free(new_cmd), *errorcode = 127, NULL);
}

char	*check_against_cmd(t_lex *node, char **pathlist, int *errorcode)
{
	ssize_t	i;
	char	*new_cmd;
	
	i = -1;

	new_cmd = NULL;
	errno = 0;
	if (node->cmd[0] == NULL)
		return (NULL);
	if (ft_strchr(node->cmd[0], '/') != NULL)
		return (new_cmd = get_cmd_absolute(node->cmd[0], errorcode));
	if (!pathlist)
		return (*errorcode = 127, errno = ENOENT, NULL);
	while (pathlist[++i] != NULL)
	{
		new_cmd = ft_strjoin(pathlist[i], node->cmd[0]);
		if (!new_cmd)
			return (*errorcode = 1, perror("command alloc"), NULL);
		if (access(new_cmd, F_OK) == 0)
			break ;
		free(new_cmd);
		if(pathlist[i+1] == NULL)
			return (*errorcode = 127, NULL);
	}
		if (access(new_cmd, X_OK) != 0)
			return(free(new_cmd), *errorcode = 126, NULL);
		return(new_cmd);
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
