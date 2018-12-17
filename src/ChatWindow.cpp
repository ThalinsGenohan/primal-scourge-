#include "pch.h"
#include "ChatWindow.h"

ChatWindow::ChatWindow(Client & client, TextManagerRef textManager): ClientWindow(client, textManager), _chat(client, this->_theme, "Chat")
{
}

void ChatWindow::addChannel(Channel channel)
{
  this->_chat.addChannel(channel);
}

void ChatWindow::removeChannel(Channel channel)
{
  this->_chat.removeChannel(channel);
}

void ChatWindow::addUser(User user) const
{

}

void ChatWindow::removeUser(User user) const
{
}

void ChatWindow::setUsers(std::list<User> users) const
{
}

void ChatWindow::addMessage(Message message) const
{
}

void ChatWindow::run()
{
}
