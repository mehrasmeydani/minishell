#include "../../header/minishell.h"

void	gen_filename(t_redirect *file)
{
	if (access())
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

}
