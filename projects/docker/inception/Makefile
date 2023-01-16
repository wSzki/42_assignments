# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 00:12:20 by wszurkow          #+#    #+#              #
#    Updated: 2022/07/09 00:17:55 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# https://stackoverflow.com/a/70663753
include ./srcs/.env
export

######################################

DOCKER_COMPOSE = docker-compose --file ./srcs/docker-compose.yml
SHARED         = ${HOST_SHARED_VOLUME}

all:
	@mkdir -p ${SHARED}/mariadb
	@mkdir -p ${SHARED}/wordpress
	@sudo sh -c 'if [ ! $(cat /etc/hosts | grep -w "127.0.0.1 ${DOMAIN_NAME}") ]; then echo "127.0.0.1 ${DOMAIN_NAME}" >> /etc/hosts;	fi'
	@${DOCKER_COMPOSE} up --build

up:
	${DOCKER_COMPOSE} up -d

up-no-daemon:
	${DOCKER_COMPOSE} up

down:
	${DOCKER_COMPOSE} down

clean:
	@${DOCKER_COMPOSE} down --rmi all --volumes
	@rm -rf ${HOST_SHARED_VOLUME}

fclean:
	@if [ -z $(cat /etc/hosts | grep -w "127.0.0.1 ${DOMAIN_NAME}") ]; then sudo sed -i "/127.0.0.1 ${DOMAIN_NAME}/d" /etc/hosts; fi
	@${DOCKER_COMPOSE} down --rmi all --volumes
	@rm -rf ${HOST_SHARED_VOLUME}

re: fclean all

.PHONY: all fclean clean re up up-no-daemon down

