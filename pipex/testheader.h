#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// ===== constants =====
#define FAIL    -1
#define INFILE   0
#define OUTFILE  1
#define APPEND   2

// ===== struct =====
typedef struct s_redirect
{
    char                *name;
    int                 fd;
    int                 level;
    struct s_redirect   *next;
}   t_redirect;

// ===== prototypes from your code =====
void    check_infile(t_redirect *file);
void    check_outfile(t_redirect *file);
void    check_append(t_redirect *file);
void    dup_redirs(t_redirect *file);
void    open_fds(t_redirect *head);


