# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 05:26:27 by wszurkow          #+#    #+#              #
#    Updated: 2022/07/12 05:49:46 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.15.0

ARG MYSQL_ADMIN_NAME

# LOCAL DEBUG
#ENV MYSQL_USER_NAME=wsz
#ENV MYSQL_USER_PASSWORD=wsz
#ENV MYSQL_ROOT_PASSWORD=wsz
#ENV MYSQL_DATABASE_NAME=wordpress_database

# mariadb-client for testing purposes
RUN 	apk update && apk upgrade
RUN		apk add --no-cache \
			mariadb \
			mariadb-client

# UTILS
COPY	./tools/start.sh     /entrypoint/
COPY	./conf/wordpress.sql /entrypoint/

# DATABASE INITIALISATION [INFO] : https://mariadb.com/kb/en/mysql_install_db/
RUN		sed -i "s|.*bind-address\s*=.*|bind-address=0.0.0.0|g" /etc/my.cnf.d/mariadb-server.cnf
RUN		sed -i "s|skip-networking|# skip-networking|g"         /etc/my.cnf.d/mariadb-server.cnf

# CREATING USER FOR SHARED FOLDER ACCESS
RUN adduser -DH $MYSQL_ADMIN_NAME && addgroup $MYSQL_ADMIN_NAME mysql

# DATABASE CREATED BY DEFAULT IN /data, width default user "mysql" unless specified
RUN		mariadb-install-db --user=$MYSQL_ADMIN_NAME	#--auth-root-authentication-method=normal

# CHANGING OWNERSHIP OF SHARED FOLDER AFTER INSTALLATION
RUN chown -R $MYSQL_ADMIN_NAME:$MYSQL_ADMIN_NAME /data

# START
WORKDIR		/entrypoint
ENTRYPOINT	["sh", "start.sh"]

# **************************************************************************** #

# DAEMON SOCKETS, mariadb install does not generate it ? FALSE, mariadb-install-db seems to generate it
#RUN		\
			#mkdir -p /run/mysqld
			#chown -R mysql:mysql /run/mysqld

## Database created by default in /data
#RUN		mariadb-install-db --user=mysql
			##--auth-root-authentication-method=normal // used with --datadir below
			##--datadir='/home/mariadb' \
