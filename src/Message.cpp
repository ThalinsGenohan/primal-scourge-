#include "Message.h"

#include <string>
#include <SFML/Network.hpp>

#include "operators.h"
#include "User.h"

std::ostream& operator<<(std::ostream& o, Message& msg)
{
  return o << msg._user << ": " << msg._message << std::endl;
}
sf::Packet& operator<<(sf::Packet& packet, Message& msg)
{
  return packet << msg._user << msg._message;
}
sf::Packet& operator>>(sf::Packet& packet, Message& msg)
{
  return packet >> msg._user >> msg._message;
}

Message::Message(): _id(0), _channel(nullptr), _type(MESSAGE)
{
}

Message::Message(User user, Channel* channel, std::string message, MessageType type) : _id(0), _user(user), _channel(channel), _message(message), _type(type) {}

