#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <TGUI/TGUI.hpp>

#include "ClientWindow.h"
#include "TextManager.h"
#include "User.h"
#include "ChatWindow.h"

class Client
{
public:
  explicit Client(TextManagerRef textManager);

  User getUser() const { return this->_user; }

  bool connect(std::string ipAddress);
  void disconnect();

  bool send(sf::Packet& packet);
  bool send(tgui::TextBox::Ptr& textbox);
  bool receive();

private:
  User _user;

  std::vector<ChatWindow> _chatWindows;
  sf::TcpSocket _socket;

  TextManagerRef _textManager;
};

#endif
