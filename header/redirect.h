#ifndef REDIRECT_H
# define REDIRECT_H

enum e_redirect_level
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
};

typedef enum e_redirect_level	t_redir_type;

typedef struct s_redirect
{
	char				*name;
	int					fd;
	char				*input;
	int					input_expand;
	t_redir_type		level;
	struct s_redirect	*next;
}	t_redirect;

void		redirect_addback(t_redirect **redirect, t_redirect *new);
void		redirect_clear(t_redirect **redirect, void (*del)(void *));
void		redirect_delone(t_redirect *redirect, void (*del)(void *));
t_redirect	*redirect_new(char *in, int i);
t_redirect	*redirect_last(t_redirect *redirect);

#endif