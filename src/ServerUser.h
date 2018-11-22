#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <SFML/Network.hpp>

#include "User.h"

class ServerUser : public User
{
public:
  ServerUser();
  explicit ServerUser(User user);

  sf::TcpSocket* getSocket() const { return this->_socket; }
  sf::IpAddress getIpAddress() const { return this->_ipAddress; }

private:
  sf::TcpSocket* _socket;
  sf::IpAddress _ipAddress;

};

#endif
