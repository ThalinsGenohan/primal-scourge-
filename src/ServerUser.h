#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <SFML/Network.hpp>

#include "User.h"

class ServerUser : public User
{
public:
  ServerUser();
  explicit ServerUser(User user);
  explicit ServerUser(sf::TcpSocket* socket);

  sf::TcpSocket* getSocket() const { return this->_socket; }
  sf::IpAddress getIpAddress() const { return this->_ipAddress; }

  bool saveUser() const;

  friend std::ostream& operator<<(std::ostream& os, ServerUser u);
  friend std::ofstream& operator<<(std::ofstream& ofs, ServerUser u);
  friend std::istream& operator>>(std::istream& is, ServerUser& u);

private:
  sf::TcpSocket* _socket;
  sf::IpAddress _ipAddress;

};

std::ostream& operator<<(std::ostream& os, ServerUser u);
std::ofstream& operator<<(std::ofstream& ofs, ServerUser u);
std::istream& operator>>(std::istream& is, ServerUser& u);

#endif
