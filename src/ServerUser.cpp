#include "ServerUser.h"

#include <iostream>

ServerUser::ServerUser(): _socket(nullptr) {}

ServerUser::ServerUser(User user) : User(user), _socket()
{
  std::cout << this->_id;
}

sf::TcpSocket* ServerUser::getSocket() const
{
  return this->_socket;
}

sf::IpAddress ServerUser::getIpAddress() const
{
  return this->_ipAddress;
}

