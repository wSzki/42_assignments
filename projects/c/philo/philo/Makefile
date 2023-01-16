#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 22:40:46 by wszurkow          #+#    #+#              #
#    Updated: 2021/11/14 21:27:07 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo
CC				= clang
HEADER			= ./includes
FLAGS			= -Wall -Wextra -Werror -pthread
THREAD_CHECK	= -fsanitize=thread
LEAK_CHECK		= -fsanitize=address -fsanitize=leak
VALGRINDERS		= -ggdb3
OPTIMIZERS		= -O3
RM				= /bin/rm -f

SRCS		= $(addprefix ./srcs/, ${SRCS_FILES})
SRCS_FILES	= \
			  ft_atoi.c \
			  ft_strlen.c \
			  initialize.c \
			  routine.c \
			  threads.c \
			  all_full.c \
			  monitor_death.c \
			  putmsg.c \
			  timestamp.c \

OBJS		= ${SRCS:.c=.o}

%.o: %.c
	@${CC} ${FLAGS} -I ${HEADER} -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
	@echo -e "${YELLOW}[COMPILING]${R}"
	@${CC} ${FLAGS} ./main.c -lreadline ${OBJS} -o ${NAME}
	@echo -e "${GREEN}[DONE]${R}"

clean:
	@echo -e "${RED}[CLEANING]${R}"
	@${RM} ${OBJS}

fclean:		clean
	@echo -e "${RED}[REMOVING BINARY]${R}"
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

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
LIGHT_GRAY		=	\033[0;37m
DARK_GRAY		=	\033[1;30m
LIGHT_RED		=	\033[1;31m
LIGHT_GREEN		=	\033[1;32m
YELLOW			=	\033[1;33m
LIGHT_BLUE		=	\033[1;34m
LIGHT_PURPLE	=	\033[1;35m
LIGHT_CYAN		=	\033[1;36m
WHITE			=	\033[1;37m
NO_COLOR		=	\033[0m
BOLD		=\e[1m
R			=\e[0m

#Auto update
#@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUE): $(GREEN)Compiled [√]$(RESET)\n"

# $(RESET)
