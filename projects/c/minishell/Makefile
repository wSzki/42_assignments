#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 22:40:46 by wszurkow          #+#    #+#              #
#    Updated: 2021/11/12 13:55:14 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
CC				= clang
HEADER			= ./includes
FLAGS			= -Wall -Wextra -Werror  -g
THREAD_CHECK	= -fsanitize=thread
LEAK_CHECK		= -fsanitize=address -fsanitize=leak
VALGRINDERS		= -ggdb3
OPTIMIZERS		= -O3
RM				= /bin/rm -f

SRCS		= $(addprefix ./srcs/, ${SRCS_FILES})
SRCS_FILES	= \
			  memory/memory_management.c \
			  \
			  libft/ft_atoi.c \
			  libft/ft_split.c \
			  libft/ft_strlen.c \
			  libft/ft_putstr_fd.c \
			  libft/ft_substr.c \
			  libft/ft_strncmp.c \
			  libft/ft_strcmp.c \
			  libft/ft_strjoin.c \
			  libft/ft_strdup.c \
			  \
			  utils/find_absolute_path.c \
			  utils/extract_string.c \
			  utils/matrixlen.c \
			  utils/tablen.c \
			  utils/is_whitespace.c \
			  utils/only_whitespaces.c \
			  utils/error_management.c \
			  utils/expand_env_variables_utils.c \
			  \
			  builtins/is_builtin.c \
			  builtins/pwd.c \
			  builtins/echo.c \
			  builtins/cd.c \
			  builtins/exit.c \
			  builtins/env.c \
			  builtins/unset.c \
			  builtins/export.c \
			  \
			  env_utils/custom_getenv.c \
			  env_utils/add_or_replace_env_variable.c \
			  env_utils/increment_env_variable.c \
			  env_utils/init_env.c \
			  env_utils/check_minishell_lvl.c \
			  \
			  signals/manage_main_signal.c \
			  signals/manage_sub_signal.c \
			  signals/heredoc_signal.c \
			  \
			  execution/execute_redirections.c \
			  execution/execute_builtin.c \
			  execution/execute_bin.c \
			  execution/execute_single_command.c \
			  execution/execute_pipeline.c \
			  \
			  parsing/extract_tokens.c \
			  parsing/extract_commands.c \
			  parsing/extract_operators.c \
			  parsing/split_at_operators.c \
			  parsing/trim_whitespaces.c \
			  parsing/check_for_unclosed_quotes.c \
			  parsing/trim_quotes.c \
			  parsing/expand_env_variables.c \
			  parsing/contains_only_whitespaces.c \
			  \
			  redirections/heredoc.c \
			  redirections/is_redirection.c \
			  redirections/redirect.c \
			  redirections/catch_unexpected_token.c \
			  redirections/heredoc_utils.c \
			  redirections/restore_io.c \

OBJS		= ${SRCS:.c=.o}

%.o: %.c
	@${CC} ${FLAGS} -I ${HEADER} -o $@ -c $<

all:		${NAME}

${NAME}:	${OBJS}
	@echo -e '\033[1;37m[COMPILING]\033[m'
	@${CC} ${FLAGS} ./main.c -lreadline ${OBJS} -o ${NAME}
	@echo -e '\033[1;32m[DONE]\033[m'

clean:
	@echo  "\033[1;31m[CLEANING]\033[m"
	@${RM} ${OBJS}

fclean:		clean
	@echo  "\033[1;31m[REMOVING BINARY]\033[m"
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

