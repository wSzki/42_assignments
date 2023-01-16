# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    start.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 16:50:30 by wszurkow          #+#    #+#              #
#    Updated: 2022/07/08 17:20:39 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LOCAL DEBUG
#MYSQL_USER_NAME="wszurkow"
#MYSQL_USER_PASSWORD=$MYSQL_USER_NAME
#MYSQL_ROOT_PASSWORD=root
#MYSQL_DATABASE_NAME="wordpress"
#WORDPRESS_DB_HOST_NAME="mariadb"
#WORDPRESS_DB_ADMIN_NAME="WP_ADMIN"
#WORDPRESS_DB_ADMIN_PASSWORD=$WORDPRESS_DB_ADMIN_NAME
#WORDPRESS_DB_USER_NAME="WP_USER"
#WORDPRESS_DB_USER_PASSWORD=$WORDPRESS_DB_USER_NAME

echo "[---- CHDIR TO SHARED DIRECTORY ----]"
cd /wordpress

echo "[---- WAITING FOR MARIADB ----]"
sleep 10;

 # WAITING FOR MARIADB CONNECTION
 until mariadb \
	 -h mariadb \
	 -u ${MYSQL_USER_NAME} \
	 -p${MYSQL_USER_PASS}; \
 do
	 echo "[---- WAITING FOR MARIADB ----]"
	 sleep 5;
 done

 echo "[---- MARIADB CONNECTED ----]"

# WORDPRESS DOWNLOAD & CONFIG, CONNECTING TO MARIADB WITH MARIADB CREDENTIALS
if [ ! -f "wp-config.php" ] ; then
 	echo "[---- DOWNLOADING WP CORE AND CREATING CONFIG ----]"
	wp core download
	wp config create \
		--dbhost=mariadb \
		--dbname=${MYSQL_DATABASE_NAME} \
		--dbuser=${MYSQL_USER_NAME} \
		--dbpass=${MYSQL_USER_PASS}
fi

# WORDPRESS INSTALL
if [ ! $(wp core is-installed) ]; then
 	echo "[---- INSTALLING WP ----]"
	wp core install \
		--title="${USER_LOGIN}'s Inception" \
		--url=${DOMAIN_NAME} \
		--admin_user=${WORDPRESS_ADMIN_NAME} \
		--admin_password=${WORDPRESS_ADMIN_PASS} \
		--admin_email=${WORDPRESS_ADMIN_MAIL} \
		--skip-email
		# CHANGING OWNERSHIP AFTER INSTALL FOR HOST SHARED FOLDER ACCESS
		adduser -DH ${MYSQL_ADMIN_NAME} ${MYSQL_ADMIN_NAME}
		chown -R ${MYSQL_ADMIN_NAME}:${MYSQL_ADMIN_NAME} /wordpress
fi

# WORDPRESS USER GENERATION
if [[ $(wp user list --field=user_login | grep ${WORDPRESS_USER_NAME} | wc -l) -eq 0 ]]; then
	 echo "[---- CREATING WP USERS ----]"
	wp user create \
		${WORDPRESS_USER_NAME} \
		${WORDPRESS_USER_MAIL} \
		--user_pass=${WORDPRESS_USER_PASS} \
		--role=editor # Author, Contributor, Subscriber
fi

#if [[ $(wp user list --field=user_login | grep test | wc -l) -eq 0 ]]; then
     #echo "[---- CREATING WP USERS ----]"
	#wp user create \
		#test \
		#"test@student.42.fr" \
		#--user_pass=test \
		#--role=editor
#fi



echo "[---- LISTING WP USERS ----]"
wp user list
echo "[---- READY ----]"
exec php-fpm7 -F

