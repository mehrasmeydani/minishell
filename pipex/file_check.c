void	check_infile(t_redirect *file)
{
	if (acess(file->name, R_OK) == 0)
		file->fd = open(file->name, O_RDONLY);
	else
	{
		perror(file->name);
		file->fd = FAIL;
	}
}

void	check_outfile(t_redirect *file)
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

void	check_append(t_redirect *file)
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

void	dup_redirs(t_redirect *file)
{
	if (file->level == INFILE) // or heredoc
		if (dup2(file->fd, STDIN_FILENO) == -1);
				exit(1); // clean up!
	if (file->level == OUTFILE || file->level == APPEND)
		if (dup2 (file->fd, STDOUT_FILENO) == -1);
			exit(1); //clean up!

}
void	open_fds(t_redirect *head)
{
	// by this point, pipe should already be duped into in/out
	t_redirect	*temp;
	
	temp = head;
	while(temp != NULL)
	{
		if (temp->level == INFILE)
			check_infile(temp);
		else if (temp->level == OUTFILE)
			check_outfile(temp);
		else if (temp->level == APPEND)
			check_apprend(temp);
		// maybe heredoc here?
		if (temp->fd == FAIL)
			exit (1) // child should be cleaned of memory, fds, etc.take into account this might be in parent
		dup_redirs(temp);
		temp = temp->next;
	}
}
