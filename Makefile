EXPAND2_PRE	= expansion/
EXPAND2_SRC	= expansion.c expansion_helper.c redirect_expansion.c expansion_helper2.c redric_helper.c

EXPAND_PRE	= expand_tools/
EXPAND_SRC	= exp_addback.c exp_clear.c exp_delone.c exp_last.c exp_new.c exp_split.c\
			exp_removeinject.c exp_len.c exp_split_helper.c

REDIR_PRE	= redir_tools/
REDIR_SRC	= redir_addback.c redir_clear.c redir_delone.c redir_last.c redir_new.c 

LEX_PRE		= lexer_tools/
LEX_SRC		= lex_addback.c lex_clear.c lex_delone.c lex_last.c lex_new.c

PIPE_PRE	= pipex/
PIPE_SRC	= child_spawning.c command_check.c file_check.c free_paths.c path_construct.c \
			heredoc_filegen.c backup_fds.c close_and_exit.c fill_data_pre_exec.c pipe_dup.c \
			exec_signals.c wait_for_death.c run_builtin.c exec_wrappers.c cmd_with_slashes.c

BUILT_PRE	= builtins/
BUILT_SRC	= env.c export.c echo.c cd.c pwd.c unset.c my_exit.c actual_export.c export_helper.c

SRC			= main.c ft_free.c mini_split.c my_read.c quotes.c ft_duostrdup.c lexer.c\
			${addprefix ${LEX_PRE}, ${LEX_SRC}} ${addprefix ${REDIR_PRE}, ${REDIR_SRC}}\
			remove_quotes.c expand.c preset_var.c env_var.c ${addprefix ${PIPE_PRE}, ${PIPE_SRC}}\
			${addprefix ${BUILT_PRE}, ${BUILT_SRC}} builtin.c ${addprefix ${EXPAND_PRE}, ${EXPAND_SRC}}\
			split_2.c lexer_helper.c ${addprefix ${EXPAND2_PRE}, ${EXPAND2_SRC}} ft_relocat.c\
			heredoc.c ft_free_free.c env_var_helper.c expand_helper.c heredoc_helper.c
SRCS		= ${addprefix ${PRE}, ${SRC}}
PRE			= ./srcs/
HEAD		= ./header/
NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= cd libft
OBJS		= ${SRCS:.c=.o}
RM			= rm -f
CC			= cc
MAKEFLAGS	+= --no-print-directory

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o} -g

${NAME}:	${OBJS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} -I ${HEAD} ${OBJS} -o ${NAME} ./libft/libft.a -lreadline -g

clean: 
			@(${LIBFT} && make clean)
			${RM} ${OBJS}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME}
			rm -rf mstest*

re:			fclean all clean
			

.PHONY:		all clean fclean re
