# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 23:22:28 by wszurkow          #+#    #+#              #
#    Updated: 2022/07/06 05:32:49 by wszurkow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.15.0

ARG USER_LOGIN

# LOCAL DEBUG
#ENV USER_LOGIN=${USER_LOGIN}
#ENV COUNTRY=FR
#ENV STATE_CODE="75"
#ENV LOCATION=Paris
#ENV ORGANISATION="42"
#ENV DOMAIN_NAME=${USER_LOGIN}.42.fr

RUN  apk upgrade
RUN  apk add --no-cache nginx openssl

COPY   conf/default.conf /etc/nginx/http.d/default.conf

RUN mkdir -p /etc/nginx/ssl

RUN  openssl                                           \
		req                                            \
		-newkey rsa:2048                               \
		-nodes                                         \
		-keyout /etc/nginx/ssl/inception.42.fr.key     \
		-x509                                          \
		-days 365                                      \
		-out /etc/nginx/ssl/inception.42.fr.crt        \
		-subj "/C=${COUNTRY}/ST=${STATE_CODE}/L=${LOCATION}/O=${ORGANISATION}/CN=${USER_LOGIN}"

#RUN    chown -R nginx:nginx /etc/nginx/ssl # Not necessary to chown to nginx

EXPOSE 443

# INFO https://stackoverflow.com/questions/57554703/why-use-nginx-with-daemon-off-in-background-with-docker
ENTRYPOINT ["nginx", "-g", "daemon off;"]
