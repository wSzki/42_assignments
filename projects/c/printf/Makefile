# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 22:40:46 by wszurkow          #+#    #+#              #
#    Updated: 2021/01/24 23:22:10 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
SRCS		= $(addprefix ./srcs/, ${SRCS_FILES})
SRCS_FILES	= \
				ft_printf.c \
				ft_printf_character.c \
				ft_printf_string.c \
				ft_printf_number.c \
				ft_printf_utils.c \
				ft_printf_putnbr_base.c \
				ft_printf_atoi.c \
				ft_printf_parsers.c \

OBJS		= ${SRCS:.c=.o}
%.o: %.c
				clang -Wall -Werror -Wextra -I ./includes -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
				ar -rcs libftprintf.a ${OBJS}

clean:
				rm -f ${OBJS}

fclean:		clean
				rm -f ./libftprintf.a

re:			fclean all

.PHONY: 		all fclean clean re
