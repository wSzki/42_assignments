#!/bin/bash

service php7.3-fpm start
service nginx start
service mysql start
service --status-all
rm -f /var/www/html/index.nginx-debian.html

zsh
