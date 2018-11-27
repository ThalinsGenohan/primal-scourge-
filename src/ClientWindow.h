#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <TGUI/TGUI.hpp>

#include "operators.h"
#include "Channel.h"
#include "Message.h"
#include "Client.h"

class Client::ClientWindow
{
public:
  explicit ClientWindow(Client& client, TextManagerRef textManager);

  std::vector<Channel> getLChannels() const { return this->_lChannels; }
  std::vector<Channel> getRChannels() const { return this->_rChannels; }
  std::vector<Channel> getChannels() const { return  this->_lChannels + this->_rChannels; }
  std::vector<User> getUsers() const { return this->_users; }

  void addChannel(Channel channel);
  void removeChannel(std::string id);
  void removeChannel(Channel channel);
  void addUser(std::string username) const;
  void removeUser(std::string username) const;
  void addMessage(Message message);

  void sendButtonClick();

  void run();

private:
  Client& _client;
  TextManagerRef _textManager;

  sf::RenderWindow _window;

  tgui::Gui _gui;
  tgui::Theme _theme;

  std::vector<Channel> _lChannels;
  tgui::Tabs::Ptr _lTabs;
  std::map<std::string, tgui::ChatBox::Ptr> _lChatBox;

  std::vector<Channel> _rChannels;
  tgui::Tabs::Ptr _rTabs;
  std::map<std::string, tgui::ChatBox::Ptr> _rChatBox;

  std::vector<User> _users;
  tgui::ListBox::Ptr _memberList;
  tgui::TextBox::Ptr _typeBox;
  tgui::Button::Ptr _sendButton;
};

#endif
