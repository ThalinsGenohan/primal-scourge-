#ifndef CHATDISPLAY_H
#define CHATDISPLAY_H

#include <TGUI/TGUI.hpp>

#include "Channel.h"
#include "Client.h"
#include "ClientWindow.h"
#include "CONSTANTS.h"

class Message;

class Client::ClientWindow::ChatDisplay
{
public:
  explicit ChatDisplay(Client& client, std::string title);

  static sf::Vector2f getSize() { return { CHATBOX_WIDTH + PADDING + MEMBERLIST_WIDTH, CHATBOX_HEIGHT + PADDING + TYPEBOX_HEIGHT }; }

  sf::Vector2f getPosition() const { return this->_position; }
  void setPosition(const sf::Vector2f position);

  tgui::Theme getTheme() const { return this->_theme; }
  void setTheme(const tgui::Theme theme);
  void setTheme(const std::string theme) { this->setTheme(tgui::Theme(theme)); }
  std::string getTitle() const { return this->_title; }
  void setTitle(const std::string title);
  std::list<Channel*> getChannels() const { return this->_channels; }
  void setChannels(const std::list<Channel*> channels);
  std::list<User*> getUsers() const { return this->_users; }
  void setUsers(const std::list<User> users);
  std::string getLastUser() const { return this->_lastUser; }
  void setLastUser(const std::string lastUser) { this->_lastUser = lastUser; }

  tgui::Tabs::Ptr getTabs() const { return this->_tabs; }
  std::map<std::string, tgui::ChatBox::Ptr> getChatBoxes() const { return this->_chatBoxes; }
  tgui::Label::Ptr getLabel() const { return this->_label; }
  tgui::ListBox::Ptr getMemberList() const { return this->_memberList; }
  tgui::Label::Ptr getMemberListLabel() const { return this->_memberListLabel; }
  tgui::TextBox::Ptr getTypeBox() const { return this->_typeBox; }
  tgui::Button::Ptr getSendButton() const { return this->_sendButton; }

  void addMessage(Message message);
  void addChannel(Channel* channel);
  void removeChannel(Channel* channel);
  void addUser(User* user);
  void removeUser(User* user);

  void switchChatBox();

  void checkInput(sf::Event event);

  std::vector<tgui::Widget::Ptr> getWidgets() const;

  bool isFocused();
  void setFocus(bool b);

  Channel getFocusedChannel() const;

private:
  sf::Vector2f _position;

  tgui::Theme _theme;
  std::string _title;
  std::list<Channel*> _channels;
  std::list<User*> _users;
  std::string _lastUser;
  int _focusedChat;
  bool _typeFocus;

  tgui::Tabs::Ptr _tabs;
  std::map<std::string, tgui::ChatBox::Ptr> _chatBoxes;
  tgui::Label::Ptr _label;
  tgui::ListBox::Ptr _memberList;
  tgui::Label::Ptr _memberListLabel;
  tgui::TextBox::Ptr _typeBox;
  tgui::Button::Ptr _sendButton;

  Client& _client;
};

#endif
