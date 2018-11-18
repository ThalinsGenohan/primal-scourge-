#include "Message.h"

#include "User.h"
#include "operators.hpp"

Message::Message() {}
Message::Message(User user, std::string message) : _user(user), _message(message) {}

User Message::getUser() const
{
  return this->_user;
}
std::string Message::getMessage() const
{
  return this->_message;
}

std::ostream& operator<<(std::ostream& o, const Message& msg)
{
  return o << msg._user << ": " << msg._message << std::endl;
}

sf::Packet& operator<<(sf::Packet& packet, const Message& msg)
{
  return packet << msg._user << msg._message;
}

sf::Packet& operator>>(sf::Packet& packet, Message& msg)
{
  return packet >> msg._user >> msg._message;
}
