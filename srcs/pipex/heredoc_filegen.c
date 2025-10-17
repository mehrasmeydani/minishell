#include "../../header/minishell.h"

void	gen_filename(t_redirect *file)
{
	char	*origin_str;
	char	filename[23];
	size_t	i;

	file->name = NULL;
	origin_str = "/tmp/here_doc/00000000";
	ft_bzero(filename, 23);
	i = 14;
	ft_strlcpy(filename, origin_str, 23);
	if (access("/tmp", F_OK | X_OK) == -1)
		return ;
	while (access(filename, F_OK) != -1)
	{
		if (filename[i] != '9')
			filename[i]++;
		else
			i++;
		if (i == 21 && filename[21] == '9')
			return ;
	}
	file->name = ft_calloc(23, sizeof(char)); // remember to free when unlinking files
	if (!file->name)
		return ;
	ft_strlcpy(file->name, filename, 23);
}
void	clear_heredoc_fns(t_lex *cmds)
{
	t_lex *cmds;
	t_redirect *files;
}
int	cpy_heredoc(t_redirect *file)
{
	int	fd;
	fd = open(file->name, O_WRONLY);
	if (fd = -1)
}
int	name_heredocs(t_minishell *mini)
{
	t_lex	*cmds;
	t_redirect	*files;
	cmds = mini->lex;

	while(cmds != NULL)
	{
		files = cmds->redic;
		while(files != NULL)
		{
			if(files->level == HEREDOC)
			{
				gen_filename(files);
				if (files->name == NULL)
					return (perror("heredoc name"), -1);
			}
			files = files->next;
		}
		cmds = cmds->next;
	}
	return (1);
}

