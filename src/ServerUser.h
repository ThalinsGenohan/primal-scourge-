#ifndef SERVERUSER_H
#define SERVERUSER_H

#include <SFML/Network/IpAddress.hpp>

#include "User.h"

namespace sf
{
  class TcpSocket;
}

class ServerUser : public User
{
public:
  ServerUser();
  explicit ServerUser(User user);
  explicit ServerUser(sf::TcpSocket* socket);

  sf::TcpSocket* getSocket() const { return this->_socket; }
  sf::IpAddress getIpAddress() const { return this->_ipAddress; }

  bool saveUser() const;

  friend std::ostream& operator<<(std::ostream& fs, const ServerUser& su);
  friend std::istream& operator>>(std::istream& fs, ServerUser& su);

private:
  sf::TcpSocket* _socket;
  sf::IpAddress _ipAddress;

};

extern std::ostream& operator<<(std::ostream& os, const std::vector<std::string> v);
extern std::ostream& operator<<(std::ostream& os, const ServerUser& su);
extern std::istream& operator>>(std::istream& is, ServerUser& su);
extern User serverUserToUser(ServerUser su);

#endif
