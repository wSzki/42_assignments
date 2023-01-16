#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 22:40:46 by wszurkow          #+#    #+#              #
#    Updated: 2021/06/08 17:30:38 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pushswap.a
SRCS		= $(addprefix ./srcs/, ${SRCS_FILES})
SRCS_FILES	= \
			  utils/free_everything.c \
			  utils/print_error_and_exit.c \
			  operators/sx.c \
			  operators/px.c \
			  operators/rx.c \
			  operators/rrx.c \
			  sorters/sort.c \
			  sorters/scroll_to.c \
			  sorters/sort_three.c \
			  sorters/check_simple_cases.c \
			  sorters/find_smallest.c \
			  sorters/find_largest.c \
			  sorters/find_median.c \
			  sorters/push_smallest_or_largest.c \
			  sorters/quarter_sort.c \
			  ps_delete_first.c \
			  ps_prepend.c \
			  ps_atoi.c \
			  ps_fill_tab_a.c \


OBJS		= ${SRCS:.c=.o}
%.o: %.c
	gcc -Wall -Werror -Wextra -I ./includes -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
	ar -rcs ${NAME} ${OBJS}
	@gcc -o push_swap -fsanitize=address -Wall -Werror -Wextra main.c pushswap.a -I ./includes

exec:		pushswap.a
	@gcc -fsanitize=address -Wall -Werror -Wextra main.c pushswap.a -I ./includes
	@./a.out

clean:
	rm -f ${OBJS}
	rm -f push_swap

fclean:		clean
	rm -f ./${NAME}

re:			fclean all

.PHONY: 		all fclean clean re


