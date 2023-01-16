/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_server_users.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:32:51 by wszurkow          #+#    #+#             */
/*   Updated: 2022/11/18 11:21:36 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
void Server::print_server_users(void)
{
	map_users::iterator it = _users.begin();
	map_users::iterator ite = _users.end();
	int fd;
	while (it != ite)
	{
		fd = (*it).second.getFd();
		if (Debug) {
			std::cout << "+ FD OF SERVER USER IS : " << fd << std::endl;
			std::cout << "- FD OF SERVER USER IS : " << (*it).first << std::endl;
		}
		it++;
	}
}

