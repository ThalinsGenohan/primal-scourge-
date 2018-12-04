#include "ServerPacket.h"

ServerPacket::ServerPacket() {}

ServerPacket::ServerPacket(Message msg, std::list<User> users, std::list<Channel> channels) : _message(msg), _users(users), _channels(channels) {}

User ServerPacket::getUser(int id) const
{
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = *it;
    if (u.getId() == id)
    {
      return u;
    }
  }
  return User();
}

User ServerPacket::getUser(std::string username) const
{
  for (auto it = this->_users.begin(); it != this->_users.end(); ++it)
  {
    auto& u = *it;
    if (u.getUsername() == username)
    {
      return u;
    }
  }
  return User();
}

Channel ServerPacket::getChannel(std::string name) const
{
  for (auto it = this->_channels.begin(); it != this->_channels.end(); ++it)
  {
    auto& c = *it;
    if (c.getName() == name || c.getId() == name)
    {
      return c;
    }
  }
  return Channel();
}

sf::Packet & operator<<(sf::Packet & p, const ServerPacket & sp)
{
  return p << sp._message << sp._users << sp._channels;
}

sf::Packet & operator>>(sf::Packet & p, ServerPacket & sp)
{
  return p >> sp._message >> sp._users >> sp._channels;
}
