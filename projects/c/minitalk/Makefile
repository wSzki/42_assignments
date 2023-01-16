# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 18:57:18 by wszurkow          #+#    #+#              #
#    Updated: 2021/08/18 06:16:50 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME = client
SERVER_NAME = server

CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = /bin/rm -f

CLIENT_OBJS			= ${CLIENT_SRCS:.c=.o}
CLIENT_SRCS			= $(addprefix ./srcs/, ${CLIENT_FILES})
CLIENT_FILES = \
			   client.c \
			   mt_utils.c \

SERVER_OBJS			= ${SERVER_SRCS:.c=.o}
SERVER_SRCS			= $(addprefix ./srcs/, ${SERVER_FILES})
SERVER_FILES = \
			   server.c \
			   mt_utils.c \

%.o: %.c
	${CC} ${FLAGS} -I ./includes -o $@ -c $<

all: ${CLIENT_NAME} ${SERVER_NAME}

$(CLIENT_NAME): ${CLIENT_OBJS}
	${CC} ${FLAGS} ${CLIENT_OBJS} -o ${CLIENT_NAME}

$(SERVER_NAME): ${SERVER_OBJS}
	${CC} ${FLAGS} ${SERVER_OBJS} -o ${SERVER_NAME}

clean :
	${RM} ./${CLIENT_OBJS}
	${RM} ./${SERVER_OBJS}

fclean : clean
	${RM} ./${CLIENT_NAME}
	${RM} ./${SERVER_NAME}

re : fclean all

.PHONY:	all clean fclean re
