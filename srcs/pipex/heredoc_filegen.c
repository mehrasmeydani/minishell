#include "../../header/minishell.h"


void	gen_filename(t_redirect *file)
{
	ssize_t	i;
	char	*num;

	file->name = NULL;
	num = NULL;
	if (access("/tmp", F_OK | X_OK) == -1)
		return ;
	i = -1;
	while(++i <= 100000)
	{
		num = ft_itoa(i);
		if (!num)
			return ;
		file->name = ft_strjoin("/tmp/here_doc_", num);
		free(num);
		if (!file->name)
			return ;
		if (access(file->name, F_OK) != 0)
			return ;
		free(file->name);
		file->name = NULL;
	}
	errno = EEXIST;
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

