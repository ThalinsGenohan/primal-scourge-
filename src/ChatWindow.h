#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "Channel.h"
#include "ChatDisplay.h"
#include "ClientWindow.h"
#include "Message.h"

class ChatWindow : public ClientWindow
{
public:
  explicit ChatWindow(Client& client, TextManagerRef textManager);
  ~ChatWindow() {}

  Channel getFocusedChannel() const { return *this->_chat.getChannels()[this->_chat.getTabs()->getSelectedIndex()]; }

  void addChannel(Channel channel);
  void removeChannel(std::string id);
  void removeChannel(Channel channel);
  void addUser(User user) const;
  void removeUser(User user) const;
  void setUsers(std::list<User> users) const;
  void addMessage(Message message) const;

  void run() override;

private:
  ChatDisplay _chat;

};

#endif
