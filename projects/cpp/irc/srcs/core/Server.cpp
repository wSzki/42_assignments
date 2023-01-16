/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thhusser <thhusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:42:50 by thhusser          #+#    #+#             */
/*   Updated: 2022/11/21 16:55:49 by thhusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Header.hpp"
#include <netinet/in.h>

/* ========================================================================== */
/* ----------------------- CONSTRUCTORS / DESTRUCTOR ------------------------ */
/* ========================================================================== */

Server::Server(void) : _fdServer(-1), _passwd(), _port() {}
Server::Server(std::string passwd, std::string port) : _fdServer(-1), _passwd(passwd), _port(port)
{
	memset(&_serverAddress, 0, sizeof(_serverAddress));
	memset(&_clientAddress, 0, sizeof(_clientAddress));
}
Server::~Server(void) {}

Server::map_users Server::get_users() const { return _users ; }
std::string Server::getPasswd(void) const { return (_passwd); }
std::string Server::getPort(void) const { return (_port); }
void Server::setPasswd(std::string pass) { _passwd = pass; }
void Server::setPort(std::string port) { _port = port; }

/* ========================================================================== */
/* ------------------------------ SERVER INIT ------------------------------- */
/* ========================================================================== */

void Server::init(void)
{
	server_init_socket_fd(&_fdServer);
	server_init_socket_struct(_fdServer, _serverAddress, _port);
	server_init_bind_fd_to_socket(_fdServer, _serverAddress);
	server_init_check(_fdServer);
	initCmd(); // NOTE this is a Server::method
}

/* ========================================================================== */
/* ----------------------------- SERVER LAUNCH ------------------------------ */
/* ========================================================================== */

void Server::launch(void)
{
	// const int 			MAX_FD = sysconf(_SC_OPEN_MAX); //necessaire pour un usage avec select

	// NOTE: The  epoll  API  performs  a similar task to poll(2):
	// monitoring multiple file descriptors to see if I/O is possible on any of them.
	// The central concept of the epoll API is the epoll instance,
	// an in-kernel data structure which, from a user-space perspective,
	// considered as a container for two lists:
	//     uint32_t     events - interest list (== epoll set), is a list of fd that the process "wants" to monitor
	//     epoll_data_t data   - ready    list , list of fds which are ready for IO

	server_launch_epoll_init(_fdPoll);
	server_launch_epoll_struct_init(_fdServer, _fdPoll);
	server_launch_start(_fdServer, _fdPoll, *this);
}

/* ========================================================================== */
/* ----------------------------- NEW CONNECTION ----------------------------- */
/* ========================================================================== */

int Server::newConnection()
{
	int fdNew;
	std::string ip;

	fdNew = server_new_connection_accept(_fdServer, _clientAddress, _users.size());
	if (fdNew == -1)
		return (1);
	ip = inet_ntoa(_clientAddress.sin_addr);
	__debug_newConnection(ip);
	server_new_connection_epoll_ctl(fdNew, _fdPoll);
	_users[fdNew] = User(fdNew, ip);
	return (0);
}

/* ========================================================================== */
/* ----------------------------- REQUEST CLIENT ----------------------------- */
/* ========================================================================== */

static bool is_return_detected(char *buff, int len)
{
	for (int i = 0; i < len; i++)
		if (buff[i] == '\n')
			return true;
	return false;
}
std::map<std::string, Channel *> Server::getChannels()
{
	return (_channels);
};

