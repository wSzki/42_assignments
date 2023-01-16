
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/22 12:57:20 by wszurkow          #+#    #+#              #
#    Updated: 2021/12/22 16:51:46 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# VARIABLES ############

SHELL		= /bin/sh

NAME		:= cub3D
FILETYPE	:= c

CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -O3
SANITIZER	:=

MLX			:= -lXext -lX11 -lm

DIR_INC		:= inc
DIR_SRC 	:= src
DIR_OBJ		:= obj
DIR_MLX		:= mlx

LIB_MLX		:= ${DIR_MLX}/libmlx.a

ECHO		:= printf
RM			:= /bin/rm -rf

HEADERS     := \
	${DIR_INC}/cub3d.h \

SRCS		:=                         \
	main.c                             \
	cub_error.c                        \
	cub_free_all.c                     \
	cub_init.c                         \
	cub_init_img.c                     \
	cub_init_mlx.c                     \
	cub_init_xpm.c                     \
	cub_init_angle.c                   \
	cub_utils.c                        \
	cub_parsing_utils.c                \
	cub_parsing_fetch_data.c           \
	cub_parsing_fill_path.c            \
	cub_parsing_fill_color.c           \
	cub_parsing_skip_newlines.c        \
	cub_parsing_fetch_map.c            \
	cub_parsing_check_after_map.c      \
	cub_parsing_validate_map.c         \
	cub_put_pixel.c                    \
	cub_get_pixel.c                    \
	cub_get_wall_pos.c                 \
	cub_render_walls.c                 \
	cub_display.c                      \
	cub_display_refresh.c              \
	cub_img_join.c                     \
	cub_keypress.c                     \
	cub_vector_end.c                   \
	utils/cub_get_wall_pos_utils.c     \
	utils/cub_get_wall_pos_utils_bis.c \
	utils/ft_atoi.c                    \
	utils/ft_split.c                   \
	utils/ft_strdup.c                  \
	utils/ft_strncmp.c                 \
	utils/get_next_line.c              \
	utils/ft_is_in_c.c


OBJS		= \
			  $(addprefix ${DIR_OBJ}/, ${SRCS:.c=.o})

# DEBUG ################

ifdef DEBUG
	FLAGS		:=
endif

ifdef VALG
	SANITIZER	:= -g3
endif

ifdef ASAN
	SANITIZER	:= -fsanitize=address -fsanitize=leak
endif

# MACROS ###############

CC_FULL		:= ${CC} ${FLAGS} ${SANITIZER} -I ${DIR_INC} -I ${DIR_MLX} ${MLX}

# RULES #################
all		:	${NAME}
bonus           :       ${NAME}

$(DIR_OBJ)	:
	mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o	:	$(DIR_SRC)/%.c | ${DIR_OBJ} ${HEADERS}
	@mkdir -p $(dir $@)
	@${CC_FULL} -o $@ -c $<

$(NAME)		:	 $(OBJS)
	@make -C ${DIR_MLX}
	${CC_FULL}  $(OBJS)  ${LIB_MLX} ${MLX} -o ${NAME}

clean	:
	@make clean -C ${DIR_MLX}
	@${RM} ${DIR_OBJ}

fclean	:	clean
	@${RM} ${NAME}

re		:	fclean all


.PHONY:\
	all fclean clean re

# COLORS ################
R				=	${ECHO} "\033[0;31m"
G				=	${ECHO} "\033[0;32m"
B				=	${ECHO} "\033[0;34m"
Y				=	${ECHO} "\033[1;33m"
BLACK			=	${ECHO} "\033[0;30m"
PURPLE			=	${ECHO} "\033[0;35m"
CYAN			=	${ECHO} "\033[0;36m"
ORANGE			=	${ECHO} "\033[0;33m"
LIGHT_GRAY		=	${ECHO} "\033[0;37m"
DARK_GRAY		=	${ECHO} "\033[1;30m"
LIGHT_RED		=	${ECHO} "\033[1;31m"
LIGHT_GREEN		=	${ECHO} "\033[1;32m"
LIGHT_BLUE		=	${ECHO} "\033[1;34m"
LIGHT_PURPLE	=	${ECHO} "\033[1;35m"
LIGHT_CYAN		=	${ECHO} "\033[1;36m"
WHITE			=	${ECHO} "\033[1;37m"
NO_COLOR		=	${ECHO} "\033[0m"
BOLD			=	${ECHO} "\e[1m"
_R				=	${ECHO} "\e[0m"

# MISC #################
#Auto update
#@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUE): $(GREEN)Compiled [√]$(RESET)\n"
# use "\r" on printf to clear current line
