#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"

class Client
{
public:
  class ClientWindow;

  Client();

  User getUser() const { return this->_user; }

  bool send(sf::Packet& packet);
  bool receive();

private:
  User _user;

  ClientWindow* _window;
  sf::TcpSocket _socket;
};

#endif
