# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/10 09:48:37 by thhusser          #+#    #+#              #
#    Updated: 2022/11/18 11:53:04 by thhusser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_NC     = `tput sgr0`
_RED    = \033[0;31m
_GREEN  = \033[0;32m
_YELLOW = \033[0;33m
_BLUE   = \033[0;34m
_PURPLE = \033[0;95m
_CYAN   = \033[0;36m
_WHITE  = \033[0;37m

NAME    =  ircserv
RM      =  rm    -rf
CC      =  c++
FLAGS   =  -Wall -Wextra -Werror -std=c++98
DIR_INC =  -I    ./includes/
DIR_INC += -I    ./includes/numericReplies/

SRCS		:=                                                \
				main.cpp                                      \
				core/Server.cpp                               \
				core/Channel.cpp                              \
				core/User.cpp                                 \
				core/server/server_init.cpp                   \
				core/server/server_launch.cpp                 \
				core/server/server_new_connection.cpp         \
				\
				utils/basic/perror_and_exit.cpp               \
				utils/basic/myToupper.cpp                     \
				utils/basic/find_char_string.cpp\
				utils/basic/get_local_time.cpp                \
				utils/basic/send_to_client.cpp                \
				\
				utils/print/print_buff.cpp                    \
				utils/print/print_cmd.cpp                     \
				utils/print/print_allBuff.cpp                 \
				utils/print/print_server_users.cpp            \
				utils/print/print_users.cpp                   \
				\
				utils/split/splitCmdIrssi.cpp                 \
				utils/split/splitCmdUser.cpp                  \
				utils/split/splitCmd.cpp                      \
				utils/split/split_classic.cpp                 \
				\
				utils/debug/debug.cpp                         \
				\
				commands/connection.cpp                       \
				commands/init_commands.cpp                    \
				commands/nick.cpp                             \
				commands/kill.cpp                             \
				commands/ping.cpp                             \
				commands/pass.cpp                             \
				commands/user.cpp                             \
				commands/cap.cpp                              \
				commands/topic.cpp                            \
				\
				commands/version.cpp                          \
				commands/time.cpp                             \
				commands/info.cpp                             \
				commands/quit.cpp                             \
				commands/motd.cpp                             \
				commands/notice.cpp                           \
				commands/join.cpp                             \
				commands/privmsg.cpp                          \
				commands/bot_privmsg.cpp                      \
				commands/names.cpp                            \
				commands/list.cpp                             \
				commands/mode.cpp                             \
				commands/invite.cpp                           \
				commands/part.cpp                             \
				commands/mode_channel.cpp                     \
				commands/mode_user.cpp                        \
				commands/mode_utils.cpp                       \
				commands/who.cpp                              \
				commands/pong.cpp                             \
				commands/kick.cpp                             \
				commands/oper.cpp                             \
				\
				commands/checks/check_ERR_NOSUCHSERVER.cpp    \
				commands/checks/check_ERR_NOTREGISTERED.cpp   \
				commands/checks/check_ERR_NEEDMOREPARAMS.cpp  \
				commands/checks/check_ERR_NOTONCHANNEL.cpp    \
				commands/checks/check_ERR_NOSUCHCHANNEL.cpp   \
				commands/checks/check_ERR_NOSUCHNICK.cpp      \
				commands/checks/check_ERR_NONICKNAMEGIVEN.cpp \


# SRCS		+= SRCS_CMD
DIR_SRCS    := ./srcs
DIR_OBJ     := obj
OBJS        := $(addprefix ${DIR_OBJ}/, ${SRCS:.cpp=.o})
DEPS        =  $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

$(DIR_OBJ)/%.o:	$(DIR_SRCS)/%.cpp
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} ${DIR_INC} -o $@ -c $< -MMD

$(NAME):		$(OBJS)
	@$(CC) $(FLAGS) ${DIR_INC} $(OBJS) -o $(NAME)
	@printf "$(_GREEN)Generating $(NAME) $(_NC)\n"

clean:
	@$(RM) $(DIR_OBJ)
	@printf "$(_GREEN)Deletes objects files $(NAME) $(_NC)\n"

fclean:		clean
	@$(RM) $(NAME)
	@printf "$(_GREEN)Delete $(NAME) $(_NC)\n"

re:			fclean all

