SRCS		= main.c philo.c utils.c

OBJS		= ${SRCS:.c=.o}

HEADER		= philo.h

NAME		= philo

CC			= gcc

RM			= rm -f

CFLAGS		= -g #-Wall -Wextra -Werror

all:		${NAME}

${NAME}:	${HEADER} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re

