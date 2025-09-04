/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvcampo <alvcampo@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:25:08 by alvcampo          #+#    #+#             */
/*   Updated: 2025/09/04 19:55:49 by alvcampo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define YES 1
# define NO 0
# define FAIL -1
# define CMD1 1
# define CMD2 2
# define ALLCMDS 3
# define CLOSED -1
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

typedef struct	s_parts
{
	char	**pathlist;
	int		splitlen;
	int		fdout;
	int		fdin;
	char	**cmd1;
	char	**cmd2;
	int		pid1;
	int		pid2;
	int		status;
	int		cmds_fail;
}				t_parts;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	parseinput(t_parts *parts, char **argv, int argc);
char	**ft_split(const char *s, char c);
void	getpatharray(t_parts *parts, char **envp);
char	*ft_strdup(const char *s);
char	*partialjoin(const char *s1, const char *s2, int len2);
char	***buildargvs(t_parts *parts, char **argv, int argc);
char	*ft_strchr(const char *s, int c);
void	check_heredoc(t_parts *parts, char **argv);
void	check_files(t_parts *parts, int argc, char **argv);
int		splitlen(char **split);
void	freetable(char **strarray, int words);
void	freepaths(t_parts *parts);
void	labor(t_parts *parts, int argc);
void	set_commands(t_parts *parts, char **argv);
void	free_cmds(t_parts *parts, int cmd);
void	have_a_child(t_parts *parts, char **envp);
void	init_pids_status(t_parts *parts);
void	clean_children(t_parts *parts, int *pipes, int cmd);
void	set_exit_status(t_parts *parts, int use, int status1, int status2);
#endif
