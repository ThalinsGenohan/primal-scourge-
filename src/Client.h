#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "User.h"
#include "TextManager.h"

class Client
{
public:
  class ClientWindow;

  explicit Client(sf::IpAddress ip, TextManagerRef textManager);

  User getUser() const { return this->_user; }

  bool connect(std::string ipAddress);
  void disconnect();

  bool send(sf::Packet& packet);
  bool send(tgui::TextBox::Ptr& textbox);
  bool receive();

private:
  User _user;

  ClientWindow* _window;
  sf::TcpSocket _socket;

  TextManagerRef _textManager;
};

#endif
