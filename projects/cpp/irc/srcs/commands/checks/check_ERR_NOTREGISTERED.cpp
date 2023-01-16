/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ERR_NOTREGISTERED.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:44:55 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/04 15:45:12 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool check_ERR_NOTREGISTERED(Server *server, User user)
{
	int               destination = user.getFd();
	BUFFER_           buffer      = server->get_allBuff();
	BUFFER_::iterator it          = buffer.begin();
	STR_              command     = *it;
	STR_              msg;

	if (user.getValidUser() == false)
	{
		msg = ERR_NOTREGISTERED(*it);
		send(destination, msg.c_str(), msg.length(), 0);
		return NOT_OK_;
	}
	return OK_;
}
