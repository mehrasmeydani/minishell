#include "../../header/execution.h" // cahnge to the header folder on merge
static void	check_infile(t_redirect *file)
{
	if (access(file->name, F_OK) == -1)
	{
		perror(file->name);
		file->fd = FAIL;
		return ;
	}
	if (access(file->name, R_OK) == 0)
		file->fd = open(file->name, O_RDONLY);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

static void	check_outfile(t_redirect *file)
{
	if(access(file->name, F_OK) == -1)
		file->fd = open(file->name, O_WRONLY | O_CREAT, 0644);
	else if (access(file->name, W_OK) == 0)
		file->fd = open(file->name, O_WRONLY | O_TRUNC);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

static void	check_append(t_redirect *file)
{
	if(access(file->name, F_OK) == -1)
		file->fd = open(file->name, O_WRONLY | O_CREAT, 0644);
	else if (access(file->name, W_OK) == 0)
		file->fd = open(file->name, O_WRONLY | O_APPEND);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}


/*static void	check_heredoc(t_redirect *file) // filenames need to be generated in the temp name
{
	
	file->fd = open("test", O_CREAT | O_RDWR, 0600);
	if (file->fd == -1)
	{
		perror("heredoc");
		return ;
	}
	write(file->fd, file->input, ft_strlen(file->input));
	close(file->fd);
	file->fd = open("test", O_RDONLY);
	if (file->fd == -1)
	{
		perror("heredoc");
		return ;
	}
}
*/
static void	dup_redirs(t_redirect *file)
{
	if (file->level == INFILE || file->level == HEREDOC) // or heredoc
	{
		if (dup2(file->fd, STDIN_FILENO) == -1)
				file->fd = FAIL; // clean up!
		close(file->fd);
	}
	if (file->level == OUTFILE || file->level == APPEND)
	{
		if (dup2 (file->fd, STDOUT_FILENO) == -1)
			file->fd = FAIL; //clean up!
		close(file->fd);
	}
}

int	redirect_and_filecheck(t_redirect *head)
{
	// by this point, pipe should already be duped into in/out
	// here, i should also close all fds of the redirs, and free the redirs struct
	t_redirect	*temp;
	
	temp = head;
	while(temp != NULL)
	{
		if (temp->level == INFILE || temp->level == HEREDOC)
			check_infile(temp);
		else if (temp->level == OUTFILE)
			check_outfile(temp);
		else if (temp->level == APPEND)
			check_append(temp);
		if (temp->fd == FAIL)
			return (-1); // child should be cleaned of memory, fds, etc.take into account this might be in parent
		dup_redirs(temp);
		if (temp->fd == FAIL)
			return(perror("dup redirections"), -1);
		temp = temp->next;
	}
	return (1);
}

