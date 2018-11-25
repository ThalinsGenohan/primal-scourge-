#ifndef CLIENT_H
#define CLIENT_H

#include "User.h"
#include "TextManager.h"

class Client
{
public:
  class ClientWindow;

  explicit Client(TextManagerRef textManager);

  User getUser() const { return this->_user; }

  bool connect(std::string ipAddress);

  bool send(sf::Packet& packet);
  bool receive();

private:
  User _user;

  ClientWindow* _window;
  sf::TcpSocket _socket;

  TextManagerRef _textManager;
};

#endif
