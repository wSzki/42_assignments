# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wsz </var/spool/mail/wsz>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/12 05:48:53 by wsz               #+#    #+#              #
#    Updated: 2022/07/12 05:50:44 by wsz              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/sh

echo "[ ---- LAUNCHING MYSQLD IN BACKGROUND ----]";
mysqld_safe --user=${MYSQL_ADMIN_NAME} --datadir='/data' &

until mysqladmin status 2> /dev/null; do
	echo "[ ---- WAITING FOR MYSQLD TO LAUNCH ----]";
	sleep 1;
done

#echo "[ ---- GENERATING DB IF IT DOES NOT EXIST ----]"
if [ $(mariadb -e "SHOW DATABASES" | grep "${MYSQL_DATABASE_NAME}" | wc -l) ]; then
	mariadb -e "$(eval "echo \"$(cat wordpress.sql)\"")"
fi

echo "[ ---- WAITING FOR BACKGROUND MYSQLD TO DIE ----]";
killall mariadbd
sleep 5

echo "[ ---- LAUNCHING MYSQLD IN FOREGROUND ----]";
exec mysqld_safe --user=${MYSQL_ADMIN_NAME} --datadir='/data'
