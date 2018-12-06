#include "pch.h"
#include "Message.h"

#include "Channel.h"
#include "User.h"

Message::Message(): _id(0), _type(MESSAGE)
{
}

Message::Message(User user, Channel channel, std::string message, MessageType type) : _id(0), _user(user), _channel(channel), _message(message), _type(type) {}

sf::Packet & operator<<(sf::Packet & p, const Message::MessageType & t)
{
  return p << int(t);
}
sf::Packet & operator>>(sf::Packet & p, Message::MessageType & t)
{
  int x;
  p >> x;
  t = Message::MessageType(x);
  return p;
}
sf::Packet & operator<<(sf::Packet & p, const Message & m)
{
  return p << m._id << m._user << m._channel << m._message << m._type;
}
sf::Packet & operator>>(sf::Packet & p, Message & m)
{
  return p >> m._id >> m._user >> m._channel >> m._message >> m._type;
}
