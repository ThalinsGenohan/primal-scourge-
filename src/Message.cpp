#include "Message.h"

#include <string>
#include <SFML/Network.hpp>

#include  "Channel.h"
#include "User.h"
#include "operators.h"

sf::Packet& operator<<(sf::Packet& packet, const Message& msg)
{
  return packet << msg._user << msg._channel << msg._message;
}
sf::Packet& operator>>(sf::Packet& packet, Message& msg)
{
  return packet >> msg._user >> msg._message;
}

Message::Message(): _id(0), _type(MESSAGE)
{
}

Message::Message(User user, Channel channel, std::string message, MessageType type) : _id(0), _user(user), _channel(channel), _message(message), _type(type) {}

