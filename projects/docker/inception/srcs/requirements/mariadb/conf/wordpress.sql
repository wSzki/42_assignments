-- ************************************************************************** --
--                                                                            --
--                                                        :::      ::::::::   --
--   wordpress.sql                                      :+:      :+:    :+:   --
--                                                    +:+ +:+         +:+     --
--   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        --
--                                                +#+#+#+#+#+   +#+           --
--   Created: 2022/07/12 05:48:47 by wszurkow          #+#    #+#             --
--   Updated: 2022/07/12 05:48:49 by wszurkow         ###   ########.fr       --
--                                                                            --
-- ************************************************************************** --

DROP   DATABASE IF EXISTS test;

CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE_NAME};
CREATE USER IF NOT EXISTS '${MYSQL_USER_NAME}'@'%' IDENTIFIED BY '${MYSQL_USER_PASS}';

GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE_NAME}.* TO ${MYSQL_USER_NAME}@'%' IDENTIFIED BY '${MYSQL_USER_PASS}';

-- SET PASSWORD FOR 'root'@'localhost' = PASSWORD('${MYSQL_ROOT_PASSWORD}');

FLUSH PRIVILEGES;

