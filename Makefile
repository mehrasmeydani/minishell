REDIR_PRE		= redir_tools/
REDIR_SRC		= redir_addback.c redir_clear.c redir_delone.c redir_last.c redir_new.c 


LEX_PRE		= lexer_tools/
LEX_SRC		= lex_addback.c lex_clear.c lex_delone.c lex_last.c lex_new.c 
SRC			= main.c ft_free.c mini_split.c my_read.c quotes.c ft_duostrdup.c lexer.c\
			${addprefix ${LEX_PRE}, ${LEX_SRC}} ${addprefix ${REDIR_PRE}, ${REDIR_SRC}}\
			remove_quotes.c expand.c
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
			@${CC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o} -g

${NAME}:	${OBJS}
			@(${LIBFT} && make all)
			cc ${CFLAGS} -I ${HEAD} ${OBJS} -o ${NAME} ./libft/libft.a -lreadline -g

clean: 
			@(${LIBFT} && make clean)
			${RM} ${OBJS}

fclean: 	clean
			@(${LIBFT} && make fclean)
			${RM} ${NAME}

re:			fclean all
			

.PHONY:		all clean fclean re