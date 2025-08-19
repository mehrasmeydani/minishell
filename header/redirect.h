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
	t_redir_type		level;
	struct s_redirect	*next;
}	t_redirect;

#endif