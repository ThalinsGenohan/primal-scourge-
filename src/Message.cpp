#include "Message.h"

#include "User.h"
#include "operators.hpp"

Message::Message(): _id(0), _channel(nullptr) {}

Message::Message(User user, Channel* channel, std::string message, MessageType type) : _id(0), _user(user), _channel(channel), _message(message), _type(type) {}

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
