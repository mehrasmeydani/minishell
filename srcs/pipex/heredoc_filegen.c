#include "../../header/minishell.h"

void	gen_filename(t_redirect *file)
{
	char	*origin_str;
	char	filename[23];
	size_t	i;

	file->name = NULL;
	origin_str = "/tmp/here_doc_00000000";
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
	t_redirect *files;
	while(cmds != NULL)
	{
		files = cmds->redic;
		while(files != NULL)
		{
			if (files->level == HEREDOC && files->name != NULL)
			{
				if (access(files->name, F_OK) != -1)
					unlink(files->name);
				free(files->name);
				files->name = NULL;
			}
			files = files->next;
		}
		cmds = cmds->next;
	}
}
int	cpy_heredoc(t_redirect *file)
{
	int	fd;
	fd = open(file->name, O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		return (0);
	if (write(fd, file->input, ft_strlen(file->input)) == -1)
		return (close(fd), 0);
	close(fd);
	return (1);
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
					return (clear_heredoc_fns(mini->lex),
						perror("heredoc name"), -1);
				if(!cpy_heredoc(files))
					return (clear_heredoc_fns(mini->lex),
						perror("heredoc copy"), -1);
			}
			files = files->next;
		}
		cmds = cmds->next;
	}
	return (1);
}

