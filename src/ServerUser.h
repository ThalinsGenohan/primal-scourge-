#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <SFML/Network.hpp>

#include "User.h"

class ServerUser : public User
{
public:
  ServerUser();
  explicit ServerUser(User user);

  sf::TcpSocket* getSocket() const;
  sf::IpAddress getIpAddress() const;

private:
  sf::TcpSocket* _socket;
  sf::IpAddress _ipAddress;

};

#endif
