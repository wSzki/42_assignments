# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/10 22:19:18 by wszurkow          #+#    #+#              #
#    Updated: 2021/12/12 20:32:56 by jbesnier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= hotrace
CC				= cc
HEADER			= ./
FLAGS			= -Wall -Wextra -Werror 
#THREAD_CHECK	= -fsanitize=thread
#LEAK_CHECK		= -fsanitize=address -fsanitize=leak
#VALGRINDERS		= -ggdb3
#OPTIMIZERS		= -O3
RM				= /bin/rm -f

SRCS	= \
			 ./gnl.c \
			 ./ft_strdup.c \
			 ./parse_input_file.c \
			 ./ft_calloc.c \
			 ./hash.c \
			 ./process_search_queries.c \
			 ./ft_strcmp.c \
			 ./ft_putstr.c \
			 ./lst_add.c \

OBJS		= ${SRCS:.c=.o}

%.o: %.c
	@${CC} ${FLAGS} -I ${HEADER} -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
	@echo -e [COMPILING]
	@${CC} ${FLAGS} ./main.c -lreadline ${OBJS} -o ${NAME}
	@echo -e [DONE]

clean:
	@echo -e "[CLEANING]"
	@${RM} ${OBJS}

fclean:		clean
	@echo -e "[REMOVING BINARY]"
	@${RM} ${NAME}

re:			fclean all

##################################################################

leak_sanitized:	fclean ${OBJS}
	${CC} ${FLAGS} ${LEAK_CHECK} ./main.c ${OBJS} -o ${NAME}

thread_sanitized:	fclean ${OBJS}
	${CC} ${FLAGS} ${THREAD_CHECK} ./main.c ${OBJS} -o ${NAME}

valgrinded:	fclean ${OBJS}
	${CC} ${FLAGS} ${VALGRINDERS} ./main.c ${OBJS} -o ${NAME}

optimized:	fclean ${OBJS}
	${CC} ${FLAGS} ${OPTIMIZERS} ./main.c ${OBJS} -o ${NAME}

.PHONY:\
	all fclean clean re \
	leak_sanitized \
	thread_sanitized \
	valgrinded \
	optimized


#RED_L = \033[1;31m
#GREEN_L = \033[1;32m
#GREEN = \033[0;32m
#BLUE = \033[0;34m
#RED = \033[0;31m

