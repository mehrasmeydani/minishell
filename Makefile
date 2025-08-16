SRC			= main.c mini_split.c my_read.c quotes.c
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