static std::string trim_whitespaces(const std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void Server::requestClient(struct epoll_event user)
{
	char buff[BUFF_SIZE];
	int ret;
	std::string msg;
	static std::string static_buff;

	memset(buff, 0, BUFF_SIZE);
	if ((ret = recv(user.data.fd, buff, BUFF_SIZE, 0)) < 0)
	{
		perror("Fail recv user");
		exit(errno);
	}

	if (is_return_detected(buff, ret) == false)
	{
		static_buff += buff;
		return;
	}
	static_buff += buff;
	static_buff = trim_whitespaces(static_buff);
	if (static_buff.length() > 1)
		exploreCmd(user.data.fd, static_buff);
	//__debug_requestClient(static_buff);
	static_buff.clear();
}

/* ========================================================================== */
/* ---------------------------- KILL USER CLIENT ---------------------------- */
/* ========================================================================== */

void Server::killUserClient(int fd)
{
	if (epoll_ctl(_fdPoll, EPOLL_CTL_DEL, fd, NULL) < 0)
	{
		perror("Error epoll ctl del client");
		exit(EXIT_FAILURE);
	}
	if (close(fd) < 0)
	{
		perror("Error close fd client");
		exit(EXIT_FAILURE);
	}
}

/* ========================================================================== */
/* ------------------------ SERVER CHANNEL REQUESTS ------------------------- */
/* ========================================================================== */

bool Server::does_channel_exist(string ch_name) { return (_channels.find(ch_name) == _channels.end()) ? false : true; }

Channel* Server::getChannel(string ch_name) {
	return _channels.find(ch_name)->second;
}
void Server::deleteChannel(string ch_name)
{
	std::map<std::string, Channel*>::iterator it = _channels.find((ch_name));
	delete (it->second);
	_channels.erase(ch_name);
}
void Server::addChannel(string ch_name, Channel::UserPtr user)
{
	if (Debug)
		std::cout << "--addChannel--" << std::endl;
	Channel *chan = new Channel(ch_name, user);
	_channels.insert(std::make_pair<std::string, Channel *>(ch_name, chan));
}
std::map<const int, User> Server::getUsers()
{
	return _users;
}
User* Server::getUser(std::string nickname)
{

	for(std::map<const int, User>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (it->second.getNickname() == nickname)
			return (&it->second);
	}
	return NULL;
}

/* ========================================================================== */
/* ------------------------------- OPERATORS -------------------------------- */
/* ========================================================================== */

Server::map_operators* Server::get_server_operators(void) { return &_operators; }

bool Server::does_operator_name_exist(std::string name)
{
	map_operators::iterator it = _operators.begin();
	map_operators::iterator ite = _operators.end();

	while (it != ite)
	{
		if (it->first == name)
			break;
		it++;
	}

	if (it == ite)
		return false;
	return true;
}

std::string Server::is_this_user_an_operator(std::string user_name)
{
	User * user = getUser(user_name);
	return (user->get_is_operator() ? user_name : "");
}

void Server::add_server_operator(std::string user_nickname, std::string op_nickname)
{
	map_users::iterator it = _users.begin();
	map_users::iterator ite = _users.end();
	while (it != ite)
	{
		if (it->second.getNickname() == user_nickname)
			break ;
		it++;
	}
	if (it == ite)
		return;
	std::pair<std::string, User *> p(op_nickname, &(it->second));
	if (Debug)
		std::cout<<"inserted"<<std::endl;
	_operators.insert(p);
}

bool Server::is_server_operator(std::string nick)
{
	User * user = getUser(nick);
	return (user->get_is_operator() ? true : false);
}

/* ========================================================================== */
/* ----------------------- EXPLORE CMD - PARSE INPUT ------------------------ */
/* ========================================================================== */
void parse_prefix(std::string &buff)
{
	std::string::iterator it = buff.begin();
	if (buff.c_str()[0] == ':')
		it++;
	else
		return;
	for (; it != buff.end(); it++)
	{
		if (*it == ' ')
		{
			it++;
			break;
		}
	}
	buff.erase(buff.begin(), it);
}

void Server::exploreCmd(int fd, std::string buff)
{
	if (buff.size() == 0)
		return;

	/* ---------------------------------------------------------------------- */
	// 					Delete this block for a defense !
	if (Debug)
	{
		// std::str
		if (!buff.compare("M_ROOT\n") && _users[fd].getValidUser() == false)
		{
			static int nickname = 1;
			std::stringstream s;
			s << nickname;
			std::string root_nick = "root_" + s.str();
			std::string msg = "You use a backdoor for debug !\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
			_users[fd].setValidUser(true);
			_users[fd].setNickname(root_nick);
			_users[fd].setUsername(root_nick);
			_users[fd].setFullName(root_nick);
			_users[fd].setHostname(root_nick);
			acceptUser(_users[fd]);
			buff.clear();
			nickname++;
			return;
		}
	}
	/* ---------------------------------------------------------------------- */

	parse_prefix(buff);
	_buff = buff;

	std::vector<std::string> tmp;
	splitCmdIrssi(tmp, buff);
	std::vector<std::string>::iterator it_tmp = tmp.begin();

	for (; it_tmp != tmp.end(); it_tmp++)
	{
		_allBuff.clear();
		splitCmd(_allBuff, *it_tmp);

		std::vector<std::string>::iterator cmdName = _allBuff.begin();
		myToupper(*cmdName);
		std::map<std::string, cmdFunc>::iterator itCmdList = _listCmd.find(*cmdName);
		if (Debug)
			std::cout << _YELLOW << "|-|" << *cmdName << "|-|" << _NC << std::endl;
		if (itCmdList == _listCmd.end() && _users[fd].getValidUser() == false)
		{
			return;
		}
		else if (itCmdList == _listCmd.end())
		{
			std::string msg = NAME + ERR_UNKNOWNCOMMAND(_users[fd].getNickname(), print_cmd(_allBuff));
			send(_users[fd].getFd(), msg.c_str(), msg.length(), 0);
		}
		else
		{
			//User *usr = new User(_users[fd]);
			//itCmdList->second(this, *usr);
			itCmdList->second(this, _users[fd]);
		}

		if (!_users[fd].getValidUser() && !_users[fd].getNickname().empty() && !_users[fd].getUsername().empty() && !_users[fd].getFullName().empty() && !_users[fd].getHostname().empty() && _users[fd].getPASS().compare(_passwd) == 0)
		{
			_users[fd].setValidUser(true);
			acceptUser(_users[fd]);
		}
		const bool isValidUser = _users[fd].getValidUser();

		if (isValidUser && Debug)
			std::cout << _GREEN << "USER OK" << _NC << std::endl;
		else if (Debug)
			std::cout << _RED << "USER NOK" << _NC << std::endl;
	}
	if (_users[fd].getValidUser() == true)
		_users[fd].setTimeActivity();
	buff.clear();
}

/* ========================================================================== */
/* -------------------------------- PINGTIME -------------------------------- */
/* ========================================================================== */

void Server::pingTime(void)
{
	double tmp;
	std::map<const int, User>::iterator it = _users.begin(), ite = _users.end();
	std::vector<int> vecFd;

	for (; it != ite; it++)
	{
		usleep(1);
		tmp = difftime(time(NULL), it->second.getTimeActivity());
		if (tmp > REGIS_TIME && it->second.getValidUser() == false)
		{
			std::string msg = REGISTRATION_TIMEOUT(NAME_V, it->second.getIp());
			send(it->second.getFd(), msg.c_str(), msg.length(), 0);
			if (it->second.getIsKill() == false)
				killUserClient(it->second.getFd());
			vecFd.push_back(it->second.getFd());
		}
		else if (tmp > PING_TIME && it->second.getValidUser() && it->second.getPingStatus() == false) {
			std::string msg = PING(NAME);
			send(it->second.getFd(), msg.c_str(), msg.length(), 0);
			it->second.setPingStatus(true);
			it->second.setTimeActivity();
		}
		else if (tmp > PING_TIME && it->second.getValidUser() == true && it->second.getPingStatus() == true)
		{
			std::vector<std::string> tmp_chan;
			std::map<std::string, Channel *>::iterator it_c = _channels.begin();
			for(; it_c != _channels.end();it_c++) {
				if (it_c->second->does_user_exist(it->second.getNickname()))
					tmp_chan.push_back(it_c->first);
			}
			for(std::vector<std::string>::iterator vit = tmp_chan.begin(); vit != tmp_chan.end(); vit++) {
				if (getChannel(*vit)->isAdmin(it->second.getNickname()))
					getChannel(*vit)->removeAdmin(it->second.getNickname());
				getChannel(*vit)->removeUser(&it->second);
				if (getChannel(*vit)->getSize() == 0)
					deleteChannel(*vit);
			}
			tmp = difftime(time(NULL), it->second.getTimeActivity());
			std::string msg = PING_TIMEOUT(it->second.getUsername(), it->second.getIp());
			vecFd.push_back(it->second.getFd());
			send(it->second.getFd(), msg.c_str(), msg.length(), MSG_NOSIGNAL);
			if (it->second.getIsKill() == false)
				killUserClient(it->second.getFd());

		}
		else if (it->second.getIsKill() == true)
		{
			vecFd.push_back(it->second.getFd());
		}
	}
	std::vector<int>::iterator itFd = vecFd.begin();
	for (; itFd != vecFd.end(); itFd++)
	{
		_users.erase(*itFd);
	}
	vecFd.clear();
}


