

#######################
# DOCKER CLI COMMANDS #
#######################

# -i interactive mode
# -t pseudo tty (bash)
# -d detached mode (background)
# -p 80:80 map port 80 host to conatiner
# docker container run -d -t <IMAGE NAME>
# docker exec -ti <id>
# docker stop <id>

#####################
# DOCKER CREATE     #
#####################

# docker build -t <NAME>../ // build image from Dockerfile
# docker create // docker create --name <NAME> <OS>
# docker start
# docker run = docker create && docker start
# docker container run -it <NAME>  /bin/bash
# docker container start <CONTAINER ID> -i

#####################
# DOCKER DELETE     #
#####################

# docker image prune
# docker container prune
# docker rm <id>
# docker rmi


#################
# DOCKER LAUNCH #
#################

# docker build -t server .
# docker create -it -p 80:80 -p443:443 server
# docker start -it <ID>
# docker exec -i <ID> /bin/zsh

########
# INFO #
########

# RUN = Execute when build
# CMD = Execute when starting
#	If multiple CMD, only one is executed
#	If arguments passed, CMD is not executed
# ENTRYPOINT = Like CMD, but executes always. Only one allowed

# Infinite loop
# ENTRYPOINT ["tail", "-f", "/dev/null"]


# Getting base image
FROM debian:buster

MAINTAINER <wszurkow@42.student.fr>

# SET $HOME > ~/
WORKDIR /root/

# UPDATE DEBIAN
RUN apt-get update -y

# INSTALL NGINX, MARIADB, PHP, WGET
RUN apt-get install -y \
		nginx \
		mariadb-server \
		wget \
		php7.3-fpm \
		php-mysql \
		php \
		php-cgi \
		php-mysqli \
		php-pear \
		php-mbstring \
		php-gettext \
		php-common \
		php-phpseclib

# INSTALL ADDITIONAL TOOLS
RUN apt-get install -y vim zsh git fzf ack

# INSTALL OH MY ZSH
RUN sh -c "$(wget https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"

# GENERATE WORDPRESS DATABASE
RUN		service mysql start && \
		# CREATE USER
		echo "CREATE USER 'user'@'localhost';" | mysql -u root && \
		echo "SET password FOR 'user'@'localhost' = password('user');" | mysql -u root && \
		# CREATE WP DB
		echo "CREATE DATABASE wordpress;" | mysql -u root && \
		echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'user'@'localhost' IDENTIFIED BY 'user';" | mysql -u root && \
		# CREATE PHPMYADMIN DB
		echo "CREATE DATABASE phpmyadmin;" | mysql -u root && \
		echo "GRANT ALL PRIVILEGES ON phpmyadmin.* TO 'user'@'localhost' IDENTIFIED BY 'user';" | mysql -u root && \
		# SAVE CHANGES
		echo "FLUSH PRIVILEGES;" | mysql -u root

# INSTALL WORDPRESS
RUN		wget https://wordpress.org/latest.tar.gz && \
		tar -xzf latest.tar.gz && \
		mv wordpress /var/www/html && \
		chown -R www-data:www-data /var/www/html/wordpress && \
		chmod -R 775 /var/www/html/wordpress/ && \
		rm -f latest.tar.gz

# INSTALL PHPMYADMIN
# https://phoenixnap.com/kb/how-to-install-phpmyadmin-on-debian-10
RUN		wget https://www.phpmyadmin.net/downloads/phpMyAdmin-latest-english.tar.gz && \
		tar -xzf phpMyAdmin-latest-english.tar.gz && \
		rm phpMyAdmin-latest-english.tar.gz && \
		mv phpMyAdmin* /var/www/html/phpmyadmin && \
		mkdir /var/www/html/phpmyadmin/tmp && chmod 777 /var/www/html/phpmyadmin/tmp

# GENERATE SSL CERTIFICATE
# https://www.tutorialspoint.com/how-to-use-openssl-for-generating-ssl-certificates-private-keys-and-csrs
RUN		openssl req -newkey rsa:2048 -nodes -keyout /etc/ssl/private/ssl_key.key \
		-x509 -days 365 -out /etc/ssl/certs/ssl_certificate.crt \
		-subj "/C=FR/ST=75/L=Paris/O=42/CN=wsz"

COPY ./srcs/default /etc/nginx/sites-available/default
COPY ./srcs/wp-config.php /var/www/html/wordpress
COPY ./srcs/autoindex /bin
COPY ./srcs/setup.sh ./
COPY ./srcs/config.inc.php /var/www/html/phpmyadmin/
COPY ./srcs/index.nginx.html /var/www/html/

ENTRYPOINT ["./setup.sh"]